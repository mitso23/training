#pragma once

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

using namespace std;


int handleIGMP3Record(const uint8_t* record)
{
	int auxDataLen = record[1];
	int numSources = (record[2] << 8) | record[3];
	char addr[64];
	snprintf(addr, 64, "%hhu.%hhu.%hhu.%hhu", record[4], record[5], record[6], record[7]);
	string multicastAddress(addr);
	printf("Concerning multicast address %s\n", addr);

	auto* multicastServer = MulticastServer::Create(std::string{}, multicastAddress, 8433,  -1);
	std::vector<uint8_t> packet(6000);

	for(int i=0; i< 10000; ++i)
	{
		auto result = sendto(multicastServer->sd,
			packet.data(),
			packet.size(),
			0,
			(struct sockaddr*)&multicastServer->destSock,
			sizeof(multicastServer->destSock));

		if (result < 0)
		{
			perror("Sending datagram message error");
			std::abort();
		}
	}

	return 8 + numSources * 4 + auxDataLen * 4;
}

void handleIGMP3(const uint8_t* msg)
{
	int numRecords = (msg[6] << 8) | msg[7];
	msg += 8;
	for (int i = 0; i < numRecords; i++)
	{
		msg += handleIGMP3Record(msg);
	}
}

#define MY_INTERFACE 5

void IGMPLoop()
{
	int sockfd = socket(AF_PACKET, SOCK_DGRAM, htons(ETHERTYPE_IP));
	if (sockfd < 0)
	{
		printf("Failed to open IGMP socket\n");
		printf("%s\n", strerror(errno));
		return;
	}

	struct sockaddr_ll ll;
	ll.sll_family = AF_PACKET;
	ll.sll_protocol = htons(ETHERTYPE_IP);
	ll.sll_ifindex = MY_INTERFACE;

	if (bind(sockfd, (struct sockaddr*)&ll, sizeof(ll)) < 0)
	{
		printf("Failed to bind to device\n");
		printf("%s\n", strerror(errno));
	}

	struct packet_mreq mreq = { 0 };
	mreq.mr_ifindex = MY_INTERFACE;
	mreq.mr_type = PACKET_MR_PROMISC;
	if (setsockopt(sockfd, SOL_PACKET, PACKET_ADD_MEMBERSHIP, &mreq, sizeof(mreq)) < 0)
	{
		printf("Failed to set promiscuous mode\n");
		printf("%s\n", strerror(errno));
	}

	uint8_t buf[256];
	while (1)
	{
		struct sockaddr src;
		socklen_t src_len = sizeof(src);
		int len = recvfrom(sockfd, buf, 256, 0, &src, &src_len);

		if (len < 0)
		{
			printf("Failed to receive from IGMP socket");
			close(sockfd);
			return;
		}
		if ((buf[0] >> 4) != 4)
		{
			// Not IPv4
			std::cout << "Not IPV4" << std::endl;
			continue;
		}
		if (buf[9] != IPPROTO_IGMP)
		{
			continue;
		}
		printf("IGMP\n");
		uint8_t* payload = buf + (buf[0] & 0x0F) * 4;
		switch(payload[0])
		{
		case 0x22: // IGMPv3 Membership Report Message
			handleIGMP3(payload);
			break;
		default: printf("Unhandled IGMP message type 0x%02X\n", payload[0]);
		}
	}
}
