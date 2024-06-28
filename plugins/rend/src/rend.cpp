#include "rend/rend.hpp"
#include "chimera/rend/export.hpp"
#include "rend/systems.hpp"

#include <spdlog/spdlog.h>

extern "C" {
auto load(const chimera::sdk::context& ctx) -> void {
    spdlog::set_level(spdlog::level::info);
    spdlog::info("Loading chimera:rend");
    auto render_context_creation = chimera::rend::render_context::create(ctx.window);
    if(!render_context_creation) {
        spdlog::error(
            "{}:{}:Error creating render context: {}", plugin_namespace, plugin_name, render_context_creation.error()
        );
        return;
    }

    auto rendering_entity = ctx.world.entity("chimera:rend:context_entity");
    rendering_entity.set<chimera::rend::render_context>(std::move(*render_context_creation));

    ctx.world.system<chimera::rend::render_context>("render system").each(chimera::rend::render_system);
}

auto execute(const chimera::sdk::context& ctx) -> void {}

auto unload(const chimera::sdk::context& ctx) -> void {
    auto rendering_entity = ctx.world.entity("chimera:rend:context_entity");
    rendering_entity.remove<chimera::rend::render_context>();
    rendering_entity.destruct();
}
}
