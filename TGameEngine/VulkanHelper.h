#pragma once
#include <vulkan\vulkan.h>
#include <GLFW\glfw3.h>

class VulkanHelper
{
public:
	VulkanHelper();
	~VulkanHelper();
	VkFormat getSupportedDepthFormat(VkPhysicalDevice physicalDevice);
	VkMemoryAllocateInfo memoryAllocateInfo();
	VkCommandBufferAllocateInfo commandBufferAllocateInfo(VkCommandPool commandPool, VkCommandBufferLevel level, uint32_t bufferCount);
	VkCommandPoolCreateInfo commandPoolCreateInfo();
	VkCommandBufferBeginInfo commandBufferBeginInfo();
	VkCommandBufferInheritanceInfo commandBufferInheritanceInfo();
	VkRenderPassBeginInfo renderPassBeginInfo();
	VkRenderPassCreateInfo renderPassCreateInfo();
	VkImageMemoryBarrier imageMemoryBarrier();
	VkBufferMemoryBarrier bufferMemoryBarrier();
	VkMemoryBarrier memoryBarrier();
	VkImageCreateInfo imageCreateInfo();
	VkSamplerCreateInfo samplerCreateInfo();
	VkImageViewCreateInfo imageViewCreateInfo();
	VkFramebufferCreateInfo framebufferCreateInfo();
	VkSemaphoreCreateInfo semaphoreCreateInfo();
	VkFenceCreateInfo fenceCreateInfo(VkFenceCreateFlags flags);
	VkEventCreateInfo eventCreateInfo();
	VkSubmitInfo submitInfo();
	bool checkValidationLayerSupport(const std::vector<const char*> *validationLayers);
	std::vector<const char*> getRequiredExtensions();
};

