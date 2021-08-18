#pragma once

#include <vector>
#include <cstdint>
#include <time.h>

class RTPPacket
{
 public:
	RTPPacket(uint16_t seqNum,
			  uint32_t timeStamp,
			  std::vector<uint8_t>&& payload,
			  bool endOfStream,
			  struct timespec& deliveryTime);

	std::vector<uint8_t>&& TakePacket()
	{
		return std::move(m_packet);
	}

	RTPPacket(const RTPPacket&) = delete;
	RTPPacket& operator = (const RTPPacket&) = delete;

	RTPPacket(RTPPacket&& packet)
	{
		m_packet = std::move(packet.TakePacket());
		m_deliveryTime = packet.GetDeliveryTime();
	}

	struct timespec GetDeliveryTime() const
	{
		return m_deliveryTime;
	}

 private:
	std::vector<uint8_t> m_packet;
	struct timespec m_deliveryTime;
};