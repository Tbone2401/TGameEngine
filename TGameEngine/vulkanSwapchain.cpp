#include "stdafx.h"
#include "vulkanSwapchain.h"


vulkanSwapchain::vulkanSwapchain()
{
}


vulkanSwapchain::~vulkanSwapchain()
{
}

void vulkanSwapchain::initSurface(VkInstance instance, GLFWwindow* pWindow, VkDevice device)
{
	VkResult err;

	vInstance = instance;
	vDevice = device;
	err = glfwCreateWindowSurface(vInstance, pWindow, nullptr, &surface);

	if (glfwCreateWindowSurface(vInstance, pWindow, nullptr, &surface) != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create window surface!");
	}

	uint32_t queueCount;
	vkGetPhysicalDeviceQueueFamilyProperties(vPhysicalDevice, &queueCount, NULL);

	if (queueCount == 0)
	{
		throw std::runtime_error("Failed to find queue families");
	}

	std::vector<VkQueueFamilyProperties> queueProps(queueCount);
	vkGetPhysicalDeviceQueueFamilyProperties(vPhysicalDevice, &queueCount, queueProps.data());

	std::vector<VkBool32> supportsPresent(queueCount); //find ones with support for presenting
	for (uint32_t i = 0; i < queueCount; i++)
	{
		vkGetPhysicalDeviceSurfaceSupportKHR(vPhysicalDevice, i, surface, &supportsPresent[i]);
	}
	uint32_t graphicsQueueNodeIndex = UINT32_MAX;
	uint32_t presentQueueNodeIndex = UINT32_MAX;
	for (uint32_t i = 0; i < queueCount; i++)
	{
		if ((queueProps[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0)
		{
			if (graphicsQueueNodeIndex == UINT32_MAX)
			{
				graphicsQueueNodeIndex = i;
			}

			if (supportsPresent[i] == VK_TRUE)
			{
				graphicsQueueNodeIndex = i;
				presentQueueNodeIndex = i;
				break;
			}
		}
	}
	if (presentQueueNodeIndex == UINT32_MAX)
	{
		std::cout << "Separate queue to present with" << std::endl;
		for (uint32_t i = 0; i < queueCount; ++i)
		{
			if (supportsPresent[i] == VK_TRUE)
			{
				presentQueueNodeIndex = i;
				break;
			}
		}
	}

	if (graphicsQueueNodeIndex == UINT32_MAX || presentQueueNodeIndex == UINT32_MAX)
	{
		throw std::runtime_error("Failed to create graphicsQueue or presentQueue");
	}
	if (graphicsQueueNodeIndex != presentQueueNodeIndex)
	{
		throw std::runtime_error("Find out how to make this work!");
	}
	queueNodeIndex = graphicsQueueNodeIndex;

	uint32_t formatCount;
	err = vkGetPhysicalDeviceSurfaceFormatsKHR(vPhysicalDevice, surface, &formatCount, nullptr);

	if (formatCount == 0 || err != VK_SUCCESS)
	{
		throw std::runtime_error("No supported formats!");
	}

	std::vector<VkSurfaceFormatKHR> surfaceFormats(formatCount);
	err = vkGetPhysicalDeviceSurfaceFormatsKHR(vPhysicalDevice, surface, &formatCount, surfaceFormats.data());

	if (err != VK_SUCCESS)
	{
		throw std::runtime_error("Something went wrong with getting surfaceFormats");
	}
	if ((formatCount == 1) && (surfaceFormats[0].format == VK_FORMAT_UNDEFINED))
	{
		colorFormat = VK_FORMAT_B8G8R8A8_UNORM;
	}
	else
	{
		colorFormat = surfaceFormats[0].format;
	}
	colorSpace = surfaceFormats[0].colorSpace;
}

void vulkanSwapchain::connect(VkInstance instance, VkPhysicalDevice physDevice, VkDevice device)
{
		vInstance = instance;
		vPhysicalDevice = physDevice;
		vDevice = device;
}

QueueFamilyIndices vulkanSwapchain::findQueueFamilies()
{
	if (vInstance == nullptr || vPhysicalDevice == nullptr || vDevice == nullptr)
	{
		throw std::runtime_error("Failed to call connect correctly!");
	}

	QueueFamilyIndices indices;

	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(vPhysicalDevice, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(vPhysicalDevice, &queueFamilyCount, queueFamilies.data());

	int i = 0;
	for (const auto& queueFamily : queueFamilies)
	{
		if (queueFamily.queueCount > 0 && queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			indices.graphicsFamily = i;
		}
		VkBool32 presentSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(vPhysicalDevice, i, surface, &presentSupport);

		if (queueFamily.queueCount > 0 && presentSupport)
		{
			indices.presentFamily = i;
		}

		if (indices.isComplete())
		{
			break;
		}

		++i;
	}
	return indices;
}

void vulkanSwapchain::create(uint32_t *width, uint32_t *height, bool vsync = true)
{
	VkResult err;
	VkSwapchainKHR oldSwapchain = swapChain; //old one is needed for the creation of a new one

	VkSurfaceCapabilitiesKHR surfCapabilities;
	err = vkGetPhysicalDeviceSurfaceCapabilitiesKHR(vPhysicalDevice, surface, &surfCapabilities);

	uint32_t presentModeCount;
	err = vkGetPhysicalDeviceSurfacePresentModesKHR(vPhysicalDevice, surface, &presentModeCount, nullptr);

	std::vector<VkPresentModeKHR> presentModes(presentModeCount);

	err = vkGetPhysicalDeviceSurfacePresentModesKHR(vPhysicalDevice, surface, &presentModeCount, presentModes.data());

	VkExtent2D swapchainExtent = {};
	if (surfCapabilities.currentExtent.width == (uint32_t)-1) //if this is special value we can set it
	{
		swapchainExtent.width = *width;
		swapchainExtent.height = *height;
	}
	else //otherwise we must force it to the capabilities of the swapchain
	{
		swapchainExtent = surfCapabilities.currentExtent;
		*width = surfCapabilities.currentExtent.width;
		*height = surfCapabilities.currentExtent.height;
	}

	VkPresentModeKHR swapchainPresentMode = VK_PRESENT_MODE_FIFO_KHR; //this mode waits for "vsync"

	if (!vsync) //otherwise the preference is mailbox, low latency but can result in tearing
	{
		for (size_t i = 0; i < presentModeCount; i++)
		{
			if (presentModes[i] == VK_PRESENT_MODE_MAILBOX_KHR)
			{
				swapchainPresentMode = VK_PRESENT_MODE_MAILBOX_KHR;
				break;
			}
			if ((swapchainPresentMode != VK_PRESENT_MODE_MAILBOX_KHR) && (presentModes[i] == VK_PRESENT_MODE_IMMEDIATE_KHR))
			{
				swapchainPresentMode = VK_PRESENT_MODE_IMMEDIATE_KHR;
			}
		}
	}

	uint32_t desiredNumberOfSwapchainImages = surfCapabilities.minImageCount + 1;
	if ((surfCapabilities.maxImageCount > 0) && (desiredNumberOfSwapchainImages > surfCapabilities.maxImageCount))
	{
		desiredNumberOfSwapchainImages = surfCapabilities.maxImageCount;
	}

	VkSurfaceTransformFlagsKHR preTransform;
	if (surfCapabilities.supportedTransforms & VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR)
	{
		preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR; 		// No rotation needed for the rendering
	}
	else
	{
		preTransform = surfCapabilities.currentTransform;
	}

	VkSwapchainCreateInfoKHR createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.pNext = NULL;
	createInfo.surface = surface;
	createInfo.minImageCount = desiredNumberOfSwapchainImages;
	createInfo.imageFormat = colorFormat;
	createInfo.imageColorSpace = colorSpace;
	createInfo.imageExtent = { swapchainExtent.width, swapchainExtent.height };
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
	createInfo.preTransform = (VkSurfaceTransformFlagBitsKHR)preTransform;
	createInfo.imageArrayLayers = 1;
	createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	createInfo.queueFamilyIndexCount = 0;
	createInfo.pQueueFamilyIndices = NULL;
	createInfo.presentMode = swapchainPresentMode;
	createInfo.oldSwapchain = oldSwapchain;
	createInfo.clipped = VK_TRUE; 	// clipping of geometry
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;

	err = vkCreateSwapchainKHR(vDevice, &createInfo, nullptr, &swapChain);
	if (err != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to create swapchain!");
	}

	//if there is an old swapchain, destroy it (memory leaks)
	if (oldSwapchain != VK_NULL_HANDLE)
	{
		for (uint32_t i = 0; i < imageCount; i++)
		{
			vkDestroyImageView(vDevice, buffers[i].view, nullptr);
		}
		vkDestroySwapchainKHR(vDevice, oldSwapchain, nullptr);
	}

	err = vkGetSwapchainImagesKHR(vDevice, swapChain, &imageCount, NULL);
	if (err != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to get swapchain Images!");
	}

	images.resize(imageCount);
	err = vkGetSwapchainImagesKHR(vDevice, swapChain, &imageCount, images.data());
	if (err != VK_SUCCESS)
	{
		throw std::runtime_error("Failed to get swapchain Images!");
	}
}
