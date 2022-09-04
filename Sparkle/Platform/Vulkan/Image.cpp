#include "Image.h"

#include "Device.h"
#include "ImageView.h"
namespace SPK
{
    namespace Vulkan
    {
        inline VkImageType ImageType(VkExtent3D extent)
        {
            VkImageType result{};

            uint32_t depth{ 0 };

            if (extent.width >= 1)
            {
                depth++;
            }

            if (extent.height >= 1)
            {
                depth++;
            }

            if (extent.depth > 1)
            {
                depth++;
            }

            switch (depth)
            {
                case 1:
                    result = VK_IMAGE_TYPE_1D;
                    break;
                case 2:
                    result = VK_IMAGE_TYPE_2D;
                    break;
                case 3:
                    result = VK_IMAGE_TYPE_3D;
                    break;
                default:
                    result = VK_IMAGE_TYPE_2D;
                    break;
            }

            return result;
        }

        Image::Image(Device *device, VkImage handle, const VkExtent3D &extent, VkFormat format,
                     VkImageUsageFlags imageUsage, VkSampleCountFlagBits sampleCount):
                     device{device},handle{handle}
        {
            subresource.mipLevel   = 1;
            subresource.arrayLayer = 1;

            info.imageType = ImageType(extent);
            info.extent    = extent;
            info.format    = format;
            info.samples   = sampleCount;
            info.usage     = imageUsage;
        }

        Image::Image(Device *device, const VkExtent3D &extent, VkFormat format, VkImageUsageFlags imageUsage,
                     VkSampleCountFlagBits sampleCount, uint32_t mipLevels, uint32_t arrayLayers, VkImageTiling tiling,
                     VkImageCreateFlags flags, uint32_t numQueueFamilies, const uint32_t *queueFamilies):
                     device{device}
        {
            assert(mipLevels > 0 && "Image should have at least one level");
            assert(arrayLayers > 0 && "Image should have at least one layer");

            subresource.mipLevel   = mipLevels;
            subresource.arrayLayer = arrayLayers;

            info.sType         = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
            info.imageType     = Vulkan::ImageType(extent);
            info.format        = format;
            info.extent        = extent;
            info.mipLevels     = mipLevels;
            info.arrayLayers   = arrayLayers;
            info.samples       = sampleCount;
            info.tiling        = tiling;
            info.usage         = imageUsage;
            info.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;

            if (numQueueFamilies != 0)
            {
                info.sharingMode           = VK_SHARING_MODE_CONCURRENT;
                info.queueFamilyIndexCount = numQueueFamilies;
                info.pQueueFamilyIndices   = queueFamilies;
            }

            Check(device->Create(&info,&handle));
        }

        Image::Image(Device *device, VkImageCreateInfo &createInfo):
        device{device}
        {
            info = createInfo;
            subresource.mipLevel = createInfo.mipLevels;
            subresource.arrayLayer = createInfo.arrayLayers;

            Check(device->Create(&info, &handle));
        }

        Image::Image(Image &&other) :
                device{ other.device },
                handle{ other.handle },
                subresource{ other.subresource },
                mappedData{ other.mappedData },
                mapped{ other.mapped },
                views{ std::move(other.views) }
        {
            memcpy(&this->info,&other.info,sizeof(VkImageCreateInfo));

            other.handle     = VK_NULL_HANDLE;
            other.mappedData = nullptr;
            other.mapped     = false;

            for (auto& v : views)
            {
                v->Set(this);
            }
        }

        Image::Image(const Image &other) :
                device{ other.device },
                handle{ other.handle },
                subresource{ other.subresource },
                mappedData{ other.mappedData },
                mapped{ other.mapped },
                views{ other.views }
        {
            memcpy(&this->info,&other.info,sizeof(VkImageCreateInfo));

            for (auto& v : views)
            {
                v->Set(this);
            }
        }

        Image::~Image()
        {
            if (handle != VK_NULL_HANDLE && device != nullptr)
            {
                device->Destroy(handle);
            }
        }

    } // SPK
} // Vulkan