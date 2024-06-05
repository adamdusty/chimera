#include "pack.hpp"
#include "plugin.hpp"
#include "version.hpp"
#include <snitch/snitch.hpp>

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

TEST_CASE("Pack manifest from JSON") {

    constexpr auto json = R"(
        {
            "namespace": "chimera",
            "name": "testpack",
            "version": {
                "major": 0,
                "minor": 1,
                "patch": 0
            },
            "dependencies": [
                {
                    "namespace": "chimera",
                    "name": "add",
                    "version": {
                        "major": 0,
                        "minor": 1,
                        "patch": 0
                    }
                }
            ]
        }
    )";

    auto result   = pack_manifest::from_json(json);
    auto expected = pack_manifest{
        .nspace       = "chimera",
        .name         = "testpack",
        .pack_version = {0, 1, 0},
        .dependencies = {dependency{.nspace = "chimera", .name = "add", .dependency_version = {0, 1, 0}}},
    };

    REQUIRE(result);
    CHECK(*result == expected);
}