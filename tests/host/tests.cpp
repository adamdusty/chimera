#include "manifest.hpp"
#include "version.hpp"
#include <snitch/snitch.hpp>

using namespace chimera;

TEST_CASE("Plugin manifest from_json", "[plugin_manifest::from_json]") {

    constexpr auto json = R"(
        {
            "namespace": "chimera",
            "name": "add",
            "executable": "libadd.dll",
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
    CHECK(result->executable == "libadd.dll");
    CHECK(result->version == version{0, 1, 0});
}
