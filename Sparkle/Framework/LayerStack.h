#pragma once

#include "Layer.h"

namespace SPK
{

    class LayerStack
    {
    public:

        ~LayerStack();

        Layer *PushLayer(Layer *layer);

        Layer *PushOverlay(Layer *overlay);

        void PopLayer(Layer *layer);

        void PopOverlay(Layer* overlay);

        auto begin()
        {
            return layers.begin();
        }

        auto end()
        {
            return layers.end();
        }

        uint32_t size()
        {
            return layerInsertIndex;
        }

    private:

        std::vector<Layer*> layers;

        uint32_t layerInsertIndex = 0;
    };

} // SPK
