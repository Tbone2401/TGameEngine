#include "stdafx.h"
#include "VulkanHelper.h"

VulkanHelper::VulkanHelper()
{
}


VulkanHelper::~VulkanHelper()
{
}

VkFormat VulkanHelper::getSupportedDepthFormat(VkPhysicalDevice physicalDevice)
{
	// Since all depth formats may be optional, we need to find a suitable depth format to use
	// Start with the highest precision packed format
	std::vector<VkFormat> depthFormats = {
		VK_FORMAT_D32_SFLOAT_S8_UINT,
		VK_FORMAT_D32_SFLOAT,
		VK_FORMAT_D24_UNORM_S8_UINT,
		VK_FORMAT_D16_UNORM_S8_UINT,
		VK_FORMAT_D16_UNORM
	};

	for (auto& format : depthFormats)
	{
		VkFormatProperties formatProps;
		vkGetPhysicalDeviceFormatProperties(physicalDevice, format, &formatProps);
		// Format must support depth stencil attachment for optimal tiling
		if (formatProps.optimalTilingFeatures & VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT)
		{
			return format;
		}
	}
	throw std::runtime_error("failed to find supported depth format!");
}

VkMemoryAllocateInfo VulkanHelper::memoryAllocateInfo()
{
	VkMemoryAllocateInfo memAllocInfo = {};
	memAllocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	memAllocInfo.pNext = NULL;
	memAllocInfo.allocationSize = 0;
	memAllocInfo.memoryTypeIndex = 0;
	return memAllocInfo;
}

VkCommandBufferAllocateInfo VulkanHelper::commandBufferAllocateInfo(VkCommandPool commandPool, VkCommandBufferLevel level, uint32_t bufferCount)
{
	VkCommandBufferAllocateInfo commandBufferAllocateInfo = {};
	commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	commandBufferAllocateInfo.commandPool = commandPool;
	commandBufferAllocateInfo.level = level;
	commandBufferAllocateInfo.commandBufferCount = bufferCount;
	return commandBufferAllocateInfo;
}

VkCommandPoolCreateInfo VulkanHelper::commandPoolCreateInfo()
{
	VkCommandPoolCreateInfo cmdPoolCreateInfo = {};
	cmdPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	return cmdPoolCreateInfo;
}

VkCommandBufferBeginInfo VulkanHelper::commandBufferBeginInfo()
{
	VkCommandBufferBeginInfo cmdBufferBeginInfo = {};
	cmdBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	cmdBufferBeginInfo.pNext = NULL;
	return cmdBufferBeginInfo;
}

VkCommandBufferInheritanceInfo VulkanHelper::commandBufferInheritanceInfo()
{
	VkCommandBufferInheritanceInfo cmdBufferInheritanceInfo = {};
	cmdBufferInheritanceInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
	return cmdBufferInheritanceInfo;
}

VkRenderPassBeginInfo VulkanHelper::renderPassBeginInfo()
{
	VkRenderPassBeginInfo renderPassBeginInfo = {};
	renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassBeginInfo.pNext = NULL;
	return renderPassBeginInfo;
}

VkRenderPassCreateInfo VulkanHelper::renderPassCreateInfo()
{
	VkRenderPassCreateInfo renderPassCreateInfo = {};
	renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassCreateInfo.pNext = NULL;
	return renderPassCreateInfo;
}

VkImageMemoryBarrier VulkanHelper::imageMemoryBarrier()
{
	VkImageMemoryBarrier imageMemoryBarrier = {};
	imageMemoryBarrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	imageMemoryBarrier.pNext = NULL;
	// Some default values
	imageMemoryBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	imageMemoryBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	return imageMemoryBarrier;
}

VkBufferMemoryBarrier VulkanHelper::bufferMemoryBarrier()
{
	VkBufferMemoryBarrier bufferMemoryBarrier = {};
	bufferMemoryBarrier.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
	bufferMemoryBarrier.pNext = NULL;
	return bufferMemoryBarrier;
}

VkMemoryBarrier VulkanHelper::memoryBarrier()
{
	VkMemoryBarrier memoryBarrier = {};
	memoryBarrier.sType = VK_STRUCTURE_TYPE_MEMORY_BARRIER;
	memoryBarrier.pNext = NULL;
	return memoryBarrier;
}

VkImageCreateInfo VulkanHelper::imageCreateInfo()
{
	VkImageCreateInfo imageCreateInfo = {};
	imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	imageCreateInfo.pNext = NULL;
	return imageCreateInfo;
}

VkSamplerCreateInfo VulkanHelper::samplerCreateInfo()
{
	VkSamplerCreateInfo samplerCreateInfo = {};
	samplerCreateInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
	samplerCreateInfo.pNext = NULL;
	return samplerCreateInfo;
}

VkImageViewCreateInfo VulkanHelper::imageViewCreateInfo()
{
	VkImageViewCreateInfo imageViewCreateInfo = {};
	imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	imageViewCreateInfo.pNext = NULL;
	return imageViewCreateInfo;
}

VkFramebufferCreateInfo VulkanHelper::framebufferCreateInfo()
{
	VkFramebufferCreateInfo framebufferCreateInfo = {};
	framebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	framebufferCreateInfo.pNext = NULL;
	return framebufferCreateInfo;
}

VkSemaphoreCreateInfo VulkanHelper::semaphoreCreateInfo()
{
	VkSemaphoreCreateInfo semaphoreCreateInfo = {};
	semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	semaphoreCreateInfo.pNext = NULL;
	semaphoreCreateInfo.flags = 0;
	return semaphoreCreateInfo;
}

VkFenceCreateInfo VulkanHelper::fenceCreateInfo(VkFenceCreateFlags flags)
{
	VkFenceCreateInfo fenceCreateInfo = {};
	fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceCreateInfo.flags = flags;
	return fenceCreateInfo;
}

VkEventCreateInfo VulkanHelper::eventCreateInfo()
{
	VkEventCreateInfo eventCreateInfo = {};
	eventCreateInfo.sType = VK_STRUCTURE_TYPE_EVENT_CREATE_INFO;
	return eventCreateInfo;
}

VkSubmitInfo VulkanHelper::submitInfo()
{
	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.pNext = NULL;
	return submitInfo;
}

bool VulkanHelper::checkValidationLayerSupport(const std::vector<const char*> *validationLayers)
{
	uint32_t layerCount;
	vkEnumerateInstanceLayerProperties(&layerCount, nullptr);
	std::vector<VkLayerProperties> availableLayers(layerCount);
	vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

	std::cout << std::endl << "Checking validation layers:" << std::endl;
	bool layerFound = false;
	for (const char* layerName : *validationLayers)
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

std::vector<const char*> VulkanHelper::getRequiredExtensions()
{
	std::vector<const char*> extensions;

	unsigned int glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	for (unsigned int i = 0; i < glfwExtensionCount; i++)
	{
		extensions.push_back(glfwExtensions[i]);
	}
	extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);

	return extensions;
}