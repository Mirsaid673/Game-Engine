#pragma once

#include <spdlog/spdlog.h>

namespace Log
{
    template <class... Args>
    void critical(const char *format, Args... args)
    {
        spdlog::critical(format, args...);
    }

    template <class... Args>
    void error(const char *format, Args... args)
    {
        spdlog::error(format, args...);
    }

    template <class... Args>
    void warn(const char *format, Args... args)
    {
        spdlog::warn(format, args...);
    }

    template <class... Args>
    void info(const char *format, Args... args)
    {
        spdlog::info(format, args...);
    }
}