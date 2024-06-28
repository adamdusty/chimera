#include "rend/rend.hpp"

#include <chimera/rend/export.hpp>
#include <iostream>
#include <spdlog/spdlog.h>

#include <core/core.hpp>

extern "C" {
auto load(const chimera::sdk::context& /* ctx */) -> void {
    spdlog::set_level(spdlog::level::info);
    spdlog::info("Loading chimera:rend");

    int a = 32;
    int b = 64;

    spdlog::info("Using functions from other libs: {}", a * b);
}

auto execute(const chimera::sdk::context& /* ctx */) -> void {}

auto unload(const chimera::sdk::context& /* ctx */) -> void {}
}
