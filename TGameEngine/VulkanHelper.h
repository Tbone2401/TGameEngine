#pragma once
#include <vulkan\vulkan.h>
#include <GLFW\glfw3.h>

// Macro to check and display Vulkan return results
#define VK_CHECK_RESULT(f)																				\
{																										\
	VkResult res = (f);																					\
	if (res != VK_SUCCESS)																				\
	{																									\
		std::cout << "Fatal : VkResult is \"" << vkTools::errorString(res) << "\" in " << __FILE__ << " at line " << __LINE__ << std::endl; \
		assert(res == VK_SUCCESS);																		\
	}																									\
}			

namespace VulkanHelper
{
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
	VkBool32 checkDeviceExtensionPresent(VkPhysicalDevice physicalDevice, const char* extensionName);
	bool checkValidationLayerSupport(const std::vector<const char*> *validationLayers);
	std::vector<const char*> getRequiredExtensions();
};

