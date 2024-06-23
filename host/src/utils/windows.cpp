#include "utils.hpp"

#include <array>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace chimera {

auto get_executable_dir() -> std::filesystem::path {
    auto path = std::array<char, MAX_PATH>{};
    GetModuleFileName(nullptr, path.data(), MAX_PATH);
    return std::filesystem::canonical(path.data()).parent_path();
}

} // namespace chimera