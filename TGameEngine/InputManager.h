#pragma once

enum ActionId : uint8_t
{
	WPRess = 0
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
	InputAction() :
		ActionID(-1),
		TriggerState(InputTriggerState::Pressed),
		KeyboardCode(-1),
		MouseButtonCode(-1),
		GamepadButtonCode(0),
		PlayerIndex(GamepadIndex::PlayerOne),
		IsTriggered(false) {}

	InputAction(int actionID, InputTriggerState triggerState = InputTriggerState::Pressed, int keyboardCode = -1, int mouseButtonCode = -1, WORD gamepadButtonCode = 0, GamepadIndex playerIndex = GamepadIndex::PlayerOne) :
		ActionID(actionID),
		TriggerState(triggerState),
		KeyboardCode(keyboardCode),
		MouseButtonCode(mouseButtonCode),
		GamepadButtonCode(gamepadButtonCode),
		PlayerIndex(playerIndex),
		IsTriggered(false) {}

	int ActionID;
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
	InputManager();
	~InputManager();

	void Initialise();
	void Tick();
	void Destroy();

private:
	bool IsPressed();



private:
	// -------------------------
	//Disabling copy constructor and assignment operator.
	// -------------------------
	InputManager(const InputManager& t);
	InputManager& operator=(const InputManager& t);
};

