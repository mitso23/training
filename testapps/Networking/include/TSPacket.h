#pragma once
#include <array>
#include <bitset>

class TSPacket
{
 public:
	TSPacket() = default;

	bool GetPUSI()
	{
		return (m_data[1] & 0x40);
	}

	inline uint16_t GetPID()
	{
		return ((m_data[1] & 0x1FU) << 8) | m_data[2];
	}

	inline std::bitset<4> ParseAdaptaionControl()
	{
		unsigned int adaptationField = m_data[3] >> 4;
		return std::bitset<4> { adaptationField };
	}

	//@precondition clients responsibility to make sure adaptation is present
	inline bool IsPCRPResent()
	{
		if (m_data[4] != 0 && m_data[5] & 0x10)
		{
			return true;
		}

		return false;
	}

	//@precondition clients responsibility to make sure payload is present
	inline uint8_t GetContinuityCounter()
	{
		return m_data[3] & 0x0F;
	}

	inline uint64_t GetPCR()
	{
		uint8_t* start = &m_data[6];

		uint64_t value = (static_cast<uint64_t>(start[0]) << 25) |
						 (start[1] << 17) |
						 (start[2] << 9)  |
						 (start[3] << 1) |
						 (start[4] >> 7);
		return value;
	}

 private:
	std::array<uint8_t, 188> m_data;
};