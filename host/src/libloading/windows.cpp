#include "libloading.hpp"

#include <cstddef>

namespace chimera {

auto load_library(const std::filesystem::path& path) -> std::expected<library, std::string> {
    auto* library = LoadLibrary(path.string().c_str());
    if(library == nullptr) {
        auto error_code        = GetLastError();
        LPSTR error_msg_buffer = nullptr;

        size_t size = FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
            nullptr,
            error_code,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            reinterpret_cast<LPSTR>(&error_msg_buffer),
            0,
            nullptr
        );

        auto message = std::string(error_msg_buffer, size);

        LocalFree(error_msg_buffer);

        return std::unexpected(std::string(error_msg_buffer));
    }

    return library;
}

} // namespace chimera