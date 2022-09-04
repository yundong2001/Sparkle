#pragma once

#include "Core.h"

#include "Common.h"

namespace SPK
{
    class Window;
    namespace Vulkan
    {

        class PhysicalDevice;
        class Instance
        {
            VULKAN_HANDLE(VkInstance);

        public:
            Instance() = default;

            Instance(const char*                                  applicationName,
                     const std::unordered_map<const char*, bool> &requiredExtension        = {},
                     const std::vector<const char*>&              requiredValidationLayers = {},
                     bool                                         headless                 = false,
                     uint32_t                                     apiVersion               = VK_API_VERSION_1_2);

            Instance(VkInstance instance);

            ~Instance();

            PhysicalDevice &SuitablePhysicalDevice();

            void QueryPhysicalDevice();

        public: /* vk api */
            VkResult EnumeratePhysicalDevices(uint32_t *physicalDeviceCount, VkPhysicalDevice *pPhysicalDevice) const
            {
                return vkEnumeratePhysicalDevices(handle, physicalDeviceCount, pPhysicalDevice);
            }

            template <class T>
            T GetProcAddr(const std::string &func) const
            {
                return (T)vkGetInstanceProcAddr(handle, func.c_str());
            }

            void DestroySurface(VkSurfaceKHR surface, const VkAllocationCallbacks *pAllocator = nullptr) const
            {
                vkDestroySurfaceKHR(handle, surface, pAllocator);
            }

            VkResult CreateSurface(Window *window, VkSurfaceKHR *pSurface, const VkAllocationCallbacks *pAllocator = nullptr) const;

        public:
            bool IsEnabled(const char *extension) const
            {
                return std::find_if(enabledExtensions.begin(), enabledExtensions.end(),
                                    [extension](const char *enabledExtension)
                                    {
                                        return (extension == enabledExtension);
                                    }) != enabledExtensions.end();
            }

            bool Ready() const
            {
                return !!handle;
            }

        private:
            std::vector<const char*> enabledExtensions{};

            std::vector<std::unique_ptr<PhysicalDevice>> physicalDevices{};

#ifndef NDEBUG
    VkDebugUtilsMessengerEXT debugUtilsMessengers{ VK_NULL_HANDLE };

    VkDebugReportCallbackEXT debugReportCallback{ VK_NULL_HANDLE };
#endif
        };

    } // SPK
} // Vulkan
