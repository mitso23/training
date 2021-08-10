#include "MulticastClient.h"
#include "Logging.h"

#include <string.h>
#include <iostream>
using namespace std;

MulticastClient::MulticastClient(std::string interfaceAddress, std::string mutlicastAddress, uint16_t port)
	: m_multicastAddress(std::move(mutlicastAddress))
	, m_interfaceAddress(std::move(interfaceAddress))
	, m_port(port)
{

	LOGI("interface", m_interfaceAddress, "multicast", m_multicastAddress, "port", port);

	/* Create a datagram socket on which to send. */
	m_fd = socket(AF_INET, SOCK_DGRAM, 0);
	if (m_fd < 0)
	{
		LOGE("Opening datagram socket error");
		throw 1;
	}
	else
	{
		LOGD("Opening the datagram socket...OK.\n");
	}

	memset((char*)&m_destSockAddr, 0, sizeof(m_destSockAddr));
	m_destSockAddr.sin_family = AF_INET;
	m_destSockAddr.sin_addr.s_addr = inet_addr(m_multicastAddress.c_str());
	//m_destSockAddr.sin_addr.s_addr = inet_addr("224.0.0.21");
	m_destSockAddr.sin_port = htons(port);

	//Disable loopback so you do not receive your own datagrams.
#if 0
	{
		 char loopch = 0;
		 if(setsockopt(m_fd, IPPROTO_IP, IP_MULTICAST_LOOP, (char *)&loopch, sizeof(loopch)) < 0)
		 {
			 perror("Setting IP_MULTICAST_LOOP error");
			 close(m_fd);
			 exit(1);
		 }
		 else
		 {
			 printf("Disabling the loopback...OK.\n");
		 }
	 }
#endif

	/* Set local interface for outbound multicast datagrams. */
	unsigned int ifi = if_nametoindex(m_interfaceAddress.c_str());
	if (ifi == 0)
	{
		LOGE("failed to get interface index: ", m_interfaceAddress);
		throw 1;
	}

	struct ip_mreqn r;
	r.imr_multiaddr.s_addr = inet_addr(m_multicastAddress.c_str());
	r.imr_address.s_addr = INADDR_ANY;
	r.imr_ifindex = ifi;

	if (setsockopt(m_fd, SOL_IP, IP_MULTICAST_IF, &r, sizeof(r)) != 0)
	{
		LOGE("Error setting multicast interface");
		throw 1;
	}
}

int MulticastClient::Send(std::vector<uint8_t>&& data)
{
	LOGD("data size", data.size());

	auto result = sendto(m_fd,
		data.data(),
		data.size(),
		0,
		(struct sockaddr*)&m_destSockAddr,
		sizeof(m_destSockAddr));

	if (result < 0)
	{
		LOGE("failed to write", result);
	}
	else
	{
		LOGI("wrote", result , "bytes");
	}

	return result;
}