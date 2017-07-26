#include "stdafx.h"
#define GLFW_INCLUDE_VULKAN
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <GLFW\glfw3.h>
#include "InputManager.h"
#include "VulkanBase.h"
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
	VulkanBase base;
	base.Initialise();

	char test[256];

	while (true)
	{
		InputManager::getInstance().Tick();
		Sleep(100);
	}

	std::cin.getline(test, 256);

	return 0;
}