#include "RTPHeader.h"
#include "Logging.h"

RTPPacket::RTPPacket(uint16_t seqNum, uint32_t timeStamp, std::vector<uint8_t>&& payload, bool endOfStream, struct timespec& deliveryTime)
{
	m_packet.resize(payload.size() + sizeof(seqNum) + sizeof(timeStamp) + 4 + 2);

	//version 0x2, no padding, no extension
	m_packet[0] = 0x80;

	//payload type and end of stream
	m_packet[1] = 33;
	if (endOfStream)
	{
		m_packet[1]|= 0x80;
	}

	//sequence number
	m_packet[2] = (seqNum >> 8);
	m_packet[3] = seqNum & 0x00ff;

	//timestamp
	m_packet[4] = timeStamp >> 24;
	m_packet[5] = timeStamp >> 16;
	m_packet[6] = timeStamp >> 8;
	m_packet[7] = timeStamp & 0x000000ff;

	//SSRC
	for(unsigned int i=0U; i< 4; ++i)
	{
		m_packet[8 + i] = i;
	}

	std::copy(payload.begin(), payload.end(), &m_packet[12]);

	m_deliveryTime = deliveryTime;

	LOGD("Packet size", m_packet.size());

}
