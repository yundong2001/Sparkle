#pragma once

#include "Core.h"
#include "vulkan/vulkan.h"

namespace SPK
{
    struct Format
    {
    public:
        enum ValueType : uint32_t
        {
            R8G8B8A8_UNORM = 0,
            R8G8B8A8_SRGB = 1,
            INT = 0,
            IVECTOR2,
            IVECTOR3,
            IVECTOR4,
            FLOAT,
            VECTOR2,
            VECTOR3,
            VECTOR4,
            COLOUR = VECTOR4,
            MATRIX4,
            R8,
            R16,
            R16F,
            R32,
            R32F,
            RG8,
            RG16,
            RG16F,
            RG32,
            RG32F,
            RGB8,
            RGB32,
            RGB32F,
            RGBA8,
            RGBA16,
            RGBA16F,
            RGBA32,
            RGBA32F,
            BGRA8,
            SRGB,
            Depth32F,
            Depth24Stencil8,
            YUV420P,
            YUV422P,
            YUV444P,
            YUV420P10,
            YUV422P10,
            YUV444P10,
            Depth = Depth32F,
            None
        };

        Format() :
                v{ None }
        {

        }

        Format(ValueType v) :
                v{ v }
        {

        }

        operator ValueType() const
        {
            return v;
        }

        int ComponentCount() const;

        int ElementSize() const;

        int BytesPerPixel() const;

        size_t Size() const;

        operator VkFormat() const;

    private:
        ValueType v;
    };

    struct FormatElement
    {
        FormatElement(Format format, VkFormat vkFormat, int size, int count) :
                Vulkan{ vkFormat },
                ElementSize{ size },
                ComponentCount{ count }
        {

        }

        operator VkFormat() const
        {
            return Vulkan;
        }

        VkFormat    Vulkan;
        int         ElementSize;
        int         ComponentCount;
    };

    using bfloat = uint16_t;
#define FS_C(T, CC) (sizeof(T)), CC

