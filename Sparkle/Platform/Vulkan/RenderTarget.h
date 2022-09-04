#pragma once

#include "Common.h"
#include "Core.h"

#include "Render/RenderTarget.h"

#include "Device.h"
#include "Attachment.h"
#include "FrameBuffer.h"
#include "RenderPass.h"

namespace SPK
{
    namespace Vulkan
    {

        class RenderTarget : public SPK::RenderTarget
        {
        public:


        private:
            Device *device{ nullptr };

            std::shared_ptr<RenderPass> renderPass;

            std::unique_ptr<FrameBuffer> framebuffer;

            //std::unique_ptr<DescriptorSet> descriptorSet;

            //std::unique_ptr<ImageDescriptor> descriptor;

            //Sampler sampler;

            struct
            {
                Attachment depth;

                std::vector<Attachment> colors;
            } attachments;

            std::vector<std::unique_ptr<Image>> stagingImages;
        };

    } // SPK
} // Vulkan
