#pragma once

#include <expected>
#include <filesystem>
#include <string>

#if defined(__WIN32) && __WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
using library = HINSTANCE;
#elif defined(__linux__) && __linux__
using library = void*;
#endif

namespace chimera {

auto load_library(const std::filesystem::path& path) -> std::expected<library, std::string>;

}