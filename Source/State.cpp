#include "State.h"

#include <Windows.h>

const float StateMachine::State::S_MAX_STATE_TIME = 1.f;

StateMachine::State::State()
	: m_FSMOwner(nullptr)
	, m_stateParent(nullptr)
	, m_currentState(nullptr)
	, m_previousState(nullptr)
	, m_stateName("Unnamed")
{
}


StateMachine::State::~State()
{
}

// Initialization Function for a FiniteStateMachine Base State [Parent is a FiniteStateMachine]
void StateMachine::State::Init(FiniteStateMachine * SMOwner)
{
	// Set the parent
	m_FSMOwner = SMOwner;

	// If switched to this state from a previous state, clear the previous state
	if (m_FSMOwner->m_previousState)
	{
		m_FSMOwner->m_previousState->Exit();
		delete m_FSMOwner->m_previousState;
		m_FSMOwner->m_previousState = nullptr;
	}
}

// Initialization Function for a Child State [Parent is a State]
void StateMachine::State::Init(State * stateOwner)
{
	// Set the parent
	m_stateParent = stateOwner;

	// Connect this state to the original FiniteStateMachine owner so that we can interface with it.
	m_FSMOwner = m_stateParent->m_FSMOwner;

	// If switched to this nested state from a previous nested state, clear the previous nested state
	if (m_stateParent->m_previousState)
	{
		m_stateParent->m_previousState->Exit();
		delete m_stateParent->m_previousState;
		m_stateParent->m_previousState = nullptr;
	}
}

void StateMachine::State::Update(double dt)
{
	// If this is a parent state
	if (m_currentState)
	{
		// Call the nested state's update
		m_currentState->Update(dt);
	}
}

void StateMachine::State::Exit(void)
{
	// If this state is a parent state
	if (m_currentState)
	{
		// Clear the current child state
		m_currentState->Exit();
		delete m_currentState;
		m_currentState = nullptr;
	}

	// If the previous state was not deleted
	if (m_previousState)
	{
		// Clear the previous child state
		m_previousState->Exit();
		delete m_previousState;
		m_previousState = nullptr;
	}

	m_FSMOwner = nullptr;
	m_stateParent = nullptr;
}

string StateMachine::State::GetStateName(void)
{
	if (m_currentState)
	{
		return m_stateName + " - " + m_currentState->GetStateName();
	}

	return m_stateName;
}

string StateMachine::State::GetThisStateName(void)
{
	return m_stateName;
}

string StateMachine::State::GetChildStateName(void)
{
	if (m_currentState)
	{
		return m_currentState->GetStateName();
	}
	
	return "";
}

void StateMachine::State::changeState(State * state)
{
	if (m_stateParent)		// Is a Child State
	{
		m_stateParent->m_previousState = this;
		m_stateParent->m_currentState = state;
		m_stateParent->m_currentState->Init(m_stateParent);
	}
	else					// Is a FiniteStateMachine Base State
	{
		m_FSMOwner->m_previousState = this;
		m_FSMOwner->m_currentState = state;
		m_FSMOwner->m_currentState->Init(m_FSMOwner);
	}
}

bool StateMachine::State::isNestedState(void) const
{
	return m_stateParent != nullptr;
}

void StateMachine::State::setCurrentState(State * startState)
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