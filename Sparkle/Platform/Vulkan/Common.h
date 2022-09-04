#pragma once

#include "vulkan/vulkan.h"

#include "Framework/Log.h"

#include "PCH/PCH.h"

namespace SPK
{
    namespace Vulkan
    {

        static std::vector<VkDescriptorPoolSize> PoolSize{
                { VK_DESCRIPTOR_TYPE_SAMPLER,                1000 },
                { VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER, 1000 },
                { VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE,          1000 },
                { VK_DESCRIPTOR_TYPE_STORAGE_IMAGE,          1000 },
                { VK_DESCRIPTOR_TYPE_UNIFORM_TEXEL_BUFFER,   1000 },
                { VK_DESCRIPTOR_TYPE_STORAGE_TEXEL_BUFFER,   1000 },
                { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,         1000 },
                { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,         1000 },
                { VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER_DYNAMIC, 1000 },
                { VK_DESCRIPTOR_TYPE_STORAGE_BUFFER_DYNAMIC, 1000 },
                { VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT,       1000 }
        };

#define VK_CASE(x) case x: return #x;

        inline const char *Stringify(VkResult err)
        {
            switch (err)
            {
                VK_CASE(VK_SUCCESS)
                VK_CASE(VK_NOT_READY)
                VK_CASE(VK_TIMEOUT)
                VK_CASE(VK_EVENT_SET)
                VK_CASE(VK_EVENT_RESET)
                VK_CASE(VK_INCOMPLETE)
                VK_CASE(VK_ERROR_OUT_OF_HOST_MEMORY)
                VK_CASE(VK_ERROR_OUT_OF_DEVICE_MEMORY)
                VK_CASE(VK_ERROR_INITIALIZATION_FAILED)
                VK_CASE(VK_ERROR_DEVICE_LOST)
                VK_CASE(VK_ERROR_MEMORY_MAP_FAILED)
                VK_CASE(VK_ERROR_LAYER_NOT_PRESENT)
                VK_CASE(VK_ERROR_EXTENSION_NOT_PRESENT)
                VK_CASE(VK_ERROR_FEATURE_NOT_PRESENT)
                VK_CASE(VK_ERROR_INCOMPATIBLE_DRIVER)
                VK_CASE(VK_ERROR_TOO_MANY_OBJECTS)
                VK_CASE(VK_ERROR_FORMAT_NOT_SUPPORTED)
                VK_CASE(VK_ERROR_FRAGMENTED_POOL)
                VK_CASE(VK_ERROR_UNKNOWN)
                VK_CASE(VK_ERROR_OUT_OF_POOL_MEMORY)
                VK_CASE(VK_ERROR_INVALID_EXTERNAL_HANDLE)
                VK_CASE(VK_ERROR_FRAGMENTATION)
                VK_CASE(VK_ERROR_INVALID_OPAQUE_CAPTURE_ADDRESS)
                VK_CASE(VK_ERROR_SURFACE_LOST_KHR)
                VK_CASE(VK_ERROR_NATIVE_WINDOW_IN_USE_KHR)
                VK_CASE(VK_SUBOPTIMAL_KHR)
                VK_CASE(VK_ERROR_OUT_OF_DATE_KHR)
                VK_CASE(VK_ERROR_INCOMPATIBLE_DISPLAY_KHR)
                VK_CASE(VK_ERROR_VALIDATION_FAILED_EXT)
                VK_CASE(VK_ERROR_INVALID_SHADER_NV)
                VK_CASE(VK_ERROR_INVALID_DRM_FORMAT_MODIFIER_PLANE_LAYOUT_EXT)
                VK_CASE(VK_ERROR_NOT_PERMITTED_EXT)
                VK_CASE(VK_ERROR_FULL_SCREEN_EXCLUSIVE_MODE_LOST_EXT)
                VK_CASE(VK_THREAD_IDLE_KHR)
                VK_CASE(VK_THREAD_DONE_KHR)
                VK_CASE(VK_OPERATION_DEFERRED_KHR)
                VK_CASE(VK_OPERATION_NOT_DEFERRED_KHR)
                VK_CASE(VK_PIPELINE_COMPILE_REQUIRED_EXT)
            }
            return "";
        }

