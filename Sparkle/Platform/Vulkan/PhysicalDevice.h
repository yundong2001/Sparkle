#pragma once

#include "Core.h"
#include "Common.h"

#include "Instance.h"

namespace SPK
{
    namespace Vulkan
    {

        enum Feature : int {
            robustBufferAccess = 0,
            fullDrawIndexUint32,
            imageCubeArray,
            independentBlend,
            geometryShader,
            tessellationShader,
            sampleRateShading,
            dualSrcBlend,
            logicOp,
            multiDrawIndirect,
            drawIndirectFirstInstance,
            depthClamp,
            depthBiasClamp,
            fillModeNonSolid,
            depthBounds,
            wideLines,
            largePoints,
            alphaToOne,
            multiViewport,
            samplerAnisotropy,
            textureCompressionETC2,
            textureCompressionASTC_LDR,
            textureCompressionBC,
            occlusionQueryPrecise,
            pipelineStatisticsQuery,
            vertexPipelineStoresAndAtomics,
            fragmentStoresAndAtomics,
            shaderTessellationAndGeometryPointSize,
            shaderImageGatherExtended,
            shaderStorageImageExtendedFormats,
            shaderStorageImageMultisample,
            shaderStorageImageReadWithoutFormat,
            shaderStorageImageWriteWithoutFormat,
            shaderUniformBufferArrayDynamicIndexing,
            shaderSampledImageArrayDynamicIndexing,
            shaderStorageBufferArrayDynamicIndexing,
            shaderStorageImageArrayDynamicIndexing,
            shaderClipDistance,
            shaderCullDistance,
            shaderFloat64,
            shaderInt64,
            shaderInt16,
            shaderResourceResidency,
            shaderResourceMinLod,
            sparseBinding,
            sparseResidencyBuffer,
            sparseResidencyImage2D,
            sparseResidencyImage3D,
            sparseResidency2Samples,
            sparseResidency4Samples,
            sparseResidency8Samples,
            sparseResidency16Samples,
            sparseResidencyAliased,
            variableMultisampleRate,
            inheritedQueries
        };

        class PhysicalDevice
        {
        VULKAN_HANDLE(VkPhysicalDevice)

        public:

            PhysicalDevice() = default;

            PhysicalDevice(Instance *instance,VkPhysicalDevice physicalDevice);

            void Activate(Feature feature) const;

            void Deactivate(Feature feature) const;

        public:
            VkResult GetCapabilities(VkSurfaceKHR surface, VkSurfaceCapabilitiesKHR *pSurfaceCapabilities) const
            {
                return vkGetPhysicalDeviceSurfaceCapabilitiesKHR(handle, surface, pSurfaceCapabilities);
            }

            VkResult EnumerateDeviceExtensionProperties(const char *pLayerName, uint32_t *pPropertyCount, VkExtensionProperties* pProperties) const
            {
                return vkEnumerateDeviceExtensionProperties(handle, pLayerName, pPropertyCount, pProperties);
            }

            VkResult CreateDevice(const VkDeviceCreateInfo *pCreateInfo, VkDevice *pDevice, const VkAllocationCallbacks *pAllocator = nullptr) const
            {
                RENDER_INFO("Create Vulkan Device")
                return vkCreateDevice(handle, pCreateInfo, pAllocator, pDevice);
            }

            VkResult GetSurfaceSupport(uint32_t queueFamilyIndex, VkSurfaceKHR surface, VkBool32 *pSupported) const
            {
                return vkGetPhysicalDeviceSurfaceSupportKHR(handle, queueFamilyIndex, surface, pSupported);
            }

            void GetQueueFamilyProperties(uint32_t *pQueueFamilyPropertyCount, VkQueueFamilyProperties *pQueueFamilyProperties) const
            {
                vkGetPhysicalDeviceQueueFamilyProperties(handle, pQueueFamilyPropertyCount, pQueueFamilyProperties);
            }

            void GetFeatures(VkPhysicalDeviceFeatures *feature) const
            {
                return vkGetPhysicalDeviceFeatures(handle,feature);
            }

            void GetFeatures2KHR(VkPhysicalDeviceFeatures2KHR *feature) const
            {
                return vkGetPhysicalDeviceFeatures2KHR(handle,feature);
            }

            void GetProperties(VkPhysicalDeviceProperties *property) const
            {
                return vkGetPhysicalDeviceProperties(handle,property);
            }

            void GetMemoryProperties(VkPhysicalDeviceMemoryProperties *memoryProperties) const
            {
                return vkGetPhysicalDeviceMemoryProperties(handle,memoryProperties);
            }

        public:



            //TODO VkFormat GetSuitableDepthFormat(bool depthOnly = false)

            bool IsPresentSupported(VkSurfaceKHR surface, uint32_t queueFamilyIndex)
            {
                VkBool32 presentSupported = VK_FALSE;
                GetSurfaceSupport(queueFamilyIndex, surface, &presentSupported);

                return presentSupported;
            }

        private:

            Instance *instance{ nullptr };

        public:
            std::vector<VkQueueFamilyProperties> QueueFamilyProperties;

            std::unordered_map<VkStructureType, std::shared_ptr<void>> ExtensionFeatures;

            VkPhysicalDeviceFeatures Features;

            VkPhysicalDeviceProperties Properties;

            VkPhysicalDeviceMemoryProperties MemoryProperties;

            VkPhysicalDeviceFeatures RequestedFeatures;

            //Anonymous LastRequestedExtensionFeature{ nullptr };

            bool HighPriorityGraphicsQueue = true;
        };

    } // SPK
} // Vulkan
