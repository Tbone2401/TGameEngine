#include "stdafx.h"
#include "VulkanBase.h"
#include <fstream>

//Don't foget double slash!
const std::string CONFIG_FILE = "configurations\\config.ini";

//Error checking
#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
const std::vector<const char*> validationLayers = { "VK_LAYER_LUNARG_standard_validation" };
#endif

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
	bool checkValidationLayerSupport()
	{
		uint32_t layerCount;
		vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
		std::vector<VkLayerProperties> availableLayers(layerCount);
		vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

		std::cout << std::endl << "Checking validation layers:" << std::endl;
		bool layerFound = false;
		for (const char* layerName : validationLayers)
		{
			for (const VkLayerProperties& layerProperties : availableLayers)
			{
				if (strcmp(layerName, layerProperties.layerName) == 0)
				{
					layerFound = true;
					std::cout << "\t" << layerProperties.layerName << std::endl;
					break;
				}
			}
			if (!layerFound)
			{
				return false;
			}
		}
		return true;
	}
	void VulkanBase::createInstance()
	{
		if (enableValidationLayers && !checkValidationLayerSupport())
		{
			throw std::runtime_error("validation layers requested, but not available!");
		}

		VkApplicationInfo appInfo = {};
		appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		appInfo.pApplicationName = "TGameEngine";
		appInfo.applicationVersion = VK_MAKE_VERSION(0, 1, 0);
		appInfo.pEngineName = "TGameEngine";
		appInfo.engineVersion = VK_MAKE_VERSION(0, 1, 0);
		appInfo.apiVersion = VK_API_VERSION_1_0;

		VkInstanceCreateInfo createInfo = {};
		createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		createInfo.pApplicationInfo = &appInfo;


		if (enableValidationLayers)
		{
			createInfo.enabledLayerCount = static_cast<uint32_t>(validationLayers.size());
			createInfo.ppEnabledLayerNames = validationLayers.data();
		}
		else 
		{
			createInfo.enabledLayerCount = 0;
		}

		if (vkCreateInstance(&createInfo, nullptr, &vInstance) != VK_SUCCESS)
		{
			throw std::runtime_error("failed to create instance!");
		}
	}
}
