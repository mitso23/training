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
		externalEvent(ST_IDLE, boost::shared_ptr<EventData>());
	}

	// external events taken by this state machine
	void halt();

	void setSpeed(MotorData*);

private:
	// state machine state objects
	void ST_Idle();

	void ST_Stop();

	void ST_Start(MotorData*);


	void ST_ChangeSpeed(MotorData*);


// state map to define Moter states
BEGIN_STATE_MAP
		STATE_MAP_ENTRY(&Motor::ST_Idle)
		STATE_MAP_ENTRY(&Motor::ST_Stop)
		STATE_MAP_ENTRY(&Motor::ST_Start)
		STATE_MAP_ENTRY(&Motor::ST_ChangeSpeed)
END_STATE_MAP


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

	// halt motor external event
	void Motor::halt(void)
	{
	    // given the Halt event, transition to a new state based upon
	    // the current state of the state machine
	    BEGIN_TRANSITION_MAP                      // - Current State -
	        TRANSITION_MAP_ENTRY (EVENT_IGNORED)  // ST_Idle
	        TRANSITION_MAP_ENTRY (CANNOT_HAPPEN)  // ST_Stop
	        TRANSITION_MAP_ENTRY (ST_STOP)        // ST_Start
	        TRANSITION_MAP_ENTRY (ST_STOP)        // ST_ChangeSpeed
	    END_TRANSITION_MAP(boost::shared_ptr<EventData>(), [] () { return true; } )
	}

	// set motor speed external event
	void Motor::setSpeed(MotorData* pData)
	{
	    BEGIN_TRANSITION_MAP                      // - Current State -
	        TRANSITION_MAP_ENTRY (ST_START)       // ST_Idle
	        TRANSITION_MAP_ENTRY (CANNOT_HAPPEN)  // ST_Stop
	        TRANSITION_MAP_ENTRY (ST_CHANGE_SPEED)// ST_Start
	        TRANSITION_MAP_ENTRY (ST_CHANGE_SPEED)// ST_ChangeSpeed
	    END_TRANSITION_MAP(boost::shared_ptr<EventData>(), [] () { return true; })
	}

	// state machine sits here when motor is not running
	void Motor::ST_Idle()
	{
		std::cout << "We are in the IDLE state " << std::endl;
	}

	// stop the motor
	void Motor::ST_Stop()
	{
	    // perform the stop motor processing here
	    // transition to ST_Idle via an internal event
		std::cout << "We are in the STOP state " << std::endl;
	    internalEvent(ST_IDLE, boost::shared_ptr<EventData>());
	}

	// start the motor going
	void Motor::ST_Start(MotorData* pData)
	{
		std::cout << "We are in the START state " << std::endl;
	    // set initial motor speed processing here
	}

	// changes the motor speed once the motor is moving
	void Motor::ST_ChangeSpeed(MotorData* pData)
	{
		std::cout << "We are in the CHANGE SPEED state " << std::endl;
	    // perform the change motor speed to pData->speed here
	}

int main(int argc, char* argv[])
{
	std::cout << "Starting the motor" << std::endl;

	Motor motor;
	MotorData* data= new MotorData();
	data->speed= 1;
	motor.setSpeed(data);
	data->speed= 2;
	motor.setSpeed(data);
	motor.halt();


}
