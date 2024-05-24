#include "sub.hpp"

#include <iostream>

extern "C" {
auto load() -> void {
    std::cerr << "Loading subtraction plugin..." << '\n';
}

auto execute(const chimera::context& ctx) -> void {
    std::cerr << "Subtraction:\n";
    std::cerr << chimera::sub::sub(ctx.a, ctx.b) << '\n';
}

auto unload() -> void {}
}

namespace chimera::sub {

auto sub(int a, int b) -> int {
    return a - b;
}

} // namespace chimera::sub