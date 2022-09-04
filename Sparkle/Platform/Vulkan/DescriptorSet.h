#pragma once

#include "Common.h"
#include "Core.h"

namespace SPK
{
    namespace Vulkan
    {
        class Device;
        class DescriptorSet
        {
        VULKAN_HANDLE(VkDescriptorSet)

        public:
            DescriptorSet(Device *device, const VkDescriptorSetLayout &descriptorSetLayout);

            DescriptorSet(const VkDescriptorSet other);

            ~DescriptorSet();
        private:
            Device* device{nullptr};
        };

    } // SPK
} // Vulkan
