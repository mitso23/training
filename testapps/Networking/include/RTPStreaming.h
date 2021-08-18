#pragma once

#include "IGMPListener.h"
#include "MulticastClient.h"
#include "RTPHeader.h"
#include "BlockingQueue.h"

#include <iostream>
#include <list>
#include <mutex>
#include <thread>
#include <atomic>

class RTPStreaming
{

 public:
	RTPStreaming(std::string interfaceAddress, uint16_t port);

 private:
	void m_StreamRequested(std::string&& multicastAddress);
	void m_StreamingThread();
 private:
	IGMPListener m_igmpListener;
	std::string m_interfaceAddress;
	uint16_t m_port;
	std::string m_multicastAddress;
	FixedBlockingQueue<RTPPacket> m_packets;
	std::thread m_thread;
	std::atomic<bool> m_terminate;
};
