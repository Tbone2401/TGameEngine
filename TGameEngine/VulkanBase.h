#pragma once

#define GLFW_INCLUDE_VULKAN
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <GLFW\glfw3.h>
#include <map>
#include <vulkan\vulkan.h>
#include "VulkanHelper.h"

class VulkanBase
{
public:

	VkPhysicalDevice physicalDevice;
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

	int windowHeight;
	int windowWidth;

	//VULKAN FUNCTIONS
	void createInstance();

	void setupDebugCallBack();

	void createSurface();

	void createWindow();
	void readConfig();
};

