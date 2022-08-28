#pragma once

#include <memory>

#include "spdlog/logger.h"

namespace raytracing
{
    class Log
    {
    public:
        static void init();
        inline static std::shared_ptr<spdlog::logger>& getLogger() { return s_Logger; }

    private:
        static std::shared_ptr<spdlog::logger> s_Logger;
    };
};

#ifdef DEBUG
#define RT_TRACE(...)   raytracing::Log::getLogger()->trace(__VA_ARGS__)
#define RT_DEBUG(...)   raytracing::Log::getLogger()->debug(__VA_ARGS__)
#define RT_INFO(...)    raytracing::Log::getLogger()->info(__VA_ARGS__)
#define RT_WARN(...)    raytracing::Log::getLogger()->warn(__VA_ARGS__)
#define RT_ERROR(...)   raytracing::Log::getLogger()->error(__VA_ARGS__)
#define RT_FATAL(...)   raytracing::Log::getLogger()->critical(__VA_ARGS__)
#else
#define RT_TRACE(...)
#define RT_DEBUG(...)
#define RT_INFO(...)
#define RT_WARN(...)
#define RT_ERROR(...)
#define RT_FATAL(...)
#endif // DEBUG