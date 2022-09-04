#pragma once

#include "PCH/PCH.h"

#include "Log.h"
#include "Window.h"
#include "LayerStack.h"

#include "Event/Event.h"
#include "Event/ApplicationEvent.h"
#include "Event/KeyEvent.h"
#include "Event/MouseEvent.h"

#include "Window.h"

#include "Render/Render.h"

namespace SPK
{

    class RenderContext;

    class Application
    {
    public:
        Application(const Window::Description &desc = {"Sparkle Engine",800,600});

    public:
        virtual ~Application();

        virtual void Run();

        virtual void Close();

        void OnEvent(Event &e);

        //void UpdateMeta(const Window::Description &desc);

        virtual Layer *PushLayer(Layer *layer);

        virtual Layer *PushOverlay(Layer *overlay);

        virtual Window &GetWindow() const
        {
            return *window;
        }

    private:

        bool OnWindowClosed(WindowCloseEvent &e);

        bool OnWindowResize(WindowResizeEvent &e);

    private:
        std::unique_ptr<Window> window;

        std::unique_ptr<RenderContext> context;

        struct
        {
            bool running   = true;
            bool minimized = false;
        } runtime;

        Window::Description desc;

        LayerStack layerStack;

        float deltaTime;

        std::string name;

    };

} // SPK
