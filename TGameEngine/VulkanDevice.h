#pragma once
#include "vulkan\vulkan.h"
#include "VulkanHelper.h"

class VulkanDevice
{
public:
	struct 
	{
		uint32_t graphics;
		uint32_t compute;
		uint32_t transfer;
	}queueFamilyIndices;

	VkPhysicalDevice physicalDevice;
	VkDevice logicalDevice;
	VkPhysicalDeviceProperties properties;
	VkPhysicalDeviceFeatures features;
	VkPhysicalDeviceMemoryProperties memoryProperties;
	std::vector<VkQueueFamilyProperties> queueFamilyProperties;
	std::vector<std::string> supportedExtensions;
	VkCommandPool commandPool = VK_NULL_HANDLE;
	bool enableDebugMarkers = false;

	VulkanDevice(VkPhysicalDevice physicalDevice);
	~VulkanDevice();
	uint32_t getMemoryType(uint32_t typeBits, VkMemoryPropertyFlags properties, VkBool32 * memTypeFound);
	uint32_t getQueueFamilyIndex(VkQueueFlagBits queueFlags);
	VkResult createLogicalDevice(VkPhysicalDeviceFeatures enabledFeatures, bool useSwapChain = true, VkQueueFlags requestedQueueTypes = VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT);

	bool extensionSupported(std::string extension);

	VkCommandPool createCommandPool(uint32_t queueFamilyIndex, VkCommandPoolCreateFlags createFlags);

private:
	VulkanDevice(const VulkanDevice&);                 // Prevent copy-construction
	VulkanDevice& operator=(const VulkanDevice&);      // Prevent assignment
};

