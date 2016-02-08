#ifndef CONCURRENT_STATE_MACHINE
#define CONCURRENT_STATE_MACHINE

// STL Includes
#include <vector>

// Other Includes
#include "FiniteStateMachine.h"

// Using Directives
using std::vector;

namespace StateMachine
{
/******************************************************************************/
/*!
		Class ConcurrentStateMachine:
\brief	Concurrent State Machine interface class meant to provide Concurrent
		State Machine functionality to inherited classes. Unlike the Finite
		State Machine, the Concurrent State Machine can hold multiple State
		Machines.

		Each instance of a State Machine in the Concurrent State Machine is 
		given a ID starting from 0. It is recommended to use a self-defined 
		enum to identify each state.

		To set the starting state, use setCurrentState() to specify the
		state to use and the ID of the State Machine in the Concurrent State
		Machine you wish to modify. setCurrentState() will automatically call
		the Init() of the state.

		To use this class, simply inherit from it and define States for
		it. Said States should be declared as friend classes of the
		ConcurrentStateMachine.
*/
/******************************************************************************/
	class ConcurrentStateMachine
	{
		private:
			/******************************************************************************/
			/*!
					Class FiniteStateMachineInstance:
			\brief	A FiniteStateMachine for use with ConcurrentStateMAchine to hold an
					instance of a StateMachine.

					Unlike FiniteStateMachine, it is no an interface and thus can be
					instantiated.
			*/
			/******************************************************************************/

			class FiniteStateMachineInstance : public FiniteStateMachine
			{
				public:
					FiniteStateMachineInstance() : FiniteStateMachine() {}
					~FiniteStateMachineInstance() {}

					void setCurrentState(State* state)
					{
						FiniteStateMachine::setCurrentState(state);
					}
			};

			vector<FiniteStateMachineInstance> m_stateMachines;

		public:
			ConcurrentStateMachine();
			~ConcurrentStateMachine();

			// Function to set up instances of a Concurrent State Machine
			void Init(const unsigned numStateMachines);
			virtual void Update(double dt);
			virtual void Exit(void);

			virtual string GetStateName(unsigned ID = 0);
			virtual string GetThisStateName(unsigned ID = 0);
			virtual string GetChildStateName(unsigned ID = 0);

		protected:
			// Use this function to set the current state. Automatically calls the state's Init() and destroys the previous state.
			void setCurrentState(State* state, unsigned id);

		private:
			void idOutOfRangeCheck(unsigned id);

	};
}

#endif