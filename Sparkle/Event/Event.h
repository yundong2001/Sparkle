#pragma once

#include "Core.h"

#define DEFINE_EVENT_TYPE(T) \
static SPK::Event::Type GetStaticType() \
{ \
    return Event::Type::T; \
} \
\
virtual SPK::Event::Type GetType() const override \
{ \
    return GetStaticType(); \
} \
\
virtual std::string Name() const override \
{\
    return #T; \
}

#define DEFINE_EVENT_CATEGORY(category) \
virtual SPK::Event::Category GetCategoryFlags() const override \
{ \
    return category; \
}

namespace SPK
{


    class Event
    {
    public:

        enum class Type
        {
            None = 0,
            WindowClose,
            WindowResize,
            WindowFocus,
            WindowLostFocus,
            WindowMoved,
            AppTick,
            AppUpdate,
            AppRender,
            KeyPressed,
            KeyReleased,
            KeyTyped,
            MouseButtonPressed,
            MouseButtonReleased,
            MouseMoved,
            MouseScrolled,
            MaxCount
        };

        enum class Category
        {
            None = 0,
            Application = BIT(0),
            Input       = BIT(1),
            Keyboard    = BIT(2),
            Mouse       = BIT(3),
            MouseButton = BIT(4)
        };


    public:
        virtual Type GetType() const = 0;

        virtual std::string Name() const = 0;

        virtual Category GetCategoryFlags() const = 0;

        virtual std::string ToString() const
        {
            return Name();
        }

        bool IsInCategory(Category category);

    public:
        bool Handled = false;

    };

    inline constexpr bool operator&(Event::Category a, Event::Category b)
    {
        return static_cast<int>(a) & static_cast<int>(b);
    }

    inline constexpr Event::Category operator|(Event::Category a, Event::Category b)
    {
        return (Event::Category)(static_cast<int>(a) | static_cast<int>(b));
    }

    inline bool Event::IsInCategory(Category category)
    {
        return GetCategoryFlags() & category;
    }

    class EventDispatcher
    {
        template<typename T>
        using EventFn = std::function<bool(T &)>;
    public:
        EventDispatcher(Event &event)
                : event(event)
        {}

        template<typename T>
        bool Dispatch(EventFn<T> func)
        {
            if (event.GetType() == T::GetStaticType())
            {
                event.Handled = func(*(T *) &event);
                return true;
            }
            return false;
        }

    private:
        Event &event;
    };

    inline std::ostream &operator<<(std::ostream&os,const Event& e)
    {
        return os<<e.ToString();
    }
}