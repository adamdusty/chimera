#include "utils.hpp"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

namespace chimera {

auto get_executable_path() -> std::filesystem::path {
    auto buf = std::array<char, MAX_PATH>{};
    GetModuleFileName(nullptr, buf.data(), buf.size());

    return std::filesystem::path(buf.data()).parent_path();
}

} // namespace chimera