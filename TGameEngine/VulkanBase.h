#pragma once

#define GLFW_INCLUDE_VULKAN
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <GLFW\glfw3.h>
#include <map>
#include <array>
#include <vulkan\vulkan.h>
#include "VulkanHelper.h"
#include "vulkanSwapchain.h"

//struct QueueFamilyIndices
//{
//	int graphicsFamily = -1;
//	int presentFamily = -1;
//
//	bool isComplete()
//	{
//		return graphicsFamily >= 0 && presentFamily >= 0;
//	}
//};

struct SwapChainSupportDetails
{
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

struct FrameBufferAttachment {
	VkImage image;
	VkDeviceMemory mem;
	VkImageView view;
	VkFormat format;
	void destroy(VkDevice device)
	{
		vkDestroyImage(device, image, nullptr);
		vkDestroyImageView(device, view, nullptr);
		vkFreeMemory(device, mem, nullptr);
	}
};

struct FrameBuffer {
	int32_t width, height;
	VkFramebuffer frameBuffer;
	FrameBufferAttachment depth;
	VkRenderPass renderPass;
	void setSize(int32_t w, int32_t h)
	{
		this->width = w;
		this->height = h;
	}
	void destroy(VkDevice device)
	{
		vkDestroyFramebuffer(device, frameBuffer, nullptr);
		vkDestroyRenderPass(device, renderPass, nullptr);
	}
};


struct {
	struct Offscreen : public FrameBuffer {
		std::array<FrameBufferAttachment, 3> attachments;
	} offscreen;
	struct SSAO : public FrameBuffer {
		std::array<FrameBufferAttachment, 1 > attachments;
	} ssao, ssaoBlur;
} frameBuffers;


class VulkanBase
{
public:
	void Initialise();
	VulkanBase();
	~VulkanBase();

private:
	GLFWwindow* pWindow = nullptr;

	VkInstance vInstance;
	VkDevice device;
	VkQueue queue;
	VkDebugReportCallbackEXT callback;
	VkSurfaceKHR surface;
	VkQueue graphicsQueue;
	VkQueue presentQueue;
	VkDevice logicalDevice;
	VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
	VkFormat swapChainImageFormat;
	std::vector<VkImage> swapChainImages;
	std::vector<VkImageView> swapchainImageViews;
	VkExtent2D swapChainExtent;
	VkSwapchainKHR swapChain;
	VkRenderPass renderPass;
	vulkanSwapchain swapchain;

	uint32_t windowHeight;
	uint32_t windowWidth;

	//VULKAN FUNCTIONS
	void createInstance();
	void setupDebugCallBack();
	void createSurface();
	QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
	void createLogicalDevice();
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR & capabilities);
	SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);
	void createImageViews();
	void createRenderPass();
	bool isDeviceSuitable(VkPhysicalDevice device);
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	void pickPhysicalDevice();
	void createSwapChain();
	void createWindow();
	void readConfig();
};

