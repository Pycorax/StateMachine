#include "FiniteStateMachine.h"

#include "State.h"
#include "ConcurrentStateMachine.h"

StateMachine::FiniteStateMachine::FiniteStateMachine()
	: m_currentState(nullptr)
	, m_previousState(nullptr)
	, m_parent(nullptr)
{
}


StateMachine::FiniteStateMachine::~FiniteStateMachine()
{
}

void StateMachine::FiniteStateMachine::Update(double dt)
{
	if (m_currentState)
	{
		m_currentState->Update(dt);
	}
}

void StateMachine::FiniteStateMachine::Exit(void)
{
	if (m_currentState)
	{
		m_currentState->Exit();
		delete m_currentState;
		m_currentState = nullptr;
	}

	if (m_previousState)
	{
		m_previousState->Exit();
		delete m_previousState;
		m_previousState = nullptr;
	}
}

string StateMachine::FiniteStateMachine::GetStateName(void)
{
	return m_currentState->GetStateName();
}

string StateMachine::FiniteStateMachine::GetThisStateName(void)
{
	return m_currentState->GetThisStateName();
}

string StateMachine::FiniteStateMachine::GetChildStateName(void)
{
	return m_currentState->GetChildStateName();
}

void StateMachine::FiniteStateMachine::setCurrentState(State * startState)
{
	if (m_currentState)
	{
		m_currentState->Exit();
		delete m_currentState;
		m_currentState = nullptr;
	}

	m_currentState = startState;
	m_currentState->Init(this);
}

void StateMachine::FiniteStateMachine::setParent(ConcurrentStateMachine * csm)
{
	m_parent = csm;
}

StateMachine::ConcurrentStateMachine * StateMachine::FiniteStateMachine::GetParent(void) const
{
	return m_parent;
}
