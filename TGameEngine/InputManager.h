#pragma once

#include "stdafx.h"
#include <map>

enum ActionID : uint8_t
{
	WPress = 0
};

enum GamepadIndex : DWORD
{
	PlayerOne = 0,
	PlayerTwo = 1,
	PlayerThree = 2,
	PlayerFour = 3
};

enum InputTriggerState
{
	Pressed,
	Released,
	Down
};

struct InputAction
{
	InputAction(ActionID actionID, InputTriggerState triggerState = InputTriggerState::Pressed, int keyboardCode = -1, int mouseButtonCode = -1, WORD gamepadButtonCode = 0, GamepadIndex playerIndex = GamepadIndex::PlayerOne) :
		ActionID(actionID),
		TriggerState(triggerState),
		KeyboardCode(keyboardCode),
		MouseButtonCode(mouseButtonCode),
		GamepadButtonCode(gamepadButtonCode),
		PlayerIndex(playerIndex),
		IsTriggered(false) {}

	ActionID ActionID;
	InputTriggerState TriggerState;
	int KeyboardCode; //VK_... (Range 0x07 <> 0xFE)
	int MouseButtonCode; //VK_... (Range 0x00 <> 0x06)
	WORD GamepadButtonCode; //XINPUT_GAMEPAD_...
	GamepadIndex PlayerIndex;
	bool IsTriggered;
};

class InputManager :IComponent
{
public:
	static InputManager& getInstance()
	{
		static InputManager    instance; // Guaranteed to be destroyed.
										 // Instantiated on first use.
		return instance;
	}
private:
	InputManager() {}         // Constructor? (the {} brackets) are needed here.




	std::map<int, SA::delegate<void()>> m_KeyDelegates;

	SA::delegate<void()> m_voidDelegate;
	bool IsPressed();
	std::vector<ActionID> m_Actions;

protected:

	void Destroy();

public:
	// Note: Scott Meyers mentions in his Effective Modern
	//       C++ book, that deleted functions should generally
	//       be public as it results in better error messages
	//       due to the compilers behavior to check accessibility
	//       before deleted status
	InputManager(InputManager const&) = delete;
	void operator=(InputManager const&) = delete;


	void Initialise();
	void Tick();
	//TODO: add a function pointer here
	void AddInput(SA::delegate<void()> delegateToCall, int key);
};