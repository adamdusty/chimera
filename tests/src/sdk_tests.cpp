#include <chimera/sdk.hpp>
#include <snitch/snitch.hpp>

using namespace chimera;

TEST_CASE("Window creation") {
    auto desc   = sdk::window_create_options{};
    auto window = sdk::window(desc);

    CHECK(window.sdl_handle != nullptr);
}

TEST_CASE("Window size") {
    auto desc   = sdk::window_create_options{};
    auto window = sdk::window(desc);

    REQUIRE(window.sdl_handle != nullptr);

    auto [w, h] = window.size();

    CHECK(w == 1920);
    CHECK(h == 1080);
}