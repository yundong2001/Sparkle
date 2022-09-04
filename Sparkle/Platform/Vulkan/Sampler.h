#pragma once

#include "Common.h"
#include "Core.h"

#include "Render/Texture.h"

namespace SPK
{
    namespace Vulkan
    {

        class Device;
        class Sampler
        {
        VULKAN_HANDLE(VkSampler)

            Sampler(Device* device , Texture::Description &description,uint32_t mipmapLevel = 1);

            Sampler(Device* device , VkSamplerCreateInfo &createInfo);

            ~Sampler();

        private:
            Device* device{nullptr};
        };

    } // SPK
} // Vulkan
