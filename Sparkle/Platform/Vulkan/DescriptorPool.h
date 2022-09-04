#pragma once

#include "Common.h"
#include "Core.h"

namespace SPK
{
    namespace Vulkan
    {
        class Device;
        class DescriptorSetLayout;
        class DescriptorPool
        {
        public:
            static constexpr uint32_t MaxSetsPerPool = 1000;

        public:
            DescriptorPool(Device *device, const DescriptorSetLayout &layout, uint32_t poolSize = MaxSetsPerPool);

            DescriptorPool(Device *device, const std::vector<VkDescriptorPoolSize> &poolSize);

            ~DescriptorPool();

            VkResult Allocate(const VkDescriptorSetLayout *pDescriptorSetLayout, VkDescriptorSet *pDescriptorSet, uint32_t count = 1);

            void Free(VkDescriptorSet *pDescriptorSets, uint32_t size = 1);

            VkDescriptorPool Handle() const
            {
                return handles.back();
            }

            operator VkDescriptorPool() const
            {
                return Handle();
            }
        private:
            VkDescriptorPool Create();

            VkResult AllocateInternal(const VkDescriptorSetLayout *pDescriptorSetLayout, VkDescriptorSet *pDescriptorSet, uint32_t count);

        private:
            Device* device{nullptr};

            std::vector<VkDescriptorPool> handles{ VK_NULL_HANDLE };

            std::vector<VkDescriptorPoolSize> poolSize;

            uint32_t allocatedCount = 0;
        };

    } // SPK
} // Vulkan
