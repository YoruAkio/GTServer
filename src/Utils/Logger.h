#pragma once

#include <fmt/chrono.h>
#include <fmt/color.h>
#include <fmt/format.h>

#include <chrono>
#include <iostream>

namespace Logger {
template <typename... Args>
static void Info(const std::string& format, Args&&... args) {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    fmt::print("{}{}{} {}\n", fmt::format(fmt::fg(fmt::color::dark_gray), "["), fmt::format(fmt::fg(fmt::color::lime_green), "INFO"), fmt::format(fmt::fg(fmt::color::dark_gray), "]"),
               fmt::format(fmt::runtime(format), std::forward<Args>(args)...));
}

template <typename... Args>
static void Debug(const std::string& format, Args&&... args) {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    fmt::print("{}{}{} {}\n", fmt::format(fmt::fg(fmt::color::dark_gray), "["), fmt::format(fmt::fg(fmt::color::light_yellow), "DEBUG"), fmt::format(fmt::fg(fmt::color::dark_gray), "]"),
               fmt::format(fmt::runtime(format), std::forward<Args>(args)...));
}

template <typename... Args>
static void Warn(const std::string& format, Args&&... args) {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    fmt::print("{}{}{} {}\n", fmt::format(fmt::fg(fmt::color::dark_gray), "["), fmt::format(fmt::fg(fmt::color::yellow), "WARN"), fmt::format(fmt::fg(fmt::color::dark_gray), "]"),
               fmt::format(fmt::runtime(format), std::forward<Args>(args)...));
}

template <typename... Args>
static void Error(const std::string& format, Args&&... args) {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    fmt::print("{}{}{} {}\n", fmt::format(fmt::fg(fmt::color::dark_gray), "["), fmt::format(fmt::fg(fmt::color::orange_red), "ERROR"), fmt::format(fmt::fg(fmt::color::dark_gray), "]"),
               fmt::format(fmt::runtime(format), std::forward<Args>(args)...));
}
}  // namespace Logger