        inline const char *Stringify(VkFormat format)
        {
            switch (format)
            {
                VK_CASE(VK_FORMAT_R4G4_UNORM_PACK8);
                VK_CASE(VK_FORMAT_R4G4B4A4_UNORM_PACK16);
                VK_CASE(VK_FORMAT_B4G4R4A4_UNORM_PACK16);
                VK_CASE(VK_FORMAT_R5G6B5_UNORM_PACK16);
                VK_CASE(VK_FORMAT_B5G6R5_UNORM_PACK16);
                VK_CASE(VK_FORMAT_R5G5B5A1_UNORM_PACK16);
                VK_CASE(VK_FORMAT_B5G5R5A1_UNORM_PACK16);
                VK_CASE(VK_FORMAT_A1R5G5B5_UNORM_PACK16);
                VK_CASE(VK_FORMAT_R8_UNORM);
                VK_CASE(VK_FORMAT_R8_SNORM);
                VK_CASE(VK_FORMAT_R8_USCALED);
                VK_CASE(VK_FORMAT_R8_SSCALED);
                VK_CASE(VK_FORMAT_R8_UINT);
                VK_CASE(VK_FORMAT_R8_SINT);
                VK_CASE(VK_FORMAT_R8_SRGB);
                VK_CASE(VK_FORMAT_R8G8_UNORM);
                VK_CASE(VK_FORMAT_R8G8_SNORM);
                VK_CASE(VK_FORMAT_R8G8_USCALED);
                VK_CASE(VK_FORMAT_R8G8_SSCALED);
                VK_CASE(VK_FORMAT_R8G8_UINT);
                VK_CASE(VK_FORMAT_R8G8_SINT);
                VK_CASE(VK_FORMAT_R8G8_SRGB);
                VK_CASE(VK_FORMAT_R8G8B8_UNORM);
                VK_CASE(VK_FORMAT_R8G8B8_SNORM);
                VK_CASE(VK_FORMAT_R8G8B8_USCALED);
                VK_CASE(VK_FORMAT_R8G8B8_SSCALED);
                VK_CASE(VK_FORMAT_R8G8B8_UINT);
                VK_CASE(VK_FORMAT_R8G8B8_SINT);
                VK_CASE(VK_FORMAT_R8G8B8_SRGB);
                VK_CASE(VK_FORMAT_B8G8R8_UNORM);
                VK_CASE(VK_FORMAT_B8G8R8_SNORM);
                VK_CASE(VK_FORMAT_B8G8R8_USCALED);
                VK_CASE(VK_FORMAT_B8G8R8_SSCALED);
                VK_CASE(VK_FORMAT_B8G8R8_UINT);
                VK_CASE(VK_FORMAT_B8G8R8_SINT);
                VK_CASE(VK_FORMAT_B8G8R8_SRGB);
                VK_CASE(VK_FORMAT_R8G8B8A8_UNORM);
                VK_CASE(VK_FORMAT_R8G8B8A8_SNORM);
                VK_CASE(VK_FORMAT_R8G8B8A8_USCALED);
                VK_CASE(VK_FORMAT_R8G8B8A8_SSCALED);
                VK_CASE(VK_FORMAT_R8G8B8A8_UINT);
                VK_CASE(VK_FORMAT_R8G8B8A8_SINT);
                VK_CASE(VK_FORMAT_R8G8B8A8_SRGB);
                VK_CASE(VK_FORMAT_B8G8R8A8_UNORM);
                VK_CASE(VK_FORMAT_B8G8R8A8_SNORM);
                VK_CASE(VK_FORMAT_B8G8R8A8_USCALED);
                VK_CASE(VK_FORMAT_B8G8R8A8_SSCALED);
                VK_CASE(VK_FORMAT_B8G8R8A8_UINT);
                VK_CASE(VK_FORMAT_B8G8R8A8_SINT);
                VK_CASE(VK_FORMAT_B8G8R8A8_SRGB);
                VK_CASE(VK_FORMAT_A8B8G8R8_UNORM_PACK32);
                VK_CASE(VK_FORMAT_A8B8G8R8_SNORM_PACK32);
                VK_CASE(VK_FORMAT_A8B8G8R8_USCALED_PACK32);
                VK_CASE(VK_FORMAT_A8B8G8R8_SSCALED_PACK32);
                VK_CASE(VK_FORMAT_A8B8G8R8_UINT_PACK32);
                VK_CASE(VK_FORMAT_A8B8G8R8_SINT_PACK32);
                VK_CASE(VK_FORMAT_A8B8G8R8_SRGB_PACK32);
                VK_CASE(VK_FORMAT_A2R10G10B10_UNORM_PACK32);
                VK_CASE(VK_FORMAT_A2R10G10B10_SNORM_PACK32);
                VK_CASE(VK_FORMAT_A2R10G10B10_USCALED_PACK32);
                VK_CASE(VK_FORMAT_A2R10G10B10_SSCALED_PACK32);
                VK_CASE(VK_FORMAT_A2R10G10B10_UINT_PACK32);
                VK_CASE(VK_FORMAT_A2R10G10B10_SINT_PACK32);
                VK_CASE(VK_FORMAT_A2B10G10R10_UNORM_PACK32);
                VK_CASE(VK_FORMAT_A2B10G10R10_SNORM_PACK32);
                VK_CASE(VK_FORMAT_A2B10G10R10_USCALED_PACK32);
                VK_CASE(VK_FORMAT_A2B10G10R10_SSCALED_PACK32);
                VK_CASE(VK_FORMAT_A2B10G10R10_UINT_PACK32);
                VK_CASE(VK_FORMAT_A2B10G10R10_SINT_PACK32);
                VK_CASE(VK_FORMAT_R16_UNORM);
                VK_CASE(VK_FORMAT_R16_SNORM);
                VK_CASE(VK_FORMAT_R16_USCALED);
                VK_CASE(VK_FORMAT_R16_SSCALED);
                VK_CASE(VK_FORMAT_R16_UINT);
                VK_CASE(VK_FORMAT_R16_SINT);
                VK_CASE(VK_FORMAT_R16_SFLOAT);
                VK_CASE(VK_FORMAT_R16G16_UNORM);
                VK_CASE(VK_FORMAT_R16G16_SNORM);
                VK_CASE(VK_FORMAT_R16G16_USCALED);
                VK_CASE(VK_FORMAT_R16G16_SSCALED);
                VK_CASE(VK_FORMAT_R16G16_UINT);
                VK_CASE(VK_FORMAT_R16G16_SINT);
                VK_CASE(VK_FORMAT_R16G16_SFLOAT);
                VK_CASE(VK_FORMAT_R16G16B16_UNORM);
                VK_CASE(VK_FORMAT_R16G16B16_SNORM);
                VK_CASE(VK_FORMAT_R16G16B16_USCALED);
                VK_CASE(VK_FORMAT_R16G16B16_SSCALED);
                VK_CASE(VK_FORMAT_R16G16B16_UINT);
                VK_CASE(VK_FORMAT_R16G16B16_SINT);
                VK_CASE(VK_FORMAT_R16G16B16_SFLOAT);
                VK_CASE(VK_FORMAT_R16G16B16A16_UNORM);
                VK_CASE(VK_FORMAT_R16G16B16A16_SNORM);
                VK_CASE(VK_FORMAT_R16G16B16A16_USCALED);
                VK_CASE(VK_FORMAT_R16G16B16A16_SSCALED);
                VK_CASE(VK_FORMAT_R16G16B16A16_UINT);
                VK_CASE(VK_FORMAT_R16G16B16A16_SINT);
                VK_CASE(VK_FORMAT_R16G16B16A16_SFLOAT);
                VK_CASE(VK_FORMAT_R32_UINT);
                VK_CASE(VK_FORMAT_R32_SINT);
                VK_CASE(VK_FORMAT_R32_SFLOAT);
                VK_CASE(VK_FORMAT_R32G32_UINT);
                VK_CASE(VK_FORMAT_R32G32_SINT);
                VK_CASE(VK_FORMAT_R32G32_SFLOAT);
                VK_CASE(VK_FORMAT_R32G32B32_UINT);
                VK_CASE(VK_FORMAT_R32G32B32_SINT);
                VK_CASE(VK_FORMAT_R32G32B32_SFLOAT);
                VK_CASE(VK_FORMAT_R32G32B32A32_UINT);
                VK_CASE(VK_FORMAT_R32G32B32A32_SINT);
                VK_CASE(VK_FORMAT_R32G32B32A32_SFLOAT);
                VK_CASE(VK_FORMAT_R64_UINT);
                VK_CASE(VK_FORMAT_R64_SINT);
                VK_CASE(VK_FORMAT_R64_SFLOAT);
                VK_CASE(VK_FORMAT_R64G64_UINT);
                VK_CASE(VK_FORMAT_R64G64_SINT);
                VK_CASE(VK_FORMAT_R64G64_SFLOAT);
                VK_CASE(VK_FORMAT_R64G64B64_UINT);
                VK_CASE(VK_FORMAT_R64G64B64_SINT);
                VK_CASE(VK_FORMAT_R64G64B64_SFLOAT);
                VK_CASE(VK_FORMAT_R64G64B64A64_UINT);
                VK_CASE(VK_FORMAT_R64G64B64A64_SINT);
                VK_CASE(VK_FORMAT_R64G64B64A64_SFLOAT);
                VK_CASE(VK_FORMAT_B10G11R11_UFLOAT_PACK32);
                VK_CASE(VK_FORMAT_E5B9G9R9_UFLOAT_PACK32);
                VK_CASE(VK_FORMAT_D16_UNORM);
                VK_CASE(VK_FORMAT_X8_D24_UNORM_PACK32);
                VK_CASE(VK_FORMAT_D32_SFLOAT);
                VK_CASE(VK_FORMAT_S8_UINT);
                VK_CASE(VK_FORMAT_D16_UNORM_S8_UINT);
                VK_CASE(VK_FORMAT_D24_UNORM_S8_UINT);
                VK_CASE(VK_FORMAT_D32_SFLOAT_S8_UINT);
                VK_CASE(VK_FORMAT_UNDEFINED);
                default:
                    return "VK_FORMAT_INVALID";
            }
        }

