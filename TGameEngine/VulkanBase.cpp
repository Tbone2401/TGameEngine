#include "stdafx.h"
#include "VulkanBase.h"
#include <fstream>

//Don't foget double slash!
const std::string CONFIG_FILE = "configurations\\config.ini";


namespace VulkanBase
{
	void VulkanBase::Initialise()
	{
		readConfig();
		createWindow();
	}

	VulkanBase::VulkanBase()
	{

	}


	VulkanBase::~VulkanBase()
	{

	}
	void VulkanBase::createWindow()
	{
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

		pWindow = glfwCreateWindow(windowWidth, windowHeight, "TGM", nullptr, nullptr);
	}
	void VulkanBase::readConfig()
	{
		std::string line;
		std::string configName;
		std::string configVar;
		size_t seekPos;
		std::ifstream configFile(CONFIG_FILE);


		if (configFile.is_open())
		{
			
			while (getline(configFile, line))
			{
				seekPos = line.find_first_of("=");
				configName = line.substr(0, seekPos);
				if (configName == "WindowHeight")
				{
					windowHeight = std::stoi(line.substr(seekPos + 1));
				}
				if (configName == "WindowWidth")
				{
					windowWidth = std::stoi(line.substr(seekPos + 1));
				}
			}
		}
	}
}
