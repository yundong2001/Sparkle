#include "GLFWWindow.h"

#include "Render/Render.h"
#include "Event/ApplicationEvent.h"
#include "Event/MouseEvent.h"
#include "Event/KeyEvent.h"

namespace SPK
{
    uint8_t GLFWWindow::GLFWWindowCount = 0;

    static void GLFWErrorCallback(int error, const char *description)
    {
        RENDER_ERROR("GLFW Error ({0}): {1}", error, description);
    }

    GLFWWindow::GLFWWindow(const Description &description)
    {
        Setup(description);
    }

    GLFWWindow::~GLFWWindow()
    {
        Shutdown();
    }

    void GLFWWindow::SetTitle(const std::string &title)
    {
        desc.Title = title;
        glfwSetWindowTitle(window, desc.Title.c_str());
    }

    void GLFWWindow::SetIcon(const std::string &filepath)
    {
        //TODO
    }

    void GLFWWindow::Setup(const Description &description)
    {
        desc = description;

        RENDER_INFO("Creating window {0} ({1}, {2})", desc.Title, desc.Width, desc.Height);

        if (GLFWWindowCount == 0)
        {
            glfwSetErrorCallback(GLFWErrorCallback);
            auto error = glfwInit();
            if(!error)
            {
                throw  std::runtime_error("Failed to initialize GLFW Window!");
            }
        }

        if (Render::API == Render::Type::Vulkan )
        {
            glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
        }

        window = glfwCreateWindow((int)desc.Width, (int)desc.Height, description.Title.c_str(), nullptr, nullptr);
        GLFWWindowCount++;

        glfwSetWindowUserPointer(window, &desc);

        //TODO:Input Call Back

        glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int width, int height)
        {
            Description *desc = static_cast<Description *>(glfwGetWindowUserPointer(window));
            desc->Width = width;
            desc->Height = height;

            WindowResizeEvent event(width, height);
            desc->EventCallback(event);

#ifndef NDEBUG
            RENDER_DEBUG(event.ToString())
#endif

        });

        glfwSetWindowCloseCallback(window, [](GLFWwindow* window)
        {
            Description *desc = static_cast<Description *>(glfwGetWindowUserPointer(window));
            WindowCloseEvent event;
            desc->EventCallback(event);

#ifndef NDEBUG
            RENDER_DEBUG(event.ToString())
#endif
        });

        glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int modes)
        {
            Description *desc = static_cast<Description *>(glfwGetWindowUserPointer(window));

            switch (action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, 0);
                    desc->EventCallback(event);

#ifndef NDEBUG
                    RENDER_DEBUG(event.ToString())
#endif

                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    desc->EventCallback(event);

#ifndef NDEBUG
                    RENDER_DEBUG(event.ToString())
#endif

                    break;
                }

                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, 1);
                    desc->EventCallback(event);

#ifndef NDEBUG
                    RENDER_DEBUG(event.ToString())
#endif

                    break;
                }
            }

        });

        glfwSetMouseButtonCallback(window, [](GLFWwindow *window, int button, int action, int modes)
        {
            Description *desc = static_cast<Description *>(glfwGetWindowUserPointer(window));

            switch (action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    desc->EventCallback(event);

#ifndef NDEBUG
                    RENDER_DEBUG(event.ToString())
#endif

                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    desc->EventCallback(event);

#ifndef NDEBUG
                    RENDER_DEBUG(event.ToString())
#endif

                    break;
                }
            }
        });

        glfwSetScrollCallback(window, [](GLFWwindow *window, double xOffset, double yOffset)
        {
            Description *desc = static_cast<Description *>(glfwGetWindowUserPointer(window));

            MouseScrolledEvent event((float)xOffset, (float)yOffset);
            desc->EventCallback(event);

#ifndef NDEBUG
            RENDER_DEBUG(event.ToString())
#endif
        });

        glfwSetCursorPosCallback(window, [](GLFWwindow *window, double xPos, double yPos)
        {
            Description *desc = static_cast<Description *>(glfwGetWindowUserPointer(window));

            MouseMoveEvent event((float)xPos, (float)yPos);
            desc->EventCallback(event);

#ifndef NDEBUG
            RENDER_DEBUG(event.ToString())
#endif
        });
    }

    void GLFWWindow::Shutdown()
    {
        glfwDestroyWindow(window);
        --GLFWWindowCount;

        if (GLFWWindowCount==0)
        {
            glfwTerminate();
        }
    }

    float GLFWWindow::Time() const
    {
        return glfwGetTime();
    }

} // SPK