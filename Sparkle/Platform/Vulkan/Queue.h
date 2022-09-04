#pragma once

#include "Core.h"
#include "Common.h"

#include "Render/Queue.h"

namespace SPK
{
    namespace Vulkan
    {
        class Device;
        class Queue : public SPK::Queue
        {
        VULKAN_HANDLE(VkQueue)

        public:

            Queue(Device* device , uint32_t familyIndex, VkQueueFamilyProperties properties, VkBool32 canPresent, uint32_t index);

            Queue(const Queue &) = default;

            Queue(Queue &&other);

            virtual ~Queue();

            VkResult Submit(VkSubmitInfo &submitInfo, VkFence fence)
            {
                return vkQueueSubmit(handle, 1, &submitInfo, fence);
            }

            void Wait()
            {
                vkQueueWaitIdle(handle);
            }

            VkQueueFamilyProperties &Properties()
            {
                return properties;
            }

            VkBool32 &IsPresentSupported()
            {
                return presented;
            }

            VkResult Present(VkPresentInfoKHR &presentInfo)
            {
                if (!presented)
                {
                    return VK_ERROR_INCOMPATIBLE_DISPLAY_KHR;
                }

                return vkQueuePresentKHR(handle, &presentInfo);
            }

        private:
            Device *device;

            uint32_t familyIndex{ 0 };

            uint32_t index{ 0 };

            VkBool32 presented{ VK_FALSE };

            VkQueueFamilyProperties properties{};
        };

    } // SPK
} // Vulkan
