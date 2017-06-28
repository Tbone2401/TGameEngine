#include "stdafx.h"
#include "InputManager.h"
#include <stdlib.h>
#include <iostream>

int main()
{
	system("cmd.exe /c dir c:\\");

	InputManager *inputManager = new InputManager();
	inputManager->Initialise();

	char test[256];
	std::cin.getline(test, 256);

	return 0;
}