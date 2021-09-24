#pragma once

#include <vector>
#include <cstdint>
#include <chrono>

class RTPPacket
{
	using TimePoint = std::chrono::high_resolution_clock::time_point;
 public:
	RTPPacket(uint16_t seqNum,
			  uint32_t timeStamp,
			  std::vector<uint8_t>&& payload,
			  bool endOfStream,
			  TimePoint& deliveryTime);

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

	TimePoint GetDeliveryTime() const
	{
		return m_deliveryTime;
	}

 private:
	std::vector<uint8_t> m_packet;
	TimePoint m_deliveryTime;
};