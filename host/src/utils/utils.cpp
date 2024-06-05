#include "utils.hpp"

namespace chimera {

auto get_plugin_executable_path(const std::filesystem::path& plugin_dir, const plugin_manifest& man)
    -> std::filesystem::path {
    auto this_plugin_dir = std::format(
        "{}-{}-{}.{}.{}",
        man.nspace,
        man.name,
        man.plugin_version.major,
        man.plugin_version.minor,
        man.plugin_version.patch
    );

    return plugin_dir / this_plugin_dir / std::format("{}{}", man.executable_name, chimera::plugin_file_ext);
}

} // namespace chimera