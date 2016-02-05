/******************************************************************************/
/*!
\file	FSMState.h
\author Tng Kah Wei
\brief
State class designed for use with NPC Finite State Machine class.
*/
/******************************************************************************/
#ifndef FSM_STATE_H
#define FSM_STATE_H

#include "NPC.h"

/******************************************************************************/
/*!
		Class FSMState:
\brief	A Finite State Machine State meant for use with the NPC Finite State
		Machine class.

		This class will work with being a Base NPC State or a Nested Child
		State. This is determined by an overloaded Init() which takes in an
		NPC* or FSMState* as a parent.

		To use this class, create inherited specialized versions of this
		class and customize them to your will. Simply override the Init(),
		Update() and Exit() functions to your liking.

		m_FSMOwner allows you to modify and interface with the NPC Finite
		State Machine only if the inherited states are declared as friend
		classes.

		m_stateParent, m_currentState and m_previousState are hidden so as 
		to abstract the data away from the user.
*/
/******************************************************************************/
class FSMState
{
public:
	static const float S_MAX_STATE_TIME;

private:
	// For Nested States
	FSMState* m_stateParent;
	FSMState* m_currentState;
	FSMState* m_previousState;
	
protected:
	string m_stateName;
	// Pointer to the NPC being controlled by this state. Use this to control the NPC.
	NPC* m_FSMOwner;
	
	float m_stateTimer;

public:
	FSMState();
	virtual ~FSMState() = 0;

	// Initialization function for Base NPC States
	virtual void Init(NPC* FSMOwner);
	// Initialization function for Nested States
	virtual void Init(FSMState* stateOwner);
	virtual void Update(double dt);
	virtual void Exit(void);
	// Function to get the name of this state
	virtual string GetStateName(void);						// Current State - Child State
	virtual string GetThisStateName(void);					// Current State
	virtual string GetChildStateName(void);					// Child State

protected:
	// Function to change the state of the parent. Automatically slates this state for Exit() and deletion in the new state's Init().
	void changeState(FSMState* state);
	// Function to check if the current state is a nested state or a base NPC state.
	bool isNestedState(void) const;
	// Use this function to set the current child state. Automatically calls the state's Init() and destroys the previous child state.
	void setCurrentState(FSMState* state);
};

#endif