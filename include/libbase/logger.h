#ifndef LOGGER_GUARD_H
#define LOGGER_GUARD_H

#include <string>
#include <iostream>

typedef enum
{
	LOG_LEVEL_ERROR= 4,
	LOG_LEVEL_WARN= 3,
	LOG_LEVEL_INFO= 2,
	LOG_LEVEL_DEBUG1= 1,
	LOG_LEVEL_TRACE= 0

}log_level_t;

const log_level_t glogLevel= LOG_LEVEL_INFO;

class Logger
{

public:
	Logger(std::string& className):
		m_className(className)
	{

	}

	Logger()
	{

	}

template<typename T>
void logError(T t, log_level_t level)
{
	if (level >= glogLevel)
		std::cerr << m_className << ": "<< t << '\n';
}
private:
	std::string m_className;
};


#define DECLARE_LOGGER(Name) \
	private: \
		Logger logger;

#ifdef DEBUG
#define LOG_CLASS_ERROR(T) \
		logger.logError(T, LOG_LEVEL_ERROR);

#define LOG_CLASS_WARN(T) \
		logger.logError(T, LOG_LEVEL_WARN);

#define LOG_CLASS_INFO(T) \
		logger.logError(T, LOG_LEVEL_INFO);

#define LOG_CLASS_DEBUG1(T) \
		logger.logError(T, LOG_LEVEL_DEBUG1);

#define LOG_CLASS_TRACE(T) \
		logger.logError(T, LOG_LEVEL_TRACE);

#define LOG_GLOBAL_ERROR(T) \
		if (LOG_LEVEL_ERROR >= glogLevel) \
			std::cerr << T << '\n';

#define LOG_GLOBAL_WARN(T) \
		if (LOG_LEVEL_WARN >= glogLevel) \
				std::cerr << T << '\n';

#define LOG_GLOBAL_INFO(T) \
		if (LOG_LEVEL_INFO >= glogLevel) \
				std::cerr << T << '\n';
#define LOG_GLOBAL_DEBUG1(T) \
		if (LOG_LEVEL_DEBUG1 >= glogLevel) \
				std::cerr << T << '\n';

#define LOG_GLOBAL_TRACE(T) \
		if (LOG_LEVEL_TRACE >= glogLevel) \
				std::cerr << T << '\n';
#endif



#endif
