#include "NPC.h"

#include "FSMState.h"

NPC::NPC()
	: m_currentState(nullptr)
	, m_previousState(nullptr)
{
}


NPC::~NPC()
{
}

void NPC::Update(double dt)
{
	if (m_currentState)
	{
		m_currentState->Update(dt);
	}
}

void NPC::Exit(void)
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

string NPC::GetStateName(void)
{
	return m_currentState->GetStateName();
}

string NPC::GetThisStateName(void)
{
	return m_currentState->GetThisStateName();
}

string NPC::GetChildStateName(void)
{
	return m_currentState->GetChildStateName();
}

void NPC::setCurrentState(FSMState * startState)
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
