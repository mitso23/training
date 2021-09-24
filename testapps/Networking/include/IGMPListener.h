#pragma once

#include <string>
#include <functional>

class IGMPListener
{
 public:
	using Callback = std::function<void (std::string)>;

	IGMPListener(std::string networkInterface, Callback&& callback);

	void Listen();

 private:
	void m_handleIGMP3Message(uint8_t* msg);
	int m_handleIGMPRecord(uint8_t* record);

 private:
	std::string m_networkInterface;
	int m_fd = -1;
	Callback m_callback;

};