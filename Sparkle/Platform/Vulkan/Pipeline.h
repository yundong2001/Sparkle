#pragma once

#include "Common.h"
#include "Core.h"

namespace SPK
{
    namespace Vulkan
    {
        class Device;
        class Pipeline
        {

            VULKAN_HANDLE(VkPipeline)

            struct DescriptorSetPack
            {
                static constexpr size_t Size = 3;

                uint32_t Sync = 0;

                VkDescriptorSet DescriptorSets[Size];
            };

        public:


        public:
            bool Ready();

            void Update();

            void Destroy();

        private:

            Device* device;


        };

    } // SPK
} // Vulkan
