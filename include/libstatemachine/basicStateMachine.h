/*
 * basicStateMachine.h
 *
 *  Created on: Sep 29, 2013
 *      Author: dimitrios
 */

#ifndef BASICSTATEMACHINE_H_
#define BASICSTATEMACHINE_H_
#include<stdio.h>

class EventData
{
public:
	virtual ~EventData()
	{
	}
	;
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
	enum
	{
		EVENT_IGNORED = 0xFE, CANNOT_HAPPEN
	};
	unsigned char currentState;
	void ExternalEvent(unsigned char, EventData* = NULL);
	void InternalEvent(unsigned char, EventData* = NULL);
	virtual const StateStruct* GetStateMap() = 0;


private:
	const int _maxStates;
	bool _eventGenerated;
	EventData* _pEventData;
	void StateEngine(void);
};

typedef void (StateMachine::*StateFunc)(EventData *);

struct StateStruct
{
	StateFunc pStateFunc;
};

StateMachine::StateMachine(int maxStates) :
    _maxStates(maxStates),
    currentState(0),
    _eventGenerated(false),
    _pEventData(NULL)
{
}

// generates an external event. called once per external event
// to start the state machine executing
void StateMachine::ExternalEvent(unsigned char newState,
                                 EventData* pData)
{
    // if we are supposed to ignore this event
    if (newState == EVENT_IGNORED) {
        // just delete the event data, if any
        if (pData)
            delete pData;
    }
    else {
        // generate the event and execute the state engine
        InternalEvent(newState, pData);
        StateEngine();
    }
}

// generates an internal event. called from within a state
// function to transition to a new state
void StateMachine::InternalEvent(unsigned char newState,
                                 EventData* pData)
{
    _pEventData = pData;
    _eventGenerated = true;
    currentState = newState;
}

// the state engine executes the state machine states
void StateMachine::StateEngine(void)
{
    EventData* pDataTemp = NULL;

    // TBD - lock semaphore here
    // while events are being generated keep executing states
    while (_eventGenerated) {
        pDataTemp = _pEventData;  // copy of event data pointer
        _pEventData = NULL;       // event data used up, reset ptr
        _eventGenerated = false;  // event used up, reset flag

        // execute the state passing in event data, if any
        const StateStruct* pStateMap = GetStateMap();
        (this->*pStateMap[currentState].pStateFunc)(pDataTemp);

        // if event data was used, then delete it
        if (pDataTemp) {
            delete pDataTemp;
            pDataTemp = NULL;
        }
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
    { reinterpret_cast<StateFunc>(NULL) }\
    }; \
    return &StateMap[0]; }

#define BEGIN_TRANSITION_MAP \
    static const unsigned char TRANSITIONS[] = {\

#define TRANSITION_MAP_ENTRY(entry)\
    entry,

#define END_TRANSITION_MAP(data) \
    0 };\
    ExternalEvent(TRANSITIONS[currentState], data);

#endif /* BASICSTATEMACHINE_H_ */
