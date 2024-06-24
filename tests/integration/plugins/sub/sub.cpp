#include "sub.hpp"

#include <iostream>

flecs::system sys;

extern "C" {
auto load(const chimera::sdk::context& ctx) -> void {
    flecs::log::warn("Loading subtraction");
    auto entity = ctx.world.entity();
    entity.set<chimera::sub::subtraction_comp>({64, 8});

    sys = ctx.world.system<chimera::sub::subtraction_comp>().iter([](flecs::iter it,
                                                                     chimera::sub::subtraction_comp* sub) {
        for(auto e: it) {
            flecs::log::warn("%d", sub->a - sub->b);
        }
    });
}

auto execute(const chimera::sdk::context& /* ctx */) -> void {
    sys.run();
}

auto unload(const chimera::sdk::context& ctx) -> void {
    // auto entity = ctx.world.entity("sub");
    // entity.destruct();
}
}

namespace chimera::sub {

auto sub(int a, int b) -> int {
    return a - b;
}

} // namespace chimera::sub