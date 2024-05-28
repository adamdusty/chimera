#include "libloading.hpp"

namespace chimera {

auto load_library(const std::filesystem::path& path) -> std::expected<library, std::string> {
    return std::unexpected("Unimplemented");
}

} // namespace chimera