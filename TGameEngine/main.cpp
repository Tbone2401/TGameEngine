#include "stdafx.h"
#include "InputManager.h"
#include "TestInput.h"
#include <stdlib.h>
#include <iostream>

int main()
{
	system("cmd.exe /c dir c:\\");

	//InputManager *inputManager = new InputManager();
	//inputManager->Initialise();
	TestInput testInput;
	testInput.Initialise();
	InputManager::getInstance().Initialise();

	char test[256];

	while (true)
	{
		InputManager::getInstance().Tick();
		Sleep(100);
	}

	std::cin.getline(test, 256);

	return 0;
}