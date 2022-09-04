#pragma once

namespace SPK
{

    class Render
    {
    public:
        enum class Type
        {
            NONE,
            Vulkan,
            OpenGL,
            DirectX
        };

    public:

        static void Set(Type type)
        {
            API = type;
        }

        static inline Type API{Type::NONE};

    };

} // SPK
