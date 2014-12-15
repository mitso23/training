/*
 * basicStateMachine.h
 *
 *  Created on: Sep 29, 2013
 *      Author: dimitrios
 */

#ifndef BASICSTATEMACHINE_H_
#define BASICSTATEMACHINE_H_
#include<stdio.h>
#include <iostream>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

class EventData
{
public:
	virtual ~EventData()
	{
	};
};

struct StateStruct;

// base class for state machines
class StateMachine
{
public:

	StateMachine(int maxStates);

	virtual ~StateMachine()
	{

	}

protected:

	void externalEvent(unsigned char, std::shared_ptr<EventData>);

	void internalEvent(unsigned char, std::shared_ptr<EventData>);

	virtual const StateStruct* GetStateMap() = 0;

private:
	void StateEngine(void);


protected:
	unsigned char m_currentState;

	enum
	{
		EVENT_IGNORED = 0xFE, CANNOT_HAPPEN
	};

private:
	const int m_maxStates;
	bool m_eventGenerated;
	std::shared_ptr<EventData> m_eventData;

};

typedef void (StateMachine::*StateFunc)(std::shared_ptr<EventData>);
typedef boost::function<bool (void)> guardFunct;

struct StateStruct
{
	StateFunc pStateFunc;
};


StateMachine::StateMachine(int maxStates) :
	m_currentState(0),
    m_maxStates(maxStates),
    m_eventGenerated(false),
    m_eventData()
{
}

// generates an external event. called once per external event
// to start the state machine executing
void StateMachine::externalEvent(unsigned char newState,
                                 std::shared_ptr<EventData> pData)
{
	if (newState > m_maxStates)
	{
		// just delete the event data, if any
		if (pData)
		{
			std::cout << "Event has been ignored deleting data: " << std::endl;
		}
	}

	// if we are supposed to ignore this event
	if (newState == EVENT_IGNORED)
	{
		// just delete the event data, if any
		if (pData)
		{
			std::cout << "Event has been ignored deleting data: " << std::endl;
		}
	}
	else if (newState == CANNOT_HAPPEN)
	{
		// just delete the event data, if any
		if (pData)
		{
			std::cout << "Impossible transition deleting data: " << std::endl;
		}
	}
	else
	{
		// generate the event and execute the state engine
		internalEvent(newState, pData);
		StateEngine();
	}
}

// generates an internal event. called from within a state
// function to transition to a new state
void StateMachine::internalEvent(unsigned char newState,
				std::shared_ptr<EventData> pData)
{
    m_eventData = pData;
    m_eventGenerated = true;
    m_currentState = newState;
}

// the state engine executes the state machine states
void StateMachine::StateEngine(void)
{
	// TBD - lock semaphore here
	// while events are being generated keep executing states
	while (m_eventGenerated)
	{
		m_eventGenerated = false;  // event used up, reset flag

		// execute the state passing in event data, if any
		//this can result in another state change as well
		const StateStruct* pStateMap = GetStateMap();
		(this->*pStateMap[m_currentState].pStateFunc)(m_eventData);
	}
	// TBD - unlock semaphore here
}

#define BEGIN_STATE_MAP \
public:\
const StateStruct* GetStateMap() {\
    static const StateStruct StateMap[] = {

#define STATE_MAP_ENTRY(entry)\
    { reinterpret_cast<StateFunc>(entry) },

#define END_STATE_MAP \
    }; \
    return &StateMap[0]; }

#define BEGIN_TRANSITION_MAP \
    static const unsigned char TRANSITIONS[] = {\

#define TRANSITION_MAP_ENTRY(entry)\
    entry,

#define END_TRANSITION_MAP(data, guard) \
    0 }; \
    if (guard()) \
	{ \
		externalEvent(TRANSITIONS[m_currentState], data);\
	}
#endif /* BASICSTATEMACHINE_H_ */


