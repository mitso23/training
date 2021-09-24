#include "IGMPListener.h"
#include "Logging.h"

#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <random>
#include <thread>
#include <map>
#include <string>
#include <signal.h>

#include <arpa/inet.h>
#include <net/ethernet.h>
#include <net/if.h>
#include <netpacket/packet.h>

IGMPListener::IGMPListener(std::string networkInterface, Callback&& callback)
	: m_networkInterface(networkInterface)
	, m_callback(callback)
{
	LOGD("");
}

void IGMPListener::Listen()
{
	m_fd = socket(AF_PACKET, SOCK_DGRAM, htons(ETHERTYPE_IP));
	if (m_fd < 0)
	{
		LOGE("Failed to open IGMP socket", strerror(errno));
		return;
	}

	struct sockaddr_ll ll;
	ll.sll_family = AF_PACKET;
	ll.sll_protocol = htons(ETHERTYPE_IP);
	ll.sll_ifindex = if_nametoindex(m_networkInterface.c_str());

	if (bind(m_fd, (struct sockaddr*)&ll, sizeof(ll)) < 0)
	{
		LOGE("Failed to bind to device", strerror(errno));
		return;
	}

	struct packet_mreq mreq = { 0 };
	mreq.mr_ifindex = if_nametoindex(m_networkInterface.c_str());;
	mreq.mr_type = PACKET_MR_PROMISC;
	if (setsockopt(m_fd, SOL_PACKET, PACKET_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0)
	{
		LOGE("Failed to set promiscuous mode", strerror(errno));
	}

	uint8_t buf[256];
	LOGE("Start Listening");

	while (1)
	{
		struct sockaddr src;
		socklen_t src_len = sizeof(src);
		int len = recvfrom(m_fd, buf, 256, 0, &src, &src_len);

		if (len < 0)
		{
			LOGE("Failed to receive from IGMP socket");
			close(m_fd);
			return;
		}

		if ((buf[0] >> 4) != 4)
		{
			// Not IPv4
			LOGE("Not IPV4");
			continue;
		}

		if (buf[9] != IPPROTO_IGMP)
		{
			continue;
		}

		LOGD("IGMP");

		uint8_t* payload = buf + (buf[0] & 0x0F) * 4;
		switch(payload[0])
		{
		case 0x22: // IGMPv3 Membership Report Message
			m_handleIGMP3Message(payload);
			break;
		default: LOGE("Unhandled IGMP message type: ", payload[0]);
		}
	}
}

void IGMPListener::m_handleIGMP3Message(uint8_t* msg)
{
	int numRecords = (msg[6] << 8) | msg[7];
	msg += 8;
	for (int i = 0; i < numRecords; i++)
	{
		msg += m_handleIGMPRecord(msg);
	}
}

int IGMPListener::m_handleIGMPRecord(uint8_t* record)
{
	int auxDataLen = record[1];
	int numSources = (record[2] << 8) | record[3];
	char addr[64];
	snprintf(addr, 64, "%hhu.%hhu.%hhu.%hhu", record[4], record[5], record[6], record[7]);

	std::string multicastAddress(addr);
	LOGI("Concerning multicast address: ", addr, "record[0]", static_cast<unsigned>(record[0]), "auxLen", auxDataLen);

	if (m_callback && record[0] == 4)
	{
		m_callback(multicastAddress);
	}
	return 8 + numSources * 4 + auxDataLen * 4;
}