#include "Window.h"


#include "Render/Render.h"

#include "Platform/Window/GLFWWindow.h"

namespace SPK
{

    Window *Window::Create(const Description &description)
    {
        if ((int)Render::API & ((int)Render::Type::Vulkan | (int)Render::Type::OpenGL))
        {
            RENDER_INFO("Creating window with GLFW");
            return new GLFWWindow{ description };
        }

        RENDER_ERROR("There is no Window implemented for the rendering API specified yet.");
        return nullptr;
    }

} // SPK