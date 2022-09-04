#pragma once

#include "Framework/Window.h"

#include "GLFW/glfw3.h"

namespace SPK
{

    class GLFWWindow : public Window
    {
    public:
        DEFINE_WINDOW_TYPE(GLFW)

        GLFWWindow(Description const &description);

        virtual ~GLFWWindow();

        uint32_t Width() const override
        {
            return desc.Width;
        }

        uint32_t Height() const override
        {
            return desc.Height;
        }

        float Time() const override;

        void SetEventCallback(const EventCallbackFunc& callback) override
        {
            desc.EventCallback = callback;
        }

        virtual void *GetNativeWindow() const
        {
            return window;
        }


        virtual void ProcessEvents() override
        {
            glfwPollEvents();
        }

        virtual void SetTitle(const std::string &title) override;

        virtual void SetIcon(const std::string &filepath) override;

    private:
        virtual void Setup(const Description &descrition);

        virtual void Shutdown();

    private:
        GLFWwindow *window;

        Description desc{};

        //std::unique_ptr<Input> input;

    public:
        static uint8_t GLFWWindowCount;
    };

} // SPK