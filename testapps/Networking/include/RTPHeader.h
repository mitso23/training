#pragma once

#include <vector>
#include <cstdint>

class RTPPacket
{
 public:
	RTPPacket(uint16_t seqNum, uint32_t timeStamp, std::vector<uint8_t>&& payload, bool endOfStream);

	std::vector<uint8_t>&& TakePacket()
	{
		return std::move(m_packet);
	}

 private:
	std::vector<uint8_t> m_packet;
};