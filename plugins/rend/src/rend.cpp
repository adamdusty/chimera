#include "rend/rend.hpp"

#include <chimera/rend/export.hpp>
#include <iostream>
#include <spdlog/spdlog.h>

// #include <core/core.hpp>

extern "C" {
CHIMERA_EXPORT auto load(const chimera::sdk::context& ctx) -> void {
    std::cerr << "Loading rend...\n";
    spdlog::set_level(spdlog::level::info);
    spdlog::info("Loading chimera:rend");

    int a = 32;
    int b = 64;

    int c = chimera::core::max(a, b);

    spdlog::info("Using functions from other libs: {}", c);
}

CHIMERA_EXPORT auto execute(const chimera::sdk::context& ctx) -> void {}

CHIMERA_EXPORT auto unload(const chimera::sdk::context& ctx) -> void {}
}
