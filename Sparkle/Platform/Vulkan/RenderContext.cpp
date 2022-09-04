#include "RenderContext.h"

#include "Image.h"
#include "ImageView.h"
#include "RenderTarget.h"

namespace SPK
{
    namespace Vulkan
    {
        std::unordered_map<const char *, bool> RenderContext::InstanceExtensions{
#if defined( _WIN32 )
            { "VK_KHR_win32_surface", false },
#elif defined( __linux__ )
        { "VK_KHR_xcb_surface",   false },
#endif
        };

        std::unordered_map<const char *, bool> RenderContext::DeviceExtensions{
                { VK_KHR_SWAPCHAIN_EXTENSION_NAME, false }
        };

        static std::vector<const char *> ValidationLayers = {
#ifndef NDEBUG
    "VK_LAYER_KHRONOS_validation",
    "VK_LAYER_KHRONOS_synchronization2",
    // "VK_LAYER_LUNARG_api_dump",
    // "VK_LAYER_LUNARG_device_simulation",
    // "VK_LAYER_LUNARG_assistant_layer",
    // "VK_LAYER_LUNARG_monitor",
    // "VK_LAYER_LUNARG_screenshot",
    // "VK_LAYER_RENDERDOC_Capture",
#endif
        };

        RenderContext::RenderContext(const Description &desc) : window{desc.WindowHandle}
        {
            instance = std::make_unique<Instance>(desc.ApplicationName,InstanceExtensions,ValidationLayers);

            CreateSurface();

            auto& physicalDevice = instance->SuitablePhysicalDevice();

            device.reset(new Device{&physicalDevice,surface,DeviceExtensions});
            queue = device->SuitableGraphicsQueuePtr();

            surfaceExtent = VkExtent2D{ desc.Width, desc.Height };
            if (surface != VK_NULL_HANDLE)
            {
                VkSurfaceCapabilitiesKHR surfaceProperties{};
                Check(device->GetSurfaceCapabilities(&surfaceProperties));

                if (surfaceProperties.currentExtent.width == 0xFFFFFFFF)
                {
                    swapchain = std::make_unique<Swapchain>(device.get(), surfaceExtent);
                }
                else
                {
                    swapchain = std::make_unique<Swapchain>(device.get());
                }

                Prepare();
            }


        }

        RenderContext::~RenderContext() noexcept
        {
            instance->DestroySurface(surface, nullptr);
        }

        void SPK::Vulkan::RenderContext::CreateSurface()
        {
            Check(instance->CreateSurface(window,&surface));
        }

        void RenderContext::Prepare(size_t threadCount)
        {
            device->Wait();

            swapchain->Create();

            renderPass.reset(new RenderPass{device.get(),swapchain->GetFormat(),depthFormat});

            surfaceExtent = swapchain->GetExtent2D();
            VkExtent3D extent{ surfaceExtent.width, surfaceExtent.height, 1 };

            std::vector<ImageView> views;

            for (auto &handle : swapchain->GetImage())
            {
                auto image = std::make_unique<Image>(
                        device.get(),
                        handle,
                        extent,
                        swapchain->GetFormat(),
                        swapchain->GetImageUsageFlagBits()
                );
                //auto renderTarget = RenderTarget::Create(std::move(image));
                //renderTarget->Set(renderPass);
                //present.renderTargets.emplace_back(std::move(renderTarget));
            }
        }
    }
}

