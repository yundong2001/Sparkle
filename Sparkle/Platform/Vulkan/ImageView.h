#pragma once

#include "Common.h"
#include "Core.h"

namespace SPK
{
    namespace Vulkan
    {
        class Device;
        class Image;
        class ImageView
        {
        VULKAN_HANDLE(VkImageView)
        public:
            ImageView(Image          *image,
                      VkImageViewType viewType,
                      VkFormat        format         = VK_FORMAT_UNDEFINED,
                      uint32_t          baseMipLevel   = 0,
                      uint32_t          baseArrayLevel = 0,
                      uint32_t          nMipLevels     = 0,
                      uint32_t          nArrayLayers   = 0);

            ImageView(Device          *device,
                      VkImage          image,
                      VkImageViewType  viewType,
                      VkFormat         format,
                      uint32_t           baseMipLevel,
                      uint32_t           baseArrayLevel,
                      uint32_t           nMipLevels,
                      uint32_t           nArrayLayers
            );

            ImageView(ImageView &&other);

            ~ImageView();

            void Set(Image *image)
            {
                this->refImage = image;
            }

        private:
            void Setup(VkImage image, VkImageViewType viewType,
                       uint32_t baseMipLevel, uint32_t baseArrayLevel,
                       uint32_t nMipLevels, uint32_t nArrayLayers);

        private:

            Device* device{nullptr};

            Image *refImage{ nullptr };

            VkFormat format{};

            VkImageSubresourceRange subresourceRange{};
        };

    } // SPK
} // Vulkan
