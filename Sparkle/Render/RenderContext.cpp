#include "RenderContext.h"

#include "Render.h"

#include "Platform/Vulkan/RenderContext.h"

namespace SPK
{
    std::unique_ptr<RenderContext> RenderContext::Create(const Description &desc)
    {
        switch (Render::API)
        {
            case Render::Type::Vulkan:
                RENDER_INFO("Create Vulkan Render Context")
                return std::make_unique<Vulkan::RenderContext>(desc);
            default:
                RENDER_ERROR( "Not support api" )
                return nullptr;
        }
    }
} // SPK