#pragma once

#include "vulkan/vulkan.h"

#include "Render/RenderContext.h"
#include "Instance.h"
#include "Device.h"
#include "Swapchain.h"
#include "RenderPass.h"

namespace SPK
{
    namespace Vulkan
    {

        class RenderContext : public SuperRenderContext
        {
        public:
            RenderContext(const Description& desc);

            virtual ~RenderContext();

            static VkDescriptorSetLayout DescriptorSetLayout;
            static std::unordered_map<const char *, bool> InstanceExtensions;
            static std::unordered_map<const char *, bool> DeviceExtensions;

        public:
            void CreateSurface();

            void Prepare(size_t threadCount = 1);

        private:
            Window* window{nullptr};

            std::unique_ptr<Instance> instance;

            std::shared_ptr<Device> device;

            VkSurfaceKHR surface{VK_NULL_HANDLE};

            Queue *queue{ nullptr };

            std::unique_ptr<Swapchain> swapchain;

            VkExtent2D surfaceExtent{ 0, 0 };

            std::shared_ptr<RenderPass> renderPass;

            VkFormat depthFormat{ VK_FORMAT_UNDEFINED };
        };

    } // SPK
} // Vulkan
