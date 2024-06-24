#pragma once

#include <expected>

#include <chimera/sdk.hpp>
#include <echidna/echidna.hpp>

#include "chimera/rend/export.hpp"

namespace chimera::rend {

struct CHIMERA_EXPORT render_context {
    echidna::instance instance;
    echidna::surface surface;
    echidna::adapter adapter;
    echidna::device device;
    echidna::queue queue;

    static auto create(const sdk::window& window) -> std::expected<render_context, std::string>;
};
} // namespace chimera::rend