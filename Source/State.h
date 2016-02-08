/******************************************************************************/
/*!
\file	FSMState.h
\author Tng Kah Wei
\brief
State class designed for use with FiniteStateMachine Finite State Machine class.
*/
/******************************************************************************/
#ifndef SM_STATE_H
#define SM_STATE_H

#include "FiniteStateMachine.h"

/******************************************************************************/
/*!
		Class State:
\brief	A Finite State Machine State meant for use with the FiniteStateMachine class.

		This class will work with being a Base FiniteStateMachine State or a Nested Child
		State. This is determined by an overloaded Init() which takes in an
		FiniteStateMachine* or FSMState* as a parent.

		To use this class, create inherited specialized versions of this
		class and customize them to your will. Simply override the Init(),
		Update() and Exit() functions to your liking.

		m_FSMOwner allows you to modify and interface with the FiniteStateMachine Finite
		State Machine only if the inherited states are declared as friend
		classes.

		m_stateParent, m_currentState and m_previousState are hidden so as 
		to abstract the data away from the user.
*/
/******************************************************************************/
namespace StateMachine
{
	class State
	{
	public:
		static const float S_MAX_STATE_TIME;

	private:
		// For Nested States
		State* m_stateParent;
		State* m_currentState;
		State* m_previousState;

	protected:
		string m_stateName;
		// Pointer to the FiniteStateMachine being controlled by this state. Use this to control the FiniteStateMachine.
		FiniteStateMachine* m_FSMOwner;

	public:
		State();
		virtual ~State() = 0;

		// Initialization function for Base FiniteStateMachine States
		virtual void Init(FiniteStateMachine* SMOwner);
		// Initialization function for Nested States
		virtual void Init(State* stateOwner);
		virtual void Update(double dt);
		virtual void Exit(void);
		// Function to get the name of this state
		virtual string GetStateName(void);						// Current State - Child State
		virtual string GetThisStateName(void);					// Current State
		virtual string GetChildStateName(void);					// Child State

	protected:
		// Function to change the state of the parent. Automatically slates this state for Exit() and deletion in the new state's Init().
		void changeState(State* state);
		// Function to check if the current state is a nested state or a base FiniteStateMachine state.
		bool isNestedState(void) const;
		// Use this function to set the current child state. Automatically calls the state's Init() and destroys the previous child state.
		void setCurrentState(State* state);
	};
}
#endif