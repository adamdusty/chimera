#include <chimera/sdk.hpp>
#include <snitch/snitch.hpp>

using namespace chimera;

TEST_CASE("Window creation") {
    auto desc       = sdk::window_desc{};
    auto window_res = sdk::window::create(desc);

    CHECK(window_res.has_value());
}

TEST_CASE("Window size") {
    auto desc       = sdk::window_desc{};
    auto window_res = sdk::window::create(desc);

    REQUIRE(window_res);

    auto [w, h] = window_res->size();

    CHECK(w == 1920);
    CHECK(h == 1080);
}