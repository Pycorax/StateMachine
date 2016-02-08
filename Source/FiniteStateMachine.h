/******************************************************************************/
/*!
\file	NPC.h
\author Tng Kah Wei
\brief
NPC Finite State Machine interface class to turn any object into a Finite
State Machine.
*/
/******************************************************************************/
#ifndef FINITE_STATE_MACHINE_H
#define FINITE_STATE_MACHINE_H

// STL Includes
#include <string>

// Using Directives
using std::string;

/******************************************************************************/
/*!
		Class FiniteStateMachine:
\brief	Finite State Machine interface class meant to provide Finite 
		State Machine functionality to inherited classes.

		To use this class, simply inherit from it and define FSMStates for
		it. Said FSMStates should be declared as friend classes of the
		NPC.

		To set the starting state, use setCurrentState() to specify the
		state to use. setCurrentState() will automatically call the Init()
		of the state.

		m_currentState and m_previousState are hidden so as to abstract
		the data away from the user.
*/
/******************************************************************************/
namespace StateMachine
{
	/******************************************************************************/
	/*!
			Class FiniteStateMachine:
	\brief	Finite State Machine interface class meant to provide Finite
			State Machine functionality to inherited classes.

			To use this class, simply inherit from it and define FSMStates for
			it. Said FSMStates should be declared as friend classes of the
			NPC.

			To set the starting state, use setCurrentState() to specify the
			state to use. setCurrentState() will automatically call the Init()
			of the state.

			m_currentState and m_previousState are hidden so as to abstract
			the data away from the user.
	*/
	/******************************************************************************/
	class FiniteStateMachine
	{
		/*
		 *		State Classes Friend Declarations
		 *		States should be able to access this class's properties
		 */
		friend class State;

	private:
		// Stores the current state of this character
		State* m_currentState;
		// Stores a state that is set to deletion
		State* m_previousState;

	public:
		FiniteStateMachine();
		virtual ~FiniteStateMachine() = 0;

		virtual void Update(double dt);
		virtual void Exit(void);

		// Getters
		virtual string GetStateName(void);
		virtual string GetThisStateName(void);
		virtual string GetChildStateName(void);

	protected:
		// Use this function to set the current state. Automatically calls the state's Init() and destroys the previous state.
		void setCurrentState(State* startState);
	};
}
#endif