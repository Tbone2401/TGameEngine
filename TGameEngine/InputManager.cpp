#include "stdafx.h"
#include "InputManager.h"

void InputManager::Initialise()
{
	std::cout << "InputManager Initialised" << std::endl;
}

void InputManager::Tick()
{
	for (const auto& keyDelegate : m_KeyDelegates)
	{
		if (GetAsyncKeyState(keyDelegate.first))
		{
			keyDelegate.second();
		}
	}
}

void InputManager::Destroy()
{

}

bool InputManager::IsPressed()
{
	return false;
}

void InputManager::AddInput(SA::delegate<void()> delegateToCall, int key)
{
	//m_voidDelegate = delegateToCall;
	m_KeyDelegates[key] = delegateToCall;
}