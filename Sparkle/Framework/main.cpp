#include "Application.h"

int main()
{


    SPK::Log logger;
    logger.Init();

    RENDER_INFO("Logger Start")

    SPK::Render::Set(SPK::Render::Type::Vulkan);

    SPK::Application application;
    try
    {
        application.Run();
    }
    catch (std::exception& e)
    {
        throw e.what();
        RENDER_INFO("Error")
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
