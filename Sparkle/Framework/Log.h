#pragma once

#include "memory"
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include "spdlog/spdlog.h"

namespace SPK
{

    class Log
    {

    public:
        static void Setup();

        static void Release();

        static void Init()
        {
            Setup();
        }

    public:

        static std::shared_ptr<spdlog::logger>& GetRenderLogger(){return logger;}

    private:
        static std::shared_ptr<spdlog::logger> logger;

    };

} // SPK

#define RENDER_DEBUG(...) SPDLOG_DEBUG(__VA_ARGS__);
#define RENDER_INFO(...) SPDLOG_INFO(__VA_ARGS__);
#define RENDER_WARN(...) SPDLOG_WARN(__VA_ARGS__);
#define RENDER_ERROR(...) SPDLOG_ERROR(__VA_ARGS__);
