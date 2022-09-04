#include "Swapchain.h"

namespace SPK
{
    namespace Vulkan
    {

        //helper
        inline uint32_t SelectImageCount(uint32_t request, uint32_t min, uint32_t max)
        {
            request = std::clamp(request,min,max);
            return request;
        }

        inline uint32_t SelectImageArrayLayers(uint32_t request, uint32_t max)
        {
            request = std::clamp(request, 1U, max);
            return request;
        }

        inline VkExtent2D SelectExtent(VkExtent2D request, const VkExtent2D &min, const VkExtent2D &max, const VkExtent2D &current)
        {
            if (request.width < 1 || request.height < 1)
            {
                RENDER_WARN("(Swapchain) Image extent ({0}, {1}) not supported. Selecting ({2}, {3}).",
                                           request.width, request.height, current.width, current.height);
                return current;
            }

            request.width = std::clamp(request.width, min.width, max.width);
            request.height = std::clamp(request.height, min.height, max.height);
            return request;
        }

        inline VkSurfaceFormatKHR SelectSurfaceFormat(const VkSurfaceFormatKHR request, const std::vector<VkSurfaceFormatKHR> &available, const std::vector<VkSurfaceFormatKHR> &priorities)
        {
            auto it = std::find_if(available.begin(), available.end(), [&request](const VkSurfaceFormatKHR &surface)
            {
                if (surface.format == request.format && surface.colorSpace == request.colorSpace)
                {
                    return true;
                }
                return false;
            });

            // If the requested surface format isn't found, then try to request a format from the priority list
            if (it == available.end())
            {
                for (auto &f : priorities)
                {
                    it = std::find_if(available.begin(), available.end(), [&f](const VkSurfaceFormatKHR &surface)
                    {
                        if (surface.format == f.format && surface.colorSpace == f.colorSpace)
                        {
                            return true;
                        }
                        return false;
                    });
                    if (it != available.end())
                    {
                        RENDER_WARN("(Swapchain) Surface format ({0}) not supported. Selecting ({1}).",
                                                   Stringify(request), Stringify(*it));
                        return *it;
                    }
                }
            }
            else
            {
                RENDER_WARN("(Swapchain) Surface format selected: {0}", Stringify(request));
            }
            return *it;
        }

        inline VkImageUsageFlags SelectImageUsage(VkImageUsageFlags &request, VkImageUsageFlags support, VkFormatFeatureFlags supportedFeatures)
        {
            VkImageUsageFlags validated = request & support;

            if (validated != request)
            {
                VkImageUsageFlagBits flag = VkImageUsageFlagBits(1);
                while (!(flag & request) && !(flag & validated))
                {
                    RENDER_WARN("(Swapchain) Image usage ({0}) requested but not supported.", Stringify(flag));
                    flag = VkImageUsageFlagBits((int)flag << 1);
                }
            }

            if (!validated)
            {
                validated = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT | VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT;
                validated &= support;
                if (VK_FORMAT_FEATURE_STORAGE_IMAGE_BIT & supportedFeatures)
                {
                    validated |= (VK_IMAGE_USAGE_STORAGE_BIT & support);
                }
            }

            if (!validated)
            {
                throw "No compatible image usage found.";
            }

            return validated;
        }

        inline VkImageUsageFlags CompositeImageFlags(const std::set<VkImageUsageFlagBits> &imageUsageFlags)
        {
            VkImageUsageFlags imageUsage{ 0 };
            for (auto flag : imageUsageFlags)
            {
                imageUsage |= flag;
            }
            return imageUsage;
        }

        inline VkSurfaceTransformFlagBitsKHR SelectTransform(VkSurfaceTransformFlagBitsKHR request, VkSurfaceTransformFlagsKHR support, VkSurfaceTransformFlagBitsKHR current)
        {
            if (request & support)
            {
                return request;
            }

            RENDER_WARN("(Swapchain) Surface transform '{0}' not supported. Selecting '{1}'.", Stringify(request), Stringify(current));

            return current;
        }

        inline VkCompositeAlphaFlagBitsKHR SelectCompositeAlpha(VkCompositeAlphaFlagBitsKHR request, VkCompositeAlphaFlagsKHR support)
        {
            if (request & support)
            {
                return request;
            }

            static const VkCompositeAlphaFlagBitsKHR compositeAlphaFlags[] = {
                    VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
                    VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR,
                    VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR,
                    VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR
            };

            for (size_t i = 0; i < sizeof(compositeAlphaFlags)/sizeof(compositeAlphaFlags[0]); i++)
            {
                if (compositeAlphaFlags[i] & support)
                {
                    RENDER_WARN("(Swapchain) Composite alpha '{0}' not supported. Selecting '{1}.",
                                               Stringify(request), Stringify(compositeAlphaFlags[i]));
                    return compositeAlphaFlags[i];
                }
            }

            assert(false && "No compatible composite alpha found.");
            return VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
        }

        inline VkPresentModeKHR SelectPresentMode(VkPresentModeKHR request, const std::vector<VkPresentModeKHR> &available, const std::vector<VkPresentModeKHR> &priorities)
        {
            auto it = std::find(available.begin(), available.end(), request);

            if (it == available.end())
            {
                // If nothing found, always default to FIFO
                VkPresentModeKHR chosen = VK_PRESENT_MODE_FIFO_KHR;

                for (auto &presentMode : priorities)
                {
                    if (std::find(available.begin(), available.end(), presentMode) != available.end())
                    {
                        chosen = presentMode;
                    }
                }
                RENDER_WARN("(Swapchain) Present mode '{}' not supported. Selecting '{}'.",
                        Stringify(request), Stringify(chosen));
                return chosen;
            }
            else
            {
                RENDER_WARN("(Swapchain) Present mode selected: {0}", Stringify(request));
                return *it;
            }
        }

