#include <filesystem>
#include <iostream>
#include <vector>

#include "utils.hpp"
#include <chimera/sdk.hpp>

#include "libloading.hpp"

#include <dlfcn.h>

using execute_proc = void (*)(const chimera::context&);

auto main() -> int {
    auto plugin_dir = chimera::get_executable_dir() / "plugins";
    auto paths      = std::vector<std::filesystem::path>{
        "add/libadd.so",
        "sub/libsub.so",
        "mul/libmul.so",
        "div/libdiv.so",
    };

    auto libs = std::vector<library>();
    for(const auto& path: paths) {
        auto lib = chimera::load_library(plugin_dir / path);
        if(lib) {
            libs.emplace_back(*lib);
        } else {
            std::cerr << "Error loading library at path: " << path << '\n';
            std::cerr << lib.error() << '\n';
        }
    }

    auto execute_procs = std::vector<execute_proc>();
    for(auto* lib: libs) {
        auto proc = reinterpret_cast<execute_proc>(dlsym(lib, "execute"));
        if(proc == nullptr) {
            std::cerr << "Error getting execute procedure" << '\n';
        } else {
            execute_procs.emplace_back(proc);
        }
    }

    auto ctx = chimera::context(64, 8);
    for(auto proc: execute_procs) {
        proc(ctx);
    }

    // auto buf = std::array<char, MAX_PATH>{};
    // GetModuleFileName(nullptr, buf.data(), buf.size());

    // auto path = std::filesystem::path(buf.data()).parent_path();

    // auto manifests = chimera::find_available_plugins(path / "plugins");

    // for(const auto& m: manifests) {
    //     std::cerr << std::format("{}:{}", m.nspace, m.name) << '\n';
    // }

    return 0;
}