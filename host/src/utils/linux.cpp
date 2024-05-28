#include "utils.hpp"

namespace chimera {

auto get_executable_dir() -> std::filesystem::path {
    return std::filesystem::canonical("/proc/self/exe").parent_path();
}

} // namespace chimera