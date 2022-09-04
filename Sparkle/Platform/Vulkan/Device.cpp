#include "Device.h"

namespace SPK
{
    namespace Vulkan
    {

        Device::Device(PhysicalDevice *physicalDevice,
                       VkSurfaceKHR surface,
                       std::unordered_map<const char *, bool> requestedExtensions)
                       :physicalDevice{physicalDevice},surface{surface}
        {
            uint32_t propCount = physicalDevice->QueueFamilyProperties.size();

            std::vector<VkDeviceQueueCreateInfo> queueCreateInfos(propCount,{VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO});
            std::vector<std::vector<float>> queueProps(propCount);

            for (int i = 0; i < propCount; ++i)
            {
                const VkQueueFamilyProperties& properties = physicalDevice->QueueFamilyProperties[i];
                queueProps[i].resize(properties.queueCount,0.5f);
                if(physicalDevice->HighPriorityGraphicsQueue && QueueFamilyIndex(VK_QUEUE_GRAPHICS_BIT) == i)
                {
                    queueProps[i][0]=1.0f;
                }
                queueCreateInfos[i].pNext = nullptr;
                queueCreateInfos[i].queueFamilyIndex = i;
                queueCreateInfos[i].queueCount = properties.queueCount;
                queueCreateInfos[i].pQueuePriorities = queueProps[i].data();
            }

            std::vector<VkExtensionProperties> deviceExtensions;
            uint32_t deviceExtensionCount;
            Check(physicalDevice->EnumerateDeviceExtensionProperties(nullptr, &deviceExtensionCount, nullptr));

            deviceExtensions.resize(deviceExtensionCount);
            Check(physicalDevice->EnumerateDeviceExtensionProperties(nullptr, &deviceExtensionCount, deviceExtensions.data()));

            for (auto &e : deviceExtensions)
            {
                availableExtensions.insert(e.extensionName);
            }

            if (!deviceExtensions.empty())
            {
                RENDER_DEBUG("Device supports the following extensions: ");
                for (auto &ext : deviceExtensions)
                {
                    RENDER_DEBUG("  \t{0}", ext.extensionName);
                }
            }

            //输出不支持的扩展
            std::vector<const char*> unsupportedExtensions{};
            for (auto &ext : requestedExtensions)
            {
                if (IsExtensionSupport(ext.first))
                {
                    enabledExtensions.emplace_back(ext.first);
                }
                else
                {
                    unsupportedExtensions.emplace_back(ext.first);
                }
            }

            if (!enabledExtensions.empty())
            {
                RENDER_DEBUG("Device supports the following requested extensions:");
                for (auto& ext : enabledExtensions)
                {
                    RENDER_DEBUG("  \t{0}", ext);
                }
            }

            if (!unsupportedExtensions.empty())
            {
                for (auto& ext : unsupportedExtensions)
                {
                    auto isOptional = requestedExtensions[ext];
                    if (isOptional)
                    {
                        RENDER_WARN("Optional device extension {0} not available. Some features may be disabled", ext);
                    }
                    else
                    {
                        RENDER_ERROR("Required device extension {0} not available. Stop running!", ext);
                        Check(VK_ERROR_EXTENSION_NOT_PRESENT);
                    }
                }
            }

            VkDeviceCreateInfo createInfo{};
            createInfo.sType                   = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
            //createInfo.pNext                   = physicalDevice->LastRequestedExtensionFeature;
            createInfo.queueCreateInfoCount    = uint32_t (queueCreateInfos.size());
            createInfo.pQueueCreateInfos       = queueCreateInfos.data();
            createInfo.enabledExtensionCount   = uint32_t(enabledExtensions.size());
            createInfo.ppEnabledExtensionNames = enabledExtensions.data();
            createInfo.pEnabledFeatures        = &physicalDevice->RequestedFeatures;

            Check(physicalDevice->CreateDevice(&createInfo,&handle));

            queues.resize(propCount);
            for (uint32_t queueFamilyIndex = 0; queueFamilyIndex < propCount; queueFamilyIndex++)
            {
                const auto& queueFamilyProps = physicalDevice->QueueFamilyProperties[queueFamilyIndex];
                VkBool32 presentSupported = surface ? physicalDevice->IsPresentSupported(surface, queueFamilyIndex) : false;

                for (uint32_t queueIndex = 0; queueIndex < queueFamilyProps.queueCount; queueIndex++)
                {
                    queues[queueFamilyIndex].emplace_back(this, queueFamilyIndex, queueFamilyProps, presentSupported, queueIndex);
                }
            }

            descriptorPool.reset(new DescriptorPool{this,PoolSize});
        }

        Device::~Device()
        {
            Wait();

            vkDestroyDevice(handle, nullptr);
        }

        void Device::GetQueue(uint32_t queueFamilyIndex, uint32_t queueIndex, VkQueue *pQueue)
        {
            return vkGetDeviceQueue(handle,queueFamilyIndex,queueIndex,pQueue);
        }

        uint32_t Device::QueueFamilyIndex(VkQueueFlagBits requestFlags)
        {
            const auto& queueFamlityProp = physicalDevice->QueueFamilyProperties;

            VkQueueFlags mask = 0;

            if (requestFlags & VK_QUEUE_COMPUTE_BIT)
            {
                mask |= VK_QUEUE_GRAPHICS_BIT;
            }

            if (requestFlags & VK_QUEUE_TRANSFER_BIT)
            {
                mask |= VK_QUEUE_GRAPHICS_BIT | VK_QUEUE_COMPUTE_BIT;
            }

            for (size_t i = 0; i < queueFamlityProp.size(); i++)
            {
                auto queueFlags = queueFamlityProp[i].queueFlags;
                if (queueFlags & requestFlags && !(queueFlags & mask))
                {
                    return uint32_t(i);
                    break;
                }
            }

            return 0;
        }

        Queue &Device::FindQueueByType(Queue::Type type, uint32_t queueIndex)
        {
            VkQueueFlags flags = VkQueueFlags(type);

            for (uint32_t familyIndex = 0; familyIndex < queues.size(); familyIndex++)
            {
                Queue& firstQueue = queues[familyIndex][0];

                VkQueueFlags queueFlags = firstQueue.Properties().queueFlags;
                uint32_t     queueCount = firstQueue.Properties().queueCount;

                if (((queueFlags & flags) == flags) && queueIndex < queueCount)
                {
                    return queues[familyIndex][queueIndex];
                }
            }

            RENDER_ERROR("Queue not found");
            return queues[0][0];
        }

        Queue &Device::SuitableGraphicsQueue()
        {
            for (uint32_t familyIndex = 0; familyIndex < queues.size(); familyIndex++)
            {
                Queue &firstQueue = queues[familyIndex][0];

                uint32_t queueCount = firstQueue.Properties().queueCount;

                if (firstQueue.IsPresentSupported() && 0 < queueCount)
                {
                    return queues[familyIndex][0];
                }
            }

            return FindQueueByType(Queue::Type::Graphics, 0);
        }

        VkResult Device::AllocateDescriptorSet(const VkDescriptorSetLayout *pDescriptorSetLayout,
                                               VkDescriptorSet *pDescriptorSets)
        {
            return descriptorPool->Allocate(pDescriptorSetLayout, pDescriptorSets);
        }

    } // SPK
} // Vulkan