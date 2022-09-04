#pragma once

#include "Core.h"

namespace SPK
{
    class Queue
    {
    public:
        enum class Type {
            Graphics      = BIT(0),
            Compute       = BIT(1),
            Transfer      = BIT(2),
            SparseBiding  = BIT(3),
            VideoDecoding = BIT(5),
            VideoEncoding = BIT(6)
        };
    };

    BIT_OPERATE(Queue::Type,uint32_t)
}