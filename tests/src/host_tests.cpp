#include "pack.hpp"
#include "plugin.hpp"
#include "version.hpp"
#include <snitch/snitch.hpp>
#include <utils.hpp>

using namespace chimera;

TEST_CASE("Plugin manifest from_json", "[plugin_manifest::from_json]") {

    constexpr auto json = R"(
        {
            "namespace": "chimera",
            "name": "add",
            "executable": "libadd",
            "version": {
                "major": 0,
                "minor": 1,
                "patch": 0
            }
        }
    )";

    auto result = plugin_manifest::from_json(json);

    REQUIRE(result);
    CHECK(result->nspace == "chimera");
    CHECK(result->name == "add");
    CHECK(result->plugin_version == version{0, 1, 0});
}

TEST_CASE("Version comparisons", "[version]") {
    auto v0 = version{0, 0, 0};
    auto v1 = version{0, 0, 1};
    auto v2 = version{0, 1, 0};
    auto v3 = version{1, 0, 0};
    auto v4 = version{1, 0, 1};
    auto v5 = version{1, 1, 0};

    CHECK(v0 == v0);
    CHECK(v1 > v0);
    CHECK(v2 > v1);
    CHECK(v3 > v2);
    CHECK(v4 > v3);
    CHECK(v5 > v4);
}

TEST_CASE("Version path operator", "[version]") {
    auto v   = version{1, 5, 24};
    auto dir = std::filesystem::current_path();

    auto res      = dir / v;
    auto expected = dir.string() + "/1.5.24";

    CHECK(res.string() == expected);
}

TEST_CASE("Get executable directory", "[utils]") {
    auto result   = get_executable_dir();
    auto expected = std::filesystem::current_path();

    CHECK(result == expected);
}