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
		struct timespec deliveryTime = packet.GetDeliveryTime();

		//LOGE("sending packet sec", deliveryTime.tv_sec, " nsec: ", deliveryTime.tv_nsec);
		clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &deliveryTime, NULL);
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
		double intervalSec = (packetSize * 8) / bitRate;
		LOGD("intervalSec", intervalSec);

		struct timespec deliveryTime;
		if (clock_gettime(CLOCK_MONOTONIC, &deliveryTime) != 0)
		{
			LOGE("Failed to get CLOCK_MONOTONIC");
			return;
		}

		for(uint16_t i = 0; i< 100000; ++i)
		{
			struct timespec tp;

			if (clock_gettime(CLOCK_MONOTONIC, &tp) != 0)
			{
				LOGE("Failed to get CLOCK_MONOTONIC");
				return;
			}

			uint32_t timestamp =  static_cast<uint32_t>((tp.tv_sec * 90000LL) + ((tp.tv_nsec * 9LL) / 100000LL));
			LOGI("timestamp", timestamp);

			auto begin = std::chrono::steady_clock::now();
			auto receivedData = reader.Read(packetSize);

			deliveryTime.tv_nsec+= intervalSec * 1000ULL * 1000ULL * 1000ULL;
			while(deliveryTime.tv_nsec > 999999999)
			{
				deliveryTime.tv_sec+=1;
				deliveryTime.tv_nsec-= 1000*1000*1000;
			}

			RTPPacket packet {seqNum++, timestamp, std::move(receivedData), false, deliveryTime};

			//LOGE("Adding packet sec", deliveryTime.tv_sec, " nsec: ", deliveryTime.tv_nsec);
			m_packets.Push(std::move(packet));

			auto end = std::chrono::steady_clock::now();
			auto durationNs = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

			//abort();
		}
	}
	catch(std::exception& e)
	{
		LOGE("Exception", e.what());
	}
}