#include "RTPStreaming.h"
#include <functional>

RTPStreaming::RTPStreaming(std::string interfaceAddress, uint16_t port)
	: m_igmpListener(interfaceAddress, std::bind(&RTPStreaming::m_StreamRequested, this, std::placeholders::_1))
{

}