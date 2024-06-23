#include <chimera/sdk.hpp>
#include <snitch/snitch.hpp>

TEST_CASE("Window creation") {
    auto desc       = chimera::window_desc{};
    auto window_res = chimera::window::create(desc);

    CHECK(window_res.has_value());
}

TEST_CASE("Window size") {
    auto desc       = chimera::window_desc{};
    auto window_res = chimera::window::create(desc);

    REQUIRE(window_res);

    auto [w, h] = window_res->size();

    CHECK(w == 1920);
    CHECK(h == 1080);
}