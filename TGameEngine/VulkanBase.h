#pragma once

#define GLFW_INCLUDE_VULKAN
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <GLFW\glfw3.h>
#include <map>
#include <vulkan\vulkan.h>

namespace VulkanBase
{
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

		VkInstance vInstance;
		VkDevice device;

		int windowHeight;
		int windowWidth;

		//VULKAN FUNCTIONS
		void createInstance();

		void createWindow();
		void readConfig();
	};
}