        //Class member
        Swapchain::Swapchain(Swapchain &swapchain, const VkExtent2D &extent,
                             const VkSurfaceTransformFlagBitsKHR transform)
        {
            Create();
        }

        Swapchain::Swapchain(Device *device,
                             const VkExtent2D &extent,
                             const uint32_t imageCount,
                             const VkSurfaceTransformFlagBitsKHR transform,
                             const VkPresentModeKHR presentMode,
                             VkImageUsageFlags imageUsage):
                Swapchain(*this,device,extent,imageCount,transform,presentMode,imageUsage)
        {

        }

        Swapchain::Swapchain(Swapchain &oldSwapchain,
                             Device *device,
                             const VkExtent2D &extent,
                             const uint32_t imageCount,
                             const VkSurfaceTransformFlagBitsKHR transform,
                             const VkPresentModeKHR presentMode,
                             VkImageUsageFlags imageUsage):
                             device{device}
        {
            auto surface = device->GetSurface();

            VkPhysicalDevice physicalDevice = device->GetPhysicalDevice();
            VkSurfaceCapabilitiesKHR surfaceCapabilities{};
            Check(device->GetSurfaceCapabilities(&surfaceCapabilities));

            uint32_t surfaceFormatCount = 0;
            Check(vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &surfaceFormatCount, nullptr));
            surfaceFormats.resize(surfaceFormatCount);
            Check(vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, &surfaceFormatCount, surfaceFormats.data()));

            RENDER_DEBUG("Surface supports the following surface formats:");
            for (auto &f : surfaceFormats)
            {
                RENDER_DEBUG("  \t{0}",Stringify(f));
            }

            uint32_t presentModeCount = 0;
            Check(vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, nullptr));
            presentModes.resize(presentModeCount);
            Check(vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, &presentModeCount, presentModes.data()));

            RENDER_DEBUG("Surface supports the following present modes:");
            for (auto &p : presentModes)
            {
                RENDER_DEBUG("  \t{0}", Stringify(p));
            }

            this->properties.ImageCount    = SelectImageCount(imageCount, surfaceCapabilities.minImageCount, surfaceCapabilities.maxImageCount);
            this->properties.Extent        = SelectExtent(extent, surfaceCapabilities.minImageExtent, surfaceCapabilities.maxImageExtent, surfaceCapabilities.currentExtent);
            this->properties.ArrayLayers   = SelectImageArrayLayers(1, surfaceCapabilities.maxImageArrayLayers);
            this->properties.SurfaceFormat = SelectSurfaceFormat(this->properties.SurfaceFormat, surfaceFormats, priorities.SurfaceFormat);

            VkFormatProperties formatProperties;
            vkGetPhysicalDeviceFormatProperties(physicalDevice, this->properties.SurfaceFormat.format, &formatProperties);
            this->properties.ImageUsage     = SelectImageUsage(imageUsage, surfaceCapabilities.supportedUsageFlags, formatProperties.optimalTilingFeatures);
            this->properties.PreTransform   = SelectTransform(transform, surfaceCapabilities.supportedTransforms, surfaceCapabilities.currentTransform);
            this->properties.CompositeAlpha = SelectCompositeAlpha(VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR, surfaceCapabilities.supportedCompositeAlpha);

            this->properties.OldSwapchain   = oldSwapchain.handle;
            this->properties.PresentMode    = presentMode;
        }

        Swapchain::~Swapchain()
        {
            vkDestroySwapchainKHR(*device,handle, nullptr);
        }

        void Swapchain::Create()
        {
            // Revalidate the present mode and surface format
            properties.PresentMode   = SelectPresentMode(properties.PresentMode, presentModes, priorities.PresentMode);
            properties.SurfaceFormat = SelectSurfaceFormat(properties.SurfaceFormat, surfaceFormats, priorities.SurfaceFormat);

            VkSwapchainCreateInfoKHR createInfo{};
            createInfo.sType            = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
            createInfo.pNext            = nullptr;
            createInfo.minImageCount    = properties.ImageCount;
            createInfo.imageExtent      = properties.Extent;
            createInfo.presentMode      = properties.PresentMode;
            createInfo.imageFormat      = properties.SurfaceFormat.format;
            createInfo.imageColorSpace  = properties.SurfaceFormat.colorSpace;
            createInfo.imageArrayLayers = properties.ArrayLayers;
            createInfo.imageUsage       = properties.ImageUsage;
            createInfo.preTransform     = properties.PreTransform;
            createInfo.compositeAlpha   = properties.CompositeAlpha;
            createInfo.oldSwapchain     = properties.OldSwapchain;
            createInfo.surface          = device->GetSurface();
            createInfo.clipped          = VK_TRUE; // Get the best performance by enabling clipping.

            device->Create(&createInfo, &handle);

            uint32_t count = 0;
            Check(vkGetSwapchainImagesKHR(*device, handle, &count, nullptr));

            images.resize(count);
            Check(vkGetSwapchainImagesKHR(*device, handle, &count, images.data()));
        }

    } // SPK
} // Vulkan