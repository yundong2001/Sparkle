#pragma once

#include "Common.h"
#include "Core.h"

namespace SPK
{
    namespace Vulkan
    {
        class Device;
        class FrameBuffer
        {
        VULKAN_HANDLE(VkFramebuffer)

        public:
            FrameBuffer(Device* device, VkRenderPass renderPass, const std::vector<VkImageView> &views, const VkExtent2D &extent);

            ~FrameBuffer();

        private:
            Device* device{nullptr};
        };

    } // SPK
} // Vulkan
