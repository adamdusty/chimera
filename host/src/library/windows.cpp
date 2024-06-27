#include "library.hpp"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <cstddef>

namespace chimera {

auto get_error_msg(DWORD ec) -> std::string {
    LPSTR error_msg_buffer = nullptr;

    size_t size = FormatMessage(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
        nullptr,
        ec,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        reinterpret_cast<LPSTR>(&error_msg_buffer),
        0,
        nullptr
    );

    auto message = std::string(error_msg_buffer, size);

    LocalFree(error_msg_buffer);

    return message;
}

auto library_deleter::operator()(library_type* lib) -> void {
    if(lib != nullptr) {
        FreeLibrary(static_cast<HMODULE>(lib));
    }
}

auto load_library(const std::filesystem::path& path) -> std::expected<library, std::string_view> {
    auto* lib = LoadLibraryEx(
        path.string().c_str(), nullptr, LOAD_LIBRARY_SEARCH_DEFAULT_DIRS | LOAD_LIBRARY_SEARCH_DLL_LOAD_DIR
    );
    // SetDllDirectory(path.parent_path().string().c_str());
    if(lib == nullptr) {
        auto error_code = GetLastError();
        auto msg        = get_error_msg(error_code);

        return std::unexpected(msg);
    }

    return library(lib, library_deleter{});
}

auto get_on_load_proc(library_type* lib) -> std::expected<on_load_proc, std::string_view> {
    auto* proc = GetProcAddress(static_cast<HMODULE>(lib), "load");
    if(proc == nullptr) {
        auto ec  = GetLastError();
        auto msg = get_error_msg(ec);
        return std::unexpected(msg);
    }

    return reinterpret_cast<on_load_proc>(proc);
}

auto get_execute_proc(library_type* lib) -> std::expected<execute_proc, std::string_view> {
    auto* proc = GetProcAddress(static_cast<HMODULE>(lib), "execute");
    if(proc == nullptr) {
        auto ec  = GetLastError();
        auto msg = get_error_msg(ec);
        return std::unexpected(msg);
    }

    return reinterpret_cast<execute_proc>(proc);
}

auto get_on_unload_proc(library_type* lib) -> std::expected<on_unload_proc, std::string_view> {
    auto* proc = GetProcAddress(static_cast<HMODULE>(lib), "unload");
    if(proc == nullptr) {
        auto ec  = GetLastError();
        auto msg = get_error_msg(ec);
        return std::unexpected(msg);
    }

    return reinterpret_cast<on_unload_proc>(proc);
}

} // namespace chimera