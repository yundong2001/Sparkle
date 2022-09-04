#include "Instance.h"

#include "GLFW/glfw3.h"

#include "Framework/Window.h"

#include "PhysicalDevice.h"
namespace SPK
{
    namespace Vulkan
    {
        VkResult CreateDebugUtilsMessengerEXT(
                VkInstance instance, const
                VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo, const
                VkAllocationCallbacks *pAllocator,
                VkDebugUtilsMessengerEXT *pCallback)
        {
            auto func = (PFN_vkCreateDebugUtilsMessengerEXT)
                    vkGetInstanceProcAddr(instance,
                                          "vkCreateDebugUtilsMessengerEXT");
            if (func != nullptr)
            {
                return func(instance, pCreateInfo, pAllocator, pCallback);
            } else
            {
                return VK_ERROR_EXTENSION_NOT_PRESENT;
            }
        }

        VkResult CreateDebugReportCallbackEXT(
                VkInstance instance, const
        VkDebugReportCallbackCreateInfoEXT *pCreateInfo,
                const VkAllocationCallbacks *pAllocator,
                VkDebugReportCallbackEXT *pCallback)
        {
            auto func = (PFN_vkCreateDebugReportCallbackEXT)
                    vkGetInstanceProcAddr(instance,"vkCreateDebugReportCallbackEXT");
            if (func != nullptr)
            {
                return func(instance, pCreateInfo, pAllocator, pCallback);
            } else
            {
                return VK_ERROR_EXTENSION_NOT_PRESENT;
            }
        }

        void DestroyDebugUtilsMessengerEXT(VkInstance instance,
                                           VkDebugUtilsMessengerEXT callback, const
                                           VkAllocationCallbacks *pAllocator)
        {
            auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)
                    vkGetInstanceProcAddr(instance,
                                          "vkDestroyDebugUtilsMessengerEXT");
            if (func != nullptr)
            {
                func(instance, callback, pAllocator);
            }
        }

        void DestroyDebugReportCallbackEXT(VkInstance instance,
                                           VkDebugReportCallbackEXT callback, const
                                           VkAllocationCallbacks *pAllocator)
        {
            auto func = (PFN_vkDestroyDebugReportCallbackEXT)
                    vkGetInstanceProcAddr(instance,
                                          "vkDestroyDebugReportCallbackEXT");
            if (func != nullptr)
            {
                func(instance, callback, pAllocator);
            }
        }

