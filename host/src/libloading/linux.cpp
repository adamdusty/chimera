#include "libloading.hpp"

#include <dlfcn.h>

namespace chimera {

auto load_library(const std::filesystem::path& path) -> std::expected<library, std::string> {
    auto* library = dlopen(path.string().c_str(), RTLD_NOW);
    if(library == nullptr) {
        auto* err = dlerror(); // NOLINT
        return std::unexpected(err);
    }

    return library;
}

} // namespace chimera