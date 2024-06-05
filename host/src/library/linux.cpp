#include "library.hpp"

#include <dlfcn.h>

namespace chimera {

auto load_library(const std::filesystem::path& path) -> std::expected<library, std::string_view> {
    auto* lib = dlopen(path.string().c_str(), RTLD_NOW);
    if(lib == nullptr) {
        auto* err = dlerror(); // NOLINT
        return std::unexpected(err);
    }

    return library(lib, library_deleter{});
}

auto library_deleter::operator()(library_type* lib) -> void {
    if(lib != nullptr) {
        dlclose(lib);
    }
}

} // namespace chimera