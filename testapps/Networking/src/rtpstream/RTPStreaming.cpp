#include "RTPStreaming.h"
#include "Logging.h"
#include "FileReader.h"
#include "TSPacket.h"
#include "RTPHeader.h"

#include <functional>
#include <thread>

RTPStreaming::RTPStreaming(std::string interfaceAddress, uint16_t port)
	: m_interfaceAddress(std::move(interfaceAddress))
	, m_port(port)
	, m_igmpListener(interfaceAddress, std::bind(&RTPStreaming::m_StreamRequested,
		 										     this, std::placeholders::_1))
{
	LOGD("");
	m_igmpListener.Listen();
}

void RTPStreaming::m_StreamRequested(std::string&& multicastAddress)
{
	static uint16_t seqNum = 0;

	if(multicastAddress == m_multicastAddress)
	{
		LOGD("Already streaming for address", multicastAddress);
		return;
	}
	else
	{
		LOGD("New multicast address", multicastAddress);
		m_multicastAddress = multicastAddress;
	}

	try
	{
		FileReader reader("/home/dimitrios/Videos/boa_clear.ts");
		MulticastClient multicastClient(m_interfaceAddress, std::move(multicastAddress), m_port);
		struct timespec tp;
		if (clock_gettime(CLOCK_MONOTONIC, &tp) != 0)
		{
			LOGE("Failed to get CLOCK_MONOTONIC");
			return;
		}

		uint32_t timestamp =  static_cast<uint32_t>((tp.tv_sec * 90000LL) + ((tp.tv_nsec * 9LL) / 100000LL));
		LOGI("timestamp", timestamp);

		for(uint16_t i = 0; i< 1000; ++i)
		{
			auto receivedData = reader.Read(1024);
			RTPPacket packet {seqNum++, timestamp, std::move(receivedData), false};
			multicastClient.Send(std::move(packet.TakePacket()));

			std::this_thread::sleep_for(std::chrono::milliseconds(6));

		}
	}
	catch(std::exception& e)
	{
		LOGE("Exception", e.what());
	}
}