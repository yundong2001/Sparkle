#include "FrameBuffer.h"

#include "Device.h"

namespace SPK
{
    namespace Vulkan
    {
        FrameBuffer::FrameBuffer(Device *device, VkRenderPass renderPass, const std::vector<VkImageView> &views,
                                 const VkExtent2D &extent):
                                 device{device}
        {
            VkFramebufferCreateInfo createInfo{};
            createInfo.sType           = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
            createInfo.pNext           = nullptr;
            createInfo.attachmentCount = uint32_t (views.size());
            createInfo.pAttachments    = views.data();
            createInfo.renderPass      = renderPass;
            createInfo.width           = extent.width;
            createInfo.height          = extent.height;
            createInfo.layers          = 1;

            Check(device->Create(&createInfo, &handle));
        }

        FrameBuffer::~FrameBuffer()
        {
            if (device)
            {
                device->Destroy(handle);
            }
        }
    } // SPK
} // Vulkan