#pragma once

#include "Common.h"
#include "Core.h"

namespace SPK
{
    namespace Vulkan
    {
        class Device;
        class ImageView;
        class Image
        {
        VULKAN_HANDLE(VkImage)
        public:
            Image(Device               *device,
                  VkImage               handle,
                  const VkExtent3D     &extent,
                  VkFormat              format,
                  VkImageUsageFlags     imageUsage,
                  VkSampleCountFlagBits sampleCount = VK_SAMPLE_COUNT_1_BIT);

            Image(Device               *device,
                  const VkExtent3D     &extent,
                  VkFormat              format,
                  VkImageUsageFlags     imageUsage,
                  VkSampleCountFlagBits sampleCount       = VK_SAMPLE_COUNT_1_BIT,
                  uint32_t                mipLevels         = 1,
                  uint32_t                arrayLayers       = 1,
                  VkImageTiling         tiling            = VK_IMAGE_TILING_OPTIMAL,
                  VkImageCreateFlags    flags             = 0,
                  uint32_t                numQueueFamilies  = 0,
                  const uint32_t*         queueFamilies     = nullptr);

            Image(Device            *device,
                  VkImageCreateInfo &createInfo);

            Image(const Image &other);

            Image(Image &&other);

            ~Image();

        public:

            Device* GetDevice()
            {
                return device;
            }

            const VkExtent3D &Extent() const
            {
                return info.extent;
            }

            const VkImageType &Type() const
            {
                return info.imageType;
            }

            const VkFormat& Format() const
            {
                return info.format;
            }

            const VkSampleCountFlagBits& SampleCount() const
            {
                return info.samples;
            }

            const VkImageUsageFlags& Usage() const
            {
                return info.usage;
            }

            const VkImageSubresource &Subresource() const
            {
                return subresource;
            }

            const VkImageCreateInfo &Info() const
            {
                return info;
            }

            std::unordered_set<ImageView *> &Views()
            {
                return views;
            }

            bool IsDepth() const
            {
                return IsDepthOnlyFormat(info.format);
            }

        private:

            Device *device{ nullptr };

            VkImageCreateInfo info{ VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO };

            VkImageSubresource subresource;

            std::unordered_set<ImageView*> views;

            unsigned char * mappedData{ nullptr };

            bool mapped{ false };
        };

    } // SPK
} // Vulkan