        inline const char *Stringify(VkPresentModeKHR presentMode)
        {
            switch (presentMode)
            {
                VK_CASE(VK_PRESENT_MODE_MAILBOX_KHR);
                VK_CASE(VK_PRESENT_MODE_IMMEDIATE_KHR);
                VK_CASE(VK_PRESENT_MODE_FIFO_KHR);
                VK_CASE(VK_PRESENT_MODE_FIFO_RELAXED_KHR);;
                VK_CASE(VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR);
                VK_CASE(VK_PRESENT_MODE_SHARED_DEMAND_REFRESH_KHR);
                default:
                    return "UNKNOWN_PRESENT_MODE";
            }
        }

        inline const char *Stringify(VkImageUsageFlagBits imageUsage)
        {
            switch (imageUsage)
            {
                VK_CASE(VK_IMAGE_USAGE_TRANSFER_SRC_BIT);
                VK_CASE(VK_IMAGE_USAGE_TRANSFER_DST_BIT);
                VK_CASE(VK_IMAGE_USAGE_SAMPLED_BIT);
                VK_CASE(VK_IMAGE_USAGE_STORAGE_BIT);
                VK_CASE(VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT);
                VK_CASE(VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT);
                VK_CASE(VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT);
                VK_CASE(VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT);
                VK_CASE(VK_IMAGE_USAGE_FLAG_BITS_MAX_ENUM);
                default:
                    return "UNKNOWN IMAGE USAGE FLAG";
            }
        }

