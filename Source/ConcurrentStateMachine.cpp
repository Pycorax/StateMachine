#include "ConcurrentStateMachine.h"

// STL Includes
#include <exception>

// Using Directives
using std::runtime_error;

StateMachine::ConcurrentStateMachine::ConcurrentStateMachine()
{
}


StateMachine::ConcurrentStateMachine::~ConcurrentStateMachine()
{
}

void StateMachine::ConcurrentStateMachine::Init(const unsigned numStateMachines)
{
	for (size_t i = 0; i < numStateMachines; ++i)
	{
		m_stateMachines.push_back(FiniteStateMachineInstance(this));
	}
}

void StateMachine::ConcurrentStateMachine::Update(double dt)
{
	for (auto& stateMachine : m_stateMachines)
	{
		stateMachine.Update(dt);
	}
}

void StateMachine::ConcurrentStateMachine::Exit(void)
{
	while (!m_stateMachines.empty())
	{
		m_stateMachines.back().Exit();
		m_stateMachines.pop_back();
	}
}

string StateMachine::ConcurrentStateMachine::GetStateName(unsigned ID)
{
	// Check if out of range
	idOutOfRangeCheck(ID);

	return m_stateMachines[ID].GetStateName();
}

string StateMachine::ConcurrentStateMachine::GetThisStateName(unsigned ID)
{
	// Check if out of range
	idOutOfRangeCheck(ID);

	return m_stateMachines[ID].GetThisStateName();
}

string StateMachine::ConcurrentStateMachine::GetChildStateName(unsigned ID)
{
	// Check if out of range
	idOutOfRangeCheck(ID);

	return m_stateMachines[ID].GetChildStateName();
}

void StateMachine::ConcurrentStateMachine::setCurrentState(State * state, unsigned id)
{
	// Check if out of range
	idOutOfRangeCheck(id);

	// Set the state
	m_stateMachines[id].setCurrentState(state);
}

void StateMachine::ConcurrentStateMachine::idOutOfRangeCheck(unsigned id)
{
	if (id >= m_stateMachines.size())
	{
		throw new runtime_error("StateMachine index out of range!");
	}
}
