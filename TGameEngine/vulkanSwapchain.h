#pragma once
#include "stdafx.h"
#include <vulkan/vulkan.h>
#include "VulkanHelper.h"

typedef struct _SwapChainBuffers {
	VkImage image;
	VkImageView view;
} SwapChainBuffer;

struct QueueFamilyIndices
{
	int graphicsFamily = -1;
	int presentFamily = -1;

	bool isComplete()
	{
		return graphicsFamily >= 0 && presentFamily >= 0;
	}
};

class vulkanSwapchain
{
public:
	vulkanSwapchain();
	~vulkanSwapchain();

	void initSurface(VkInstance instance, GLFWwindow* pWindow, VkDevice device);
	void connect(VkInstance instance, VkPhysicalDevice physDevice, VkDevice device);
	void create(uint32_t *width, uint32_t *height, bool vsync = false);
	VkResult queuePresent(VkQueue queue, uint32_t imageIndex, VkSemaphore waitSemaphore = VK_NULL_HANDLE);

	void cleanup();

private:
	VkInstance vInstance;
	VkDevice vDevice;
	VkPhysicalDevice vPhysicalDevice;
	VkSurfaceKHR surface;
	VkSwapchainKHR swapChain = VK_NULL_HANDLE;
	uint32_t imageCount;
	std::vector<VkImage> images;
	std::vector<SwapChainBuffer> buffers;
	uint32_t queueNodeIndex = UINT32_MAX;
	VkFormat colorFormat;
	VkColorSpaceKHR colorSpace;


	QueueFamilyIndices findQueueFamilies();
};