        inline const char *Stringify(VkSurfaceTransformFlagBitsKHR transform)
        {
            switch (transform)
            {
                VK_CASE(VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR);
                VK_CASE(VK_SURFACE_TRANSFORM_ROTATE_90_BIT_KHR);
                VK_CASE(VK_SURFACE_TRANSFORM_ROTATE_180_BIT_KHR);
                VK_CASE(VK_SURFACE_TRANSFORM_ROTATE_270_BIT_KHR);
                VK_CASE(VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_BIT_KHR);
                VK_CASE(VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_90_BIT_KHR);
                VK_CASE(VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_180_BIT_KHR);
                VK_CASE(VK_SURFACE_TRANSFORM_HORIZONTAL_MIRROR_ROTATE_270_BIT_KHR);
                VK_CASE(VK_SURFACE_TRANSFORM_INHERIT_BIT_KHR);
                VK_CASE(VK_SURFACE_TRANSFORM_FLAG_BITS_MAX_ENUM_KHR);
                default:
                    return "[Unknown transform flag]";
            }
        }

        inline const char *Stringify(VkCompositeAlphaFlagBitsKHR compositeAlpha)
        {
            switch (compositeAlpha)
            {
                VK_CASE(VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR);
                VK_CASE(VK_COMPOSITE_ALPHA_PRE_MULTIPLIED_BIT_KHR);
                VK_CASE(VK_COMPOSITE_ALPHA_POST_MULTIPLIED_BIT_KHR);
                VK_CASE(VK_COMPOSITE_ALPHA_INHERIT_BIT_KHR);
                VK_CASE(VK_COMPOSITE_ALPHA_FLAG_BITS_MAX_ENUM_KHR);
                default:
                    return "UNKNOWN COMPOSITE ALPHA FLAG";
            }
        }

        inline const std::string Stringify(VkSurfaceFormatKHR surfaceFormat)
        {
            std::string surfaceFormatString = std::string(Stringify(surfaceFormat.format)) + ", ";

            switch (surfaceFormat.colorSpace)
            {
                case VK_COLORSPACE_SRGB_NONLINEAR_KHR:
                    surfaceFormatString += "VK_COLORSPACE_SRGB_NONLINEAR_KHR";
                    break;
                default:
                    surfaceFormatString += "UNKNOWN COLOR SPACE";
            }
            return surfaceFormatString;
        }

#define VULKAN_HANDLE(Object) \
public:                       \
Object Handle() const         \
{return handle;}              \
operator Object() const        \
{return handle;}              \
protected:                    \
Object handle{VK_NULL_HANDLE};

        inline void Check(VkResult status)
        {
            auto msg = Stringify(status);
            if (status)
            {
                RENDER_ERROR("Detected Vulkan error: {0}", msg);
                abort();
            }
        }

        static inline bool IsDepthOnlyFormat(VkFormat format)
        {
            return format == VK_FORMAT_D16_UNORM || format == VK_FORMAT_D32_SFLOAT || format == VK_FORMAT_D24_UNORM_S8_UINT;
        }

    }
}

