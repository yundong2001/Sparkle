#include "Application.h"

#include "Render/RenderContext.h"

namespace SPK
{

#define BIND_EVENT_FN(x) std::bind(&Application::x, this,std::placeholders::_1)

    Application::Application(const Window::Description &desc)
    {
        window.reset(Window::Create(desc));

        window->SetEventCallback(BIND_EVENT_FN(OnEvent));

        context = RenderContext::Create(RenderContext::Description{window.get(),(uint32_t)desc.Width,(uint32_t)desc.Height});
    }

    Application::~Application()
    {

    }

    Layer *Application::PushLayer(Layer *layer)
    {
        layerStack.PushLayer(layer);
        layer->OnAttach();
        //gui->AddLayer(layer);

        return layer;
    }

    Layer *Application::PushOverlay(Layer *overlay)
    {
        layerStack.PushOverlay(overlay);
        overlay->OnAttach();

        return overlay;
    }

    void Application::Run()
    {
        while (runtime.running)
        {

            for (Layer* layer: layerStack)
            {
                layer->OnAttach();
            }
            window->ProcessEvents();
        }
    }

    void Application::Close()
    {
        runtime.running = false;
    }

    void Application::OnEvent(Event &e)
    {
        EventDispatcher dispatcher{e};
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClosed));

        for (auto it = layerStack.end(); it != layerStack.begin(); )
        {
            (*--it)->OnEvent(e);
            if (e.Handled)
            {
                break;
            }
        }
    }

    bool Application::OnWindowClosed(WindowCloseEvent &e)
    {
        runtime.running = false;
        return !runtime.running;
    }

    bool Application::OnWindowResize(WindowResizeEvent &e)
    {
        desc.Width  = e.Width();
        desc.Height = e.Height();
        if (e.Width() == 0 || e.Height() == 0)
        {
            runtime.minimized = true;
        }
        else
        {
            runtime.minimized = false;
            //Render::OnWindowResize(e.Width(), e.Height());
        }

        return runtime.minimized;
    }

} // SPK