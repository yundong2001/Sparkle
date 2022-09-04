#include "RenderPass.h"

#include "Device.h"
namespace SPK
{
    namespace Vulkan
    {
        RenderPass::RenderPass(Device *device, VkFormat colorFormat, VkFormat depthFormat, bool isPresent):
                device{ device },
                depthFormat{ depthFormat }
        {
            bool HasDepth {depthFormat != VK_FORMAT_UNDEFINED};

            std::vector<VkAttachmentDescription> attachments;

            VkAttachmentDescription colorAttachment{};
            colorAttachment.format         = colorFormat;
            colorAttachment.samples        = VK_SAMPLE_COUNT_1_BIT;
            colorAttachment.loadOp         = VK_ATTACHMENT_LOAD_OP_CLEAR;
            colorAttachment.storeOp        = VK_ATTACHMENT_STORE_OP_STORE;
            colorAttachment.stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
            colorAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
            colorAttachment.initialLayout  = VK_IMAGE_LAYOUT_UNDEFINED;
            colorAttachment.finalLayout    = isPresent ? VK_IMAGE_LAYOUT_PRESENT_SRC_KHR : VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
            attachments.push_back(colorAttachment);

            if(HasDepth)
            {
                VkAttachmentDescription depthAttachment{};
                depthAttachment.format         = depthFormat;
                depthAttachment.samples        = VK_SAMPLE_COUNT_1_BIT;
                depthAttachment.loadOp         = VK_ATTACHMENT_LOAD_OP_CLEAR;
                depthAttachment.storeOp        = VK_ATTACHMENT_STORE_OP_DONT_CARE;
                depthAttachment.stencilLoadOp  = VK_ATTACHMENT_LOAD_OP_CLEAR;
                depthAttachment.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;
                depthAttachment.initialLayout  = VK_IMAGE_LAYOUT_UNDEFINED;
                depthAttachment.finalLayout    = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
                attachments.push_back(depthAttachment);
            }


            VkAttachmentReference colorReference{};
            colorReference.attachment = 0;
            colorReference.layout     = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

            VkAttachmentReference depthReference{};
            if (HasDepth)
            {
                depthReference.attachment = 1;
                depthReference.layout     = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;
            }

            VkSubpassDescription subpassDescription{};
            subpassDescription.pipelineBindPoint       = VK_PIPELINE_BIND_POINT_GRAPHICS;
            subpassDescription.colorAttachmentCount    = 1;
            subpassDescription.pColorAttachments       = &colorReference;
            if (HasDepth)
            {
                subpassDescription.pDepthStencilAttachment = &depthReference;
            }
            subpassDescription.inputAttachmentCount    = 0;
            subpassDescription.pInputAttachments       = nullptr;
            subpassDescription.preserveAttachmentCount = 0;
            subpassDescription.pPreserveAttachments    = nullptr;
            subpassDescription.pResolveAttachments     = nullptr;

            std::vector<VkSubpassDependency> dependencies(2);

            dependencies[0].srcSubpass      = VK_SUBPASS_EXTERNAL;
            dependencies[0].dstSubpass      = 0;
            dependencies[0].srcStageMask    = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
            dependencies[0].dstStageMask    = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
            dependencies[0].srcAccessMask   = VK_ACCESS_SHADER_READ_BIT;
            dependencies[0].dstAccessMask   = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
            dependencies[0].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

            dependencies[1].srcSubpass      = 0;
            dependencies[1].dstSubpass      = VK_SUBPASS_EXTERNAL;
            dependencies[1].srcStageMask    = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
            dependencies[1].dstStageMask    = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT;
            dependencies[1].srcAccessMask   = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
            dependencies[1].dstAccessMask   = VK_ACCESS_SHADER_READ_BIT;
            dependencies[1].dependencyFlags = VK_DEPENDENCY_BY_REGION_BIT;

            VkRenderPassCreateInfo createInfo{};
            createInfo.sType           = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
            createInfo.pNext           = nullptr;
            createInfo.attachmentCount = uint32_t (attachments.size());
            createInfo.pAttachments    = attachments.data();
            createInfo.subpassCount    = 1;
            createInfo.pSubpasses      = &subpassDescription;
            createInfo.dependencyCount = uint32_t(dependencies.size());
            createInfo.pDependencies   = dependencies.data();

            Check(device->Create(&createInfo,&handle, nullptr));
        }

        RenderPass::RenderPass(Device *device, VkRenderPassCreateInfo * pCreateInfo) :
                device{ device }
        {
            Check(device->Create(pCreateInfo, &handle));
        }

        RenderPass::~RenderPass()
        {
            if (device)
            {
                device->Destroy(handle);
            }
        }
    } // SPK
} // Vulkan