#pragma once
#include "IGMPListener.h"
#include "MulticastClient.h"
#include <iostream>

class RTPStreaming
{

 public:
	RTPStreaming(std::string interfaceAddress, uint16_t port);

 private:
	void m_StreamRequested(std::string&& multicastAddress);
 private:
	IGMPListener m_igmpListener;
	std::string m_interfaceAddress;
	uint16_t m_port;
	std::string m_multicastAddress;
};
