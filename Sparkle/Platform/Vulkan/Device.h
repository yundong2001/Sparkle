#pragma once

#include "Core.h"
#include "Common.h"

#include "PhysicalDevice.h"
#include "Queue.h"
#include "DescriptorPool.h"

namespace SPK
{
    namespace Vulkan
    {

        class Device
        {
        VULKAN_HANDLE(VkDevice)

        public:

            Device() = default;

            Device(PhysicalDevice* physicalDevice,VkSurfaceKHR surface,std::unordered_map<const char *, bool> requestedExtensions = {});

            ~Device();

            void GetQueue(uint32_t queueFamilyIndex, uint32_t queueIndex, VkQueue *pQueue);

            uint32_t QueueFamilyIndex(VkQueueFlagBits flagBit);

            Queue &FindQueueByType(Queue::Type type, uint32_t queueIndex);

            Queue &SuitableGraphicsQueue();

            Queue *SuitableGraphicsQueuePtr()
            {
                auto &queue = SuitableGraphicsQueue();
                return &queue;
            }

            bool IsExtensionSupport(const std::string &extension) const
            {
                return availableExtensions.find(extension) != availableExtensions.end();
            }

        public:
            VkResult AllocateDescriptorSet(const VkDescriptorSetLayout *pDescriptorSetLayout, VkDescriptorSet *pDescriptorSets);

#define DEFINE_CREATE_VK_OBJECT(T) \
    VkResult Create(const Vk##T##CreateInfo *pCreateInfo, Vk##T *pObject, VkAllocationCallbacks *pAllocator = nullptr) \
    {                              \
        RENDER_INFO("Create Vulkan {}",#T)                           \
        return vkCreate##T(handle, pCreateInfo, pAllocator, pObject); \
    }

#define DEFINE_DESTORY_VK_OBJECT(T) \
    void Destroy(Vk##T object, const VkAllocationCallbacks *pAllocator = nullptr) \
        { \
            if (object != VK_NULL_HANDLE) \
            { \
                vkDeviceWaitIdle(handle); \
                vkDestroy##T(handle, object, pAllocator); \
            } \
        }

#define DEFINE_CREATE_VK_KHR_OBJECT(T) \
    VkResult Create(const Vk##T##CreateInfoKHR *pCreateInfo, Vk##T##KHR *pObject, VkAllocationCallbacks *pAllocator = nullptr) \
    {                                  \
        RENDER_INFO("Create Vulkan {}KHR",#T)\
        return vkCreate##T##KHR(handle, pCreateInfo, pAllocator, pObject); \
    }

            DEFINE_CREATE_VK_KHR_OBJECT(Swapchain)

            DEFINE_CREATE_VK_OBJECT(ImageView)
            DEFINE_DESTORY_VK_OBJECT(ImageView)
            DEFINE_CREATE_VK_OBJECT(Image)
            DEFINE_DESTORY_VK_OBJECT(Image)
            DEFINE_CREATE_VK_OBJECT(RenderPass)
            DEFINE_DESTORY_VK_OBJECT(RenderPass)
            DEFINE_CREATE_VK_OBJECT(Framebuffer)
            DEFINE_DESTORY_VK_OBJECT(Framebuffer)
            DEFINE_CREATE_VK_OBJECT(Sampler)
            DEFINE_DESTORY_VK_OBJECT(Sampler)
            DEFINE_CREATE_VK_OBJECT(DescriptorPool)
            DEFINE_DESTORY_VK_OBJECT(DescriptorPool)

        public:

            VkResult Wait()
            {
                return vkDeviceWaitIdle(handle);
            }

            VkResult Wait(const VkFence *pFences, uint32_t fenceCount = 1, VkBool32 waitAll = VK_TRUE, uint64_t timeout = std::numeric_limits<uint64_t>::max()) const
            {
                return vkWaitForFences(handle, fenceCount, pFences, waitAll, timeout);
            }

            VkSurfaceKHR GetSurface() const
            {
                return surface;
            }

            PhysicalDevice GetPhysicalDevice() const
            {
                return *physicalDevice;
            }

            VkResult GetSurfaceCapabilities(VkSurfaceCapabilitiesKHR *properties)
            {
                return physicalDevice->GetCapabilities(surface, properties);
            }

        private:
            PhysicalDevice *physicalDevice{ nullptr };

            VkSurfaceKHR surface{ VK_NULL_HANDLE };

            std::unordered_set<std::string> availableExtensions;

            std::vector<const char *> enabledExtensions;

            std::vector<std::vector<Queue>> queues;

            std::unique_ptr<DescriptorPool> descriptorPool;
        };

    } // SPK
} // Vulkan