        static VKAPI_ATTR VkBool32 VKAPI_CALL DebugUtilsMessengerCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
                                                                          VkDebugUtilsMessageTypeFlagsEXT messageType,
                                                                          const VkDebugUtilsMessengerCallbackDataEXT *callbackData,
                                                                          void *userData)
        {
            switch (messageSeverity)
            {
                case VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT:
                case VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT:
                    RENDER_INFO("{0} - {1}: {2}", callbackData->messageIdNumber, callbackData->pMessageIdName, callbackData->pMessage);
                    break;
                case VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT:
                    RENDER_WARN("{0} - {1}: {2}", callbackData->messageIdNumber, callbackData->pMessageIdName, callbackData->pMessage);
                    break;
                case VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT:
                default:
                    RENDER_ERROR("{0} - {1}: {2}", callbackData->messageIdNumber, callbackData->pMessageIdName, callbackData->pMessage);
                    break;
            }

            return VK_FALSE;
        }

        static VKAPI_ATTR VkBool32 VKAPI_CALL DebugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT /*type*/,
                                                            uint64_t /*object*/,  size_t /*location*/, int32_t /*message_code*/,
                                                            const char *layerPrefix, const char *message,void * /*userData*/)
        {
            switch (flags)
            {
                case VK_DEBUG_REPORT_ERROR_BIT_EXT:
                    RENDER_ERROR("{0}: {1}", layerPrefix, message);
                    break;
                case VK_DEBUG_REPORT_WARNING_BIT_EXT:
                case VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT:
                    RENDER_WARN("{0}: {1}", layerPrefix, message);
                    break;
                default:
                    RENDER_INFO("{0}: {1}", layerPrefix, message);
                    break;
            }

            return VK_FALSE;
        }

        static bool ValidateLayers(const std::vector<const char *> &required, const std::vector<VkLayerProperties> &available)
        {
            for (auto &layer : required)
            {
                bool found = false;
                for (auto &availableLayer : available)
                {
                    if (strcmp(layer, availableLayer.layerName) == 0)
                    {
                        found = true;
                        break;
                    }
                }
                if (!found)
                {
                    RENDER_ERROR("Validation Layer {} not found", layer);
                    return false;
                }
            }

            return true;
        }

        static inline void VkEnableExtension(const char *message)
        {
            RENDER_INFO("{0} is available. Enabling it!", message);
        }

        Instance::Instance(const char *applicationName,
                           const std::unordered_map<const char *, bool> &requiredExtension,
                           const std::vector<const char *> &requiredValidationLayers,
                           bool headless,
                           uint32_t apiVersion)
        {
            //寻找可用的Extension,并和需要的extension作比较
            uint32_t extensionCount;
            vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
            std::vector<VkExtensionProperties> availableExtension{ extensionCount };
            vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, availableExtension.data());

            uint64_t extensionsFlags = 0;
            static std::vector<const char*> utilsExtensions = {
                    { VK_EXT_DEBUG_UTILS_EXTENSION_NAME                      },
                    { VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME                 },
                    { VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME },
            };

            for (size_t i = 0; i < utilsExtensions.size(); i++)
            {
                auto &extension = utilsExtensions[i];
                for (size_t j = 0; j < availableExtension.size(); j++)
                {
                    if (strcmp(availableExtension[j].extensionName, extension) == 0)
                    {
                        extensionsFlags |= BIT(i);
                        VkEnableExtension(extension);
                        enabledExtensions.push_back(extension);
                    }
                }
            }

            if (headless && !(extensionsFlags & BIT(1)))
            {
                RENDER_WARN("{0} is not available. Disabling swapchain creation", VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME);
            }
            else
            {
                enabledExtensions.emplace_back(VK_KHR_SURFACE_EXTENSION_NAME);
            }

            if (!(extensionsFlags & BIT(0)) /* not debug utils */)
            {
                enabledExtensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);
            }

            for (auto &requird : requiredExtension)
            {
                auto extension  = requird.first;
                auto isOptional = requird.second;

                if (std::find_if(availableExtension.begin(), availableExtension.end(), [&extension](VkExtensionProperties &availableExtension)
                {
                    return strcmp(availableExtension.extensionName, extension) == 0;
                }) == availableExtension.end())
                {
                    if (isOptional)
                    {
                        RENDER_WARN("Optional instance extension {0} not available, some features may be disabled", extension);
                    }
                    else
                    {
                        RENDER_ERROR("Required instance extension {0} not available, cannot run", extension);
                        RENDER_ERROR("Required instance extensions are missing.");
                    }
                }
                else
                {
                    enabledExtensions.emplace_back(extension);
                }
            }

            //寻找可用Layer和Required Layer比较
            uint32_t layerCount;
            vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

            std::vector<VkLayerProperties> supportedValidationLayers(layerCount);
            vkEnumerateInstanceLayerProperties(&layerCount, supportedValidationLayers.data());

            if (ValidateLayers(requiredValidationLayers, supportedValidationLayers))
            {
                RENDER_INFO("Enabled Validation Layers: ");
                for (const auto &layer : requiredValidationLayers)
                {
                    RENDER_DEBUG("  \t{0}", layer);
                }
            }
            else
            {
                RENDER_DEBUG("Required validation layers are missing.");
            }

            //初始化Vkinstance
            VkApplicationInfo applicationInfo{};
            applicationInfo.pApplicationName = applicationName;
            applicationInfo.applicationVersion = VK_MAKE_VERSION(1,0,0);
            applicationInfo.pEngineName = applicationName;
            applicationInfo.engineVersion = VK_MAKE_VERSION(1,0,0);
            applicationInfo.apiVersion = apiVersion;

            VkInstanceCreateInfo createInfo{};
            createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
            createInfo.pNext = nullptr;
            createInfo.pApplicationInfo = &applicationInfo;
            createInfo.ppEnabledExtensionNames = enabledExtensions.data();
            createInfo.enabledExtensionCount = enabledExtensions.size();
            createInfo.ppEnabledLayerNames = requiredValidationLayers.data();
            createInfo.enabledLayerCount = requiredValidationLayers.size();

