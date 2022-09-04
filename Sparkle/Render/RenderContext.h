#pragma once

#include "Framework/Window.h"


namespace SPK
{

    class Swapchain
    {
    public:
        enum class PresentMode
        {
            DoubleBuffer = 2,
            TripleBuffer = 3
        };
    };

    class RenderContext
    {
    public:
        struct Description
        {
            Description() { }

            Description(Window *handle, uint32_t width, uint32_t height, Swapchain::PresentMode mode = Swapchain::PresentMode::TripleBuffer) :
                    WindowHandle{ handle },
                    Width{ width },
                    Height{ height },
                    FrameCount{ static_cast<int>(mode) }
            {

            }

            uint32_t Width{ 0 };

            uint32_t Height{ 0 };

            int FrameCount{ 3 };

            Window *WindowHandle{ nullptr };

            const char *ApplicationName{ "" };

            void Set(Swapchain::PresentMode mode)
            {
                FrameCount = static_cast<int>(mode);
            }
        };

    public:
        static std::unique_ptr<RenderContext> Create(const Description &desc);

    public:
        RenderContext()
        {

        }

        virtual ~RenderContext() = default;

        virtual void SwapBuffers()
        {

        }

        virtual bool HasSwapchain()
        {
            return false;
        }

        virtual const char *GraphicsRenderer() const
        {
            return graphicsRenderer.c_str();
        }

        virtual const char *DriverVersion() const
        {
            return driverVersion.c_str();
        }

        virtual const char *VendorID() const
        {
            return vendor.c_str();
        }

        //TODO  std::shared_ptr<Shader> CreateShader(const std::string &filename, Shader::Type type);

    public:
        RenderContext(const RenderContext &) = delete;
        RenderContext(RenderContext &&) = delete;
        RenderContext &operator=(const RenderContext &) = delete;
        RenderContext &operator=(RenderContext &&) = delete;

        void UpdateMeta(const char *physicalDevice, const char *version, const char *vendor)
        {
            if (physicalDevice)
            {
                this->graphicsRenderer = physicalDevice;
            }
            if (version)
            {
                this->driverVersion = version;
            }
            if (vendor)
            {
                this->vendor = vendor;
            }
        }

    protected:
        std::string graphicsRenderer{};
        std::string driverVersion{};
        std::string vendor{};
    };

    using SuperRenderContext = RenderContext;

} // SPK
