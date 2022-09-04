#pragma once

#include "Common.h"
#include "Core.h"

namespace SPK
{
    namespace Vulkan
    {

        class Device;
        class RenderPass
        {
        VULKAN_HANDLE(VkRenderPass)

        public:
            RenderPass(Device *device, VkFormat colorFormat, VkFormat depthFormat ,bool isPresent = true);

            RenderPass(Device *device, VkRenderPassCreateInfo *pCreateInfo);

            ~RenderPass();

        private:
            Device* device{nullptr};

            VkFormat depthFormat{VK_FORMAT_UNDEFINED};

        };

    } // SPK
} // Vulkan