    static inline FormatElement FormatElementTable[] = {
            { Format::INT,             VK_FORMAT_R32_SINT,            /*DXF(DXGI_FORMAT_R32_SINT           ),  GL_INT,              */ FS_C(int,      1)     },
            { Format::IVECTOR2,        VK_FORMAT_R32G32_SINT,         /*DXF(DXGI_FORMAT_R32G32_SINT        ),  GL_INT,              */ FS_C(int,      2)     },
            { Format::IVECTOR3,        VK_FORMAT_R32G32B32_SINT,      /*DXF(DXGI_FORMAT_R32G32B32_SINT     ),  GL_INT,              */ FS_C(int,      3)     },
            { Format::IVECTOR4,        VK_FORMAT_R32G32B32A32_SINT,   /*DXF(DXGI_FORMAT_R32G32B32A32_SINT  ),  GL_INT,              */ FS_C(int,      4)     },
            { Format::FLOAT,           VK_FORMAT_R32_SFLOAT,          /*DXF(DXGI_FORMAT_R32_FLOAT          ),  GL_FLOAT,            */ FS_C(float,    1)     },
            { Format::VECTOR2,         VK_FORMAT_R32G32_SFLOAT,       /*DXF(DXGI_FORMAT_R32G32_FLOAT       ),  GL_FLOAT,            */ FS_C(float,    2)     },
            { Format::VECTOR3,         VK_FORMAT_R32G32B32_SFLOAT,    /*DXF(DXGI_FORMAT_R32G32B32_FLOAT    ),  GL_FLOAT,            */ FS_C(float,    3)     },
            { Format::VECTOR4,         VK_FORMAT_R32G32B32A32_SFLOAT, /*DXF(DXGI_FORMAT_R32G32B32A32_FLOAT ),  GL_FLOAT,            */ FS_C(float,    4)     },
            { Format::MATRIX4,         VK_FORMAT_R32_SFLOAT,          /*DXF(DXGI_FORMAT_R32_FLOAT          ),  GL_FLOAT,            */ FS_C(float,    4 * 4) },
            { Format::R8,              VK_FORMAT_R8_UNORM,            /*DXF(DXGI_FORMAT_R8_UNORM           ),  GL_R8,               */ FS_C(uint8_t,  1)     },
            { Format::R16,             VK_FORMAT_R16_UNORM,           /*DXF(DXGI_FORMAT_R16_UNORM          ),  GL_R16,              */ FS_C(uint16_t, 1)     },
            { Format::R16F,            VK_FORMAT_R16_SFLOAT,          /*DXF(DXGI_FORMAT_R16_FLOAT          ),  GL_R32F,             */ FS_C(bfloat,   1)     },
            { Format::R32,             VK_FORMAT_R32_SINT,            /*DXF(DXGI_FORMAT_R32_SINT           ),  GL_INT ,             */ FS_C(uint32_t, 1)     },
            { Format::R32F,            VK_FORMAT_R32_SFLOAT,          /*DXF(DXGI_FORMAT_R32_FLOAT          ),  GL_R32F,             */ FS_C(float,    1)     },
            { Format::RG8,             VK_FORMAT_R8G8_UNORM,          /*DXF(DXGI_FORMAT_R8G8_UNORM         ),  GL_RG8,              */ FS_C(uint8_t,  2)     },
            { Format::RG16,            VK_FORMAT_R16G16_UNORM,        /*DXF(DXGI_FORMAT_R16G16_UNORM       ),  GL_RG16,             */ FS_C(uint16_t, 2)     },
            { Format::RG16F,           VK_FORMAT_R16G16_SFLOAT,       /*DXF(DXGI_FORMAT_R16G16_FLOAT       ),  GL_RG32F,            */ FS_C(bfloat,   2)     },
            { Format::RG32,            VK_FORMAT_R32G32_SINT,         /*DXF(DXGI_FORMAT_R32G32_SINT        ),  GL_RG32I ,           */ FS_C(uint32_t, 2)     },
            { Format::RG32F,           VK_FORMAT_R32G32_SFLOAT,       /*DXF(DXGI_FORMAT_R32G32_FLOAT       ),  GL_RG32F,            */ FS_C(float,    2)     },
            { Format::RGB8,            VK_FORMAT_R8G8B8_UNORM,        /*DXF(DXGI_FORMAT_UNKNOWN            ),  GL_RGB8 ,            */ FS_C(uint8_t,  3)     },
            { Format::RGB32,           VK_FORMAT_R32G32B32_SINT,      /*DXF(DXGI_FORMAT_R32G32B32_SINT     ),  GL_RGB32I ,          */ FS_C(uint32_t, 3)     },
            { Format::RGB32F,          VK_FORMAT_R32G32B32_SFLOAT,    /*DXF(DXGI_FORMAT_R32G32B32_FLOAT    ),  GL_RGB32F,           */ FS_C(float,    3)     },
            { Format::RGBA8,           VK_FORMAT_R8G8B8A8_UNORM,      /*DXF(DXGI_FORMAT_R8G8B8A8_UNORM     ),  GL_RGBA8,            */ FS_C(uint8_t,  4)     },
            { Format::RGBA16,          VK_FORMAT_R16G16B16A16_UNORM,  /*DXF(DXGI_FORMAT_R16G16B16A16_UNORM ),  GL_RGBA16,           */ FS_C(uint16_t, 4)     },
            { Format::RGBA16F,         VK_FORMAT_R16G16B16A16_SFLOAT, /*DXF(DXGI_FORMAT_R16G16B16A16_FLOAT ),  GL_RGBA16F,          */ FS_C(bfloat,   4)     },
            { Format::RGBA32,          VK_FORMAT_R32G32B32A32_SINT,   /*DXF(DXGI_FORMAT_R32G32B32A32_SINT  ),  GL_INT,              */ FS_C(int,      4)     },
            { Format::RGBA32F,         VK_FORMAT_R32G32B32A32_SFLOAT, /*DXF(DXGI_FORMAT_R32G32B32A32_FLOAT ),  GL_RGBA32F,          */ FS_C(float,    4)     },
            { Format::BGRA8,           VK_FORMAT_B8G8R8A8_UNORM,      /*DXF(DXGI_FORMAT_B8G8R8A8_UNORM     ),  GL_RGBA8,            */ FS_C(uint8_t,  4)     },
            { Format::SRGB,            VK_FORMAT_R8G8B8A8_SRGB,       /*DXF(DXGI_FORMAT_R8G8B8A8_UNORM_SRGB),  GL_SRGB8,            */ FS_C(uint8_t,  4)     },
            { Format::Depth32F,        VK_FORMAT_D32_SFLOAT,          /*DXF(DXGI_FORMAT_D32_FLOAT          ),  GL_DEPTH32F_STENCIL8,*/ FS_C(float,    1)     },
            { Format::Depth24Stencil8, VK_FORMAT_D24_UNORM_S8_UINT,   /*DXF(DXGI_FORMAT_D24_UNORM_S8_UINT  ),  GL_DEPTH24_STENCIL8, */ FS_C(uint32_t, 1)     },
            { Format::YUV420P,         VK_FORMAT_UNDEFINED,           /*DXF(DXGI_FORMAT_UNKNOWN            ),  GL_INVALID_ENUM,     */ FS_C(uint8_t,  3)     },
            { Format::YUV422P,         VK_FORMAT_UNDEFINED,           /*DXF(DXGI_FORMAT_UNKNOWN            ),  GL_INVALID_ENUM,     */ FS_C(uint8_t,  3)     },
            { Format::YUV444P,         VK_FORMAT_UNDEFINED,           /*DXF(DXGI_FORMAT_UNKNOWN            ),  GL_INVALID_ENUM,     */ FS_C(uint8_t,  3)     },
            { Format::YUV420P10,       VK_FORMAT_UNDEFINED,           /*DXF(DXGI_FORMAT_UNKNOWN            ),  GL_INVALID_ENUM,     */ FS_C(uint16_t, 3)     },
            { Format::YUV422P10,       VK_FORMAT_UNDEFINED,           /*DXF(DXGI_FORMAT_UNKNOWN            ),  GL_INVALID_ENUM,     */ FS_C(uint16_t, 3)     },
            { Format::YUV444P10,       VK_FORMAT_UNDEFINED,           /*DXF(DXGI_FORMAT_UNKNOWN            ),  GL_INVALID_ENUM,     */ FS_C(uint16_t, 3)     },
    };

    inline int Format::ComponentCount() const
    {
        return FormatElementTable[v].ComponentCount;
    }

    inline Format::operator VkFormat() const
    {
        return FormatElementTable[v];
    }

    inline int Format::ElementSize() const
    {
        return FormatElementTable[v].ElementSize;
    }

    inline int Format::BytesPerPixel() const
    {
        return ElementSize();
    }

    inline size_t Format::Size() const
    {
        return ElementSize() * ComponentCount();
    }
}