#ifndef NDEBUG
            VkDebugUtilsMessengerCreateInfoEXT debugUtilsCreateInfo = { VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT };
            VkDebugReportCallbackCreateInfoEXT debugReportCreateInfo = { VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT };

            if (extensionsFlags & BIT(0))
            {
                debugUtilsCreateInfo.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT;
                debugUtilsCreateInfo.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
                debugUtilsCreateInfo.pfnUserCallback =DebugUtilsMessengerCallback;

                createInfo.pNext = &debugUtilsCreateInfo;
            }
            else
            {
                debugReportCreateInfo.flags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT | VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT;
                debugReportCreateInfo.pfnCallback =DebugCallback;

                createInfo.pNext = &debugReportCallback;
            }
#endif

            VkResult  a = vkCreateInstance(&createInfo, nullptr,&handle);
            //创建Instance
            if( a != VK_SUCCESS)
            {
                RENDER_WARN("Failed To Create VkInstance")
            } else
            {
                RENDER_INFO("Create VkInstance")
            }

            //Debug模式下开启Messager
#ifndef NDEBUG
            if (extensionsFlags & BIT(0))
            {
                if(CreateDebugUtilsMessengerEXT(handle, &debugUtilsCreateInfo, nullptr, &debugUtilsMessengers) != VK_SUCCESS)
                {
                    RENDER_WARN("Failed To Create VkDebugUtilsMessengerEXT")
                } else
                {
                    RENDER_DEBUG("Create VkDebugUtilsMessengerEXT")
                }
            }
            else
            {
                if(CreateDebugReportCallbackEXT(handle, &debugReportCreateInfo, nullptr, &debugReportCallback) != VK_SUCCESS)
                {
                    RENDER_WARN("Failed To Create VkDebugReportCallbackEXT")
                } else
                {
                    RENDER_DEBUG("Create VkDebugReportCallbackEXT")
                }
            }
#endif

            //查询并存储所有可用PD
            QueryPhysicalDevice();
        }

        Instance::Instance(VkInstance instance):handle(instance)
        {
            if (handle != VK_NULL_HANDLE)
            {
                throw std::runtime_error("Instance is not valid!");
            }
            QueryPhysicalDevice();
        }

        Instance::~Instance()
        {
#ifndef NDEBUG
    if (debugUtilsMessengers)
    {
        DestroyDebugUtilsMessengerEXT(handle, debugUtilsMessengers, nullptr);
    }
    if (debugReportCallback)
    {
        DestroyDebugReportCallbackEXT(handle, debugReportCallback, nullptr);
    }
#endif
            if (handle)
            {
                vkDestroyInstance(handle, nullptr);
            }
        }

        void Instance::QueryPhysicalDevice()
        {
            uint32_t count{ 0 };
            EnumeratePhysicalDevices(&count, nullptr);

            if (!count)
            {
                throw std::runtime_error("Couldn't find a physical device that supports Vulkan.");
            }

            std::vector<VkPhysicalDevice> physicalDevices{ count };
            EnumeratePhysicalDevices(&count, physicalDevices.data());

            for (auto &pd : physicalDevices)
            {
                this->physicalDevices.emplace_back(std::make_unique<PhysicalDevice>(this, pd));
            }
        }


        PhysicalDevice &Instance::SuitablePhysicalDevice()
        {
            if (physicalDevices.empty())
            {
                throw std::runtime_error("There is no GPU on this device.");
            }

            for (auto &physicalDevice : physicalDevices)
            {
                if (physicalDevice->Properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
                {
                    return *physicalDevice;
                }
            }

            if (physicalDevices[0]->Properties.deviceType == VK_PHYSICAL_DEVICE_TYPE_CPU)
            {
                throw std::runtime_error("No physical device available on this host!");
            }

            RENDER_WARN("Couldn't find a discrete physical device. Picking the default.");
            return *physicalDevices.at(0);
        }

        VkResult Instance::CreateSurface(Window *window, VkSurfaceKHR *pSurface,
                                         const VkAllocationCallbacks *pAllocator) const
        {
            return glfwCreateWindowSurface(handle,(GLFWwindow*)(window->GetNativeWindow()),pAllocator,pSurface);
        }

    } // SPK
} // Vulkan