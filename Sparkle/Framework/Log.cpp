#include "Log.h"

#include <spdlog/async.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/rotating_file_sink.h>

namespace SPK
{

    std::shared_ptr<spdlog::logger> Log::logger;

    void Log::Setup()
    {
        std::vector<spdlog::sink_ptr> logSinks;
        logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
        logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/Sparkle.log"));

        logSinks[0]->set_pattern("%n: [%^%l%$][%T] [%^%s:%!:%#%$]: %v");
        logSinks[1]->set_pattern("[%T] [%l] [%^%s:%!:%#%$] %n: %v  ");

        logger = std::make_shared<spdlog::logger>("Sparkle", logSinks.begin(), logSinks.end());

        logger->set_level(spdlog::level::trace);
        logger->flush_on(spdlog::level::trace);

        spdlog::set_default_logger(logger);
    }

    void Log::Release()
    {
        logger.reset();
    }

} // SPK
