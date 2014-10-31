#include <libthread/Thread.h>
#include <stdlib.h>
/**
 * Thread can be set in an non joinable state, which means that the OS will clean up
 * after a thread terminates otherwise the thread is in a zombie state like a process
 */
void Pthread::setDetachState(int attr)
{
	pthread_attr_setdetachstate(&m_threadAttr, attr);
}

/**
 * Normally a thread can be canceled only if it reaches a certain cancellation point
 * set PTHREAD_CANCEL_ASYNCHRONOUS in order to cancel at any point
 * This must be called in a thread context
 */
void Pthread::setCancelType(int attr)
{
	pthread_setcanceltype(attr, NULL);
}

pthread_t Pthread::getId() const
{
	return m_threadId;
}

void* Pthread::join()
{
	void* result = (void*) malloc(sizeof(void*));
	pthread_join(m_threadId, &result);

	return result;
}

void Pthread::cancel()
{
	pthread_cancel(m_threadId);
}

void Pthread::setCancelationPoint()
{
	pthread_testcancel();
}

void Pthread::setThreadSpecificData(void* data)
{
	pthread_setspecific(m_threadDataKey, data);
}

void* Pthread::getThreadSpecificData()
{
	return pthread_getspecific(m_threadDataKey);
}
