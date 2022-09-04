#include "Queue.h"

#include "Device.h"

namespace SPK
{
    namespace Vulkan
    {
        Queue::Queue(Device *device, uint32_t familyIndex,
                     VkQueueFamilyProperties properties, VkBool32 canPresent,
                     uint32_t index)
                     :device{device},familyIndex{familyIndex},
                     properties{properties},presented{canPresent}
        {
            device->GetQueue(familyIndex,index,&handle);
        }

        Queue::Queue(Queue &&other):
                device{ other.device },
                familyIndex{ other.familyIndex },
                index{ other.index },
                presented{ other.presented },
                properties{ properties }
        {

        }

        Queue::~Queue()
        {

        }
    } // SPK
} // Vulkan