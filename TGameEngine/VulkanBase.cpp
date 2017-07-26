#include "stdafx.h"
#include "VulkanBase.h"
#include <fstream>
#include <glm/glm.hpp>

//Don't foget double slash!
const std::string CONFIG_FILE = "configurations\\config.ini";

//Error checking
#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

const std::vector<const char*> validationLayers = { "VK_LAYER_LUNARG_standard_validation" };

VkResult CreateDebugReportCallbackEXT(VkInstance instance,
	const VkDebugReportCallbackCreateInfoEXT* pCreateInfo,
	const VkAllocationCallbacks* pAllocator,
	VkDebugReportCallbackEXT* pCallback)
{
	auto func = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
	if (func != nullptr)
	{
		return func(instance, pCreateInfo, pAllocator, pCallback);
	}
	else
	{
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}

static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(
	VkDebugReportFlagsEXT flags,
	VkDebugReportObjectTypeEXT objType,
	uint64_t obj,
	size_t location,
	int32_t code,
	const char* layerPrefix,
	const char* msg,
	void* userData)
{
	std::cerr << "Validation layer: " << msg << std::endl;

	return VK_FALSE;
}

struct Vertex
{
	glm::vec3 pos;
	glm::vec2 uv;
	glm::vec3 color;
	glm::vec3 normal;
	glm::vec3 tangent;
};


void VulkanBase::Initialise()
{
	glfwInit();
	readConfig();
	createInstance();

	createWindow();
	createSurface();
}

VulkanBase::VulkanBase()
{

}


VulkanBase::~VulkanBase()
{

}
void VulkanBase::createWindow()
{
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);

	pWindow = glfwCreateWindow(windowWidth, windowHeight, "TGM -", nullptr, nullptr);
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

void VulkanBase::createInstance()
{
	if (enableValidationLayers && ! vHelper.checkValidationLayerSupport(&validationLayers))
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

void VulkanBase::setupDebugCallBack()
{
	if (!enableValidationLayers)
	{
		return;
	}

	VkDebugReportCallbackCreateInfoEXT createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
	createInfo.flags = VK_DEBUG_REPORT_DEBUG_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT;
	createInfo.pfnCallback = debugCallback;

	if (CreateDebugReportCallbackEXT(vInstance, &createInfo, nullptr, &callback) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to set up debug callback!");
	}
}

void VulkanBase::createSurface()
{
	if (glfwCreateWindowSurface(vInstance, pWindow, nullptr, &surface) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create window surface!");
	}

}