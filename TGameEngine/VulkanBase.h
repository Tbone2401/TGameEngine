#pragma once

#define GLFW_INCLUDE_VULKAN
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <GLFW\glfw3.h>
#include <map>
#include <vulkan\vulkan.h>
#include "VulkanHelper.h"

struct QueueFamilyIndices
{
	int graphicsFamily = -1;
	int presentFamily = -1;

	bool isComplete()
	{
		return graphicsFamily >= 0 && presentFamily >= 0;
	}
};

struct SwapChainSupportDetails
{
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};


class VulkanBase
{
public:

	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkDevice logicalDevice;


	void Initialise();
	VulkanBase();
	~VulkanBase();

private:
	GLFWwindow* pWindow = nullptr;

	VulkanHelper vHelper;
	VkInstance vInstance;
	VkDevice device;
	VkQueue queue;
	VkDebugReportCallbackEXT callback;
	VkSurfaceKHR surface;
	VkQueue graphicsQueue;
	VkQueue presentQueue;

	int windowHeight;
	int windowWidth;

	//VULKAN FUNCTIONS
	void createInstance();

	void setupDebugCallBack();

	void createSurface();

	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);

	void createLogicalDevice();

	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

	bool isDeviceSuitable(VkPhysicalDevice device);

	bool checkDeviceExtensionSupport(VkPhysicalDevice device);

	void pickPhysicalDevice();

	void createWindow();
	void readConfig();
};

