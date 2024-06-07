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
auto get_on_load_proc(library_type* lib) -> std::expected<on_load_proc, std::string_view> {
    auto* proc = dlsym(lib, "load");
    if(proc == nullptr) {
        return std::unexpected(dlerror()); // NOLINT
    }

    return reinterpret_cast<on_load_proc>(proc);
}

auto get_execute_proc(library_type* lib) -> std::expected<execute_proc, std::string_view> {
    auto* proc = dlsym(lib, "execute");
    if(proc == nullptr) {
        return std::unexpected(dlerror()); // NOLINT
    }

    return reinterpret_cast<execute_proc>(proc);
}

auto get_on_unload_proc(library_type* lib) -> std::expected<on_unload_proc, std::string_view> {
    auto* proc = dlsym(lib, "unload");
    if(proc == nullptr) {
        return std::unexpected(dlerror()); // NOLINT
    }

    return reinterpret_cast<on_unload_proc>(proc);
}

} // namespace chimera