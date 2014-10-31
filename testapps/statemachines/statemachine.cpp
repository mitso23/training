/*
 * ipctest.cpp
 *
 *  Created on: Aug 4, 2013
 *      Author: dimitrios
 */

#include<libstatemachine/basicStateMachine.h>

// structure to hold event data passed into state machine
struct MotorData: public EventData
{
	int speed;
};

// the Motor state machine class
class Motor: public StateMachine
{
public:
	Motor() :
			StateMachine(ST_MAX_STATES)
	{
	}

	// external events taken by this state machine
	void Halt();
	void SetSpeed(MotorData*);
private:
	// state machine state functions
	void ST_Idle()
	{

	}
	void ST_Stop()
	{

	}
	void ST_Start(MotorData*)
	{

	}

	void ST_ChangeSpeed(MotorData*)
	{
		StateFunc ptr= reinterpret_cast<StateFunc>(&Motor::ST_Start);


	}

#if 0
// state map to define state function order
BEGIN_STATE_MAP
		STATE_MAP_ENTRY(ST_Idle)
		STATE_MAP_ENTRY(ST_Stop)
		STATE_MAP_ENTRY(ST_Start)
		STATE_MAP_ENTRY(ST_ChangeSpeed)
END_STATE_MAP
#endif

		// state enumeration order must match the order of state
		// method entries in the state map
		enum E_States
		{
			ST_IDLE = 0,
			ST_STOP,
			ST_START,
			ST_CHANGE_SPEED,
			ST_MAX_STATES
		};
	};

using namespace std;
int main(int argc, char* argv[])
{

#if 0
	// halt motor external event
	void Motor::Halt(void)
	{
	    // given the Halt event, transition to a new state based upon
	    // the current state of the state machine
	    BEGIN_TRANSITION_MAP                      // - Current State -
	        TRANSITION_MAP_ENTRY (EVENT_IGNORED)  // ST_Idle
	        TRANSITION_MAP_ENTRY (CANNOT_HAPPEN)  // ST_Stop
	        TRANSITION_MAP_ENTRY (ST_STOP)        // ST_Start
	        TRANSITION_MAP_ENTRY (ST_STOP)        // ST_ChangeSpeed
	    END_TRANSITION_MAP(NULL)
	}

	// set motor speed external event
	void Motor::SetSpeed(MotorData* pData)
	{
	    BEGIN_TRANSITION_MAP                      // - Current State -
	        TRANSITION_MAP_ENTRY (ST_START)       // ST_Idle
	        TRANSITION_MAP_ENTRY (CANNOT_HAPPEN)  // ST_Stop
	        TRANSITION_MAP_ENTRY (ST_CHANGE_SPEED)// ST_Start
	        TRANSITION_MAP_ENTRY (ST_CHANGE_SPEED)// ST_ChangeSpeed
	    END_TRANSITION_MAP(pData)
	}

	// state machine sits here when motor is not running
	void Motor::ST_Idle()
	{
	}

	// stop the motor
	void Motor::ST_Stop()
	{
	    // perform the stop motor processing here
	    // transition to ST_Idle via an internal event
	    InternalEvent(ST_IDLE);
	}

	// start the motor going
	void Motor::ST_Start(MotorData* pData)
	{
	    // set initial motor speed processing here
	}

	// changes the motor speed once the motor is moving
	void Motor::ST_ChangeSpeed(MotorData* pData)
	{
	    // perform the change motor speed to pData->speed here
	}
#endif
}
