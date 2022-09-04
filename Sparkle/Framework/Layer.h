#pragma once

#include "PCH/PCH.h"

#include "Event/Event.h"

namespace SPK
{

    class Layer
    {
    public:
        Layer(const std::string &name = "Layer");

        virtual ~Layer();

        virtual void OnAttach() { }

        virtual void OnDetach() { }

        virtual void OnUpdate() { }

        virtual void OnGuiRender() { }

        virtual void OnEvent(Event &e) { }

        virtual void Begin() { }

        virtual void End() { }

        const std::string &Name() const
        {
            return debugName;
        }

    protected:

        std::string debugName;
    };

} // SPK
