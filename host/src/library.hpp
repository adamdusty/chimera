#pragma once

#include <chimera/sdk.hpp>
#include <expected>
#include <filesystem>
#include <string_view>

namespace chimera {

#if defined(__WIN32) && __WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
using library_type     = HINSTANCE;
constexpr auto LIB_EXT = "dll";
#elif defined(__linux__) && __linux__
using library_type     = void;
constexpr auto LIB_EXT = "so";
#endif

using on_load_proc   = void (*)(const chimera::context& ctx);
using execute_proc   = void (*)(const chimera::context& ctx);
using on_unload_proc = void (*)(const chimera::context& ctx);

struct library_deleter {
    auto operator()(library_type* lib) -> void;
};

using library = std::unique_ptr<library_type, library_deleter>;

auto load_library(const std::filesystem::path& path) -> std::expected<library, std::string_view>;
auto get_on_load_proc(library_type* lib) -> std::expected<on_load_proc, std::string_view>;
auto get_execute_proc(library_type* lib) -> std::expected<execute_proc, std::string_view>;
auto get_on_unload_proc(library_type* lib) -> std::expected<on_unload_proc, std::string_view>;

} // namespace chimera