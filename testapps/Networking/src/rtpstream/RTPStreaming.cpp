#include "RTPStreaming.h"
#include "Logging.h"
#include "FileReader.h"
#include "TSPacket.h"
#include "RTPHeader.h"

#include <functional>
#include <thread>
#include <chrono>

RTPStreaming::RTPStreaming(std::string interfaceAddress, uint16_t port)
	: m_interfaceAddress(std::move(interfaceAddress))
	, m_port(port)
	, m_packets(1000)
	, m_terminate(false)
	, m_igmpListener(interfaceAddress, std::bind(&RTPStreaming::m_StreamRequested,
		 										     this, std::placeholders::_1))
{
	LOGD("");
	m_igmpListener.Listen();
	m_terminate = true;

	LOGD("Waiting for the thread to terminate");

	m_packets.Clear();
	if (m_thread.joinable())
	{
		m_thread.join();
	}

	LOGD("Terminated");
}

void RTPStreaming::m_StreamingThread()
{
	LOGD("Thread started");

	sched_param p;
	p.__sched_priority = 19;
	pthread_setschedparam(pthread_self(), SCHED_FIFO, &p);

	MulticastClient multicastClient(m_interfaceAddress, std::move(m_multicastAddress), m_port);

	while (!m_terminate.load())
	{
		auto packet = m_packets.Pop();
		auto deliveryTime = packet.GetDeliveryTime();

		//LOGE("sending packet sec", deliveryTime.tv_sec, " nsec: ", deliveryTime.tv_nsec);
		std::this_thread::sleep_until(deliveryTime);
		multicastClient.Send(std::move(packet.TakePacket()));
	}

	LOGE("Streaming terminated");
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
		m_thread = std::move(std::thread{&RTPStreaming::m_StreamingThread, this});
	}

	try
	{
		FileReader reader("/home/dimitrios/Videos/boa_clear.ts");

		const unsigned int packetSize = (1500 / 188) * 188;
		const double bitRate = 5000000;
		std::chrono::nanoseconds interval {static_cast<uint32_t>((packetSize * 8UL * 1000UL * 1000UL * 1000UL) / bitRate)};
		auto deliveryTime = std::chrono::high_resolution_clock::now();

		LOGD("interval", interval.count());

		for(uint16_t i = 0; i< 100000; ++i)
		{
			auto timestamp = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
			timestamp*= 90000;
			LOGI("timestamp", timestamp);

			auto receivedData = reader.Read(packetSize);
			deliveryTime+= interval;
			RTPPacket
				packet{ seqNum++, static_cast<uint32_t>(timestamp), std::move(receivedData), false, deliveryTime };

			//LOGE("Adding packet sec", deliveryTime.tv_sec, " nsec: ", deliveryTime.tv_nsec);
			m_packets.Push(std::move(packet));

		}
	}
	catch(std::exception& e)
	{
		LOGE("Exception", e.what());
	}
}