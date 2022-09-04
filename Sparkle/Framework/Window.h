#pragma once

#include "Core.h"

#include "Event/Event.h"

namespace SPK
{

#define DEFINE_WINDOW_TYPE(T) \
static Window::Type GetStaticType() \
{ \
    return Window::Type::T; \
} \
\
virtual Window::Type GetType() const override \
{ \
    return GetStaticType(); \
} \

    class Window
    {

    public:
        using EventCallbackFunc = std::function<void(Event&)>;

        enum class Type : int
        {
            None = 0,
            GLFW,
            Win32,
            Headless = None
        };

        struct Description
        {
        public:
            Description(const std::string &title = "Sparkle Engine", uint32_t width = 1, uint32_t height = 1) :
                    Title{ title }, Width{ width }, Height{ height },  EventCallback{ nullptr }
            {

            }

            Description(Description &&other) :
                    Title{ other.Title }, Width{ other.Width }, Height{ other.Height },  EventCallback{ other.EventCallback }
            {

            }

            Description(const Description &other) :
                    Title{ other.Title }, Width{ other.Width }, Height{ other.Height },  EventCallback{ other.EventCallback }
            {

            }

            Description &operator =(const Description &other)
            {
                if (this != &other)
                {
                    Title         = other.Title;
                    Width         = other.Width;
                    Height        = other.Height;
                    EventCallback = other.EventCallback;
                }

                return *this;
            }

            Description &operator =(Description &&other)
            {
                if (this != &other)
                {
                    Title         = std::move(std::move(other.Title));
                    Width         = std::move(other.Width);
                    Height        = std::move(other.Height);
                    EventCallback = std::move(other.EventCallback);
                }

                return *this;
            }

        public:
            EventCallbackFunc EventCallback;

            std::string Title;

            uint32_t Width;

            uint32_t Height;
        };

    public:
        virtual ~Window() { }

        virtual uint32_t Width() const = 0;

        virtual uint32_t Height() const = 0;

        virtual float Time() const { return .0f; }

        virtual void SetEventCallback(const EventCallbackFunc& callback) = 0;

        virtual void *GetNativeWindow() const = 0;

        virtual void SetTitle(const std::string &title) {}

        virtual void SetIcon(const std::string &filepath) {}

        virtual void Show() {}

        virtual void ProcessEvents() = 0;

        virtual Type GetType() const
        {
            return Type::None;
        }

    public:
        static Window *Create(const Description &description = Description{});

    };

} // SPK
