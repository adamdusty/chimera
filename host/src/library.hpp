#pragma once

#include <expected>
#include <filesystem>
#include <string_view>

namespace chimera {

#if defined(__WIN32) && __WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
using library_type = HINSTANCE;
#elif defined(__linux__) && __linux__
using library_type = void;
#endif

struct library_deleter {
    auto operator()(library_type* lib) -> void;
};

using library = std::unique_ptr<library_type, library_deleter>;

auto load_library(const std::filesystem::path& path) -> std::expected<library, std::string_view>;

} // namespace chimera