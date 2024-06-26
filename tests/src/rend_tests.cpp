#include <rend/rend.hpp>
#include <snitch/snitch.hpp>

using namespace chimera;

TEST_CASE("Context creation") {
    auto desc   = sdk::window_desc{};
    auto window = sdk::window::create(desc);
    REQUIRE(window);

    auto rnd_ctx = rend::render_context::create(*window);

    REQUIRE(rnd_ctx);

    CHECK(rnd_ctx->instance);
    CHECK(rnd_ctx->surface);
    CHECK(rnd_ctx->adapter);
    CHECK(rnd_ctx->device);
    CHECK(rnd_ctx->queue);
}