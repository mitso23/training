#pragma once

#include <string>
#include <vector>
#include <arpa/inet.h>
#include <net/ethernet.h>
#include <net/if.h>
#include <netpacket/packet.h>

class MulticastClient
{
 public:
	MulticastClient(std::string interfaceAddress, std::string mutlicastAddress, uint16_t port);

	int Send(std::vector<uint8_t>&& data);

 public:
	int m_fd = -1;
	struct sockaddr_in m_destSockAddr;
	std::string m_multicastAddress;
	std::string m_interfaceAddress;
	uint16_t m_port;
};
