#ifdef WINDOWS

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#include "Platform.h"
#include <Windows.h>
#include "Assertion.h"

#ifndef NDEBUG

bool Impl::IsDebuggingImpl() noexcept
{
    return IsDebuggerPresent();
}

#endif

namespace
{
    String GetLastErrorMsg()
    {
        constexpr static auto MaxSize = 512;
        static wchar_t buffer[MaxSize];

        FormatMessageW(
            FORMAT_MESSAGE_FROM_SYSTEM,
            nullptr,
            GetLastError(),
            0,
            buffer,
            MaxSize,
            nullptr
        );
        
        const std::wstring msg(buffer);
        return String(msg.begin(), msg.end());
    }
}

Dll::Dll(StringView inPath)
    : path(inPath.data())
{
    const std::wstring wPath(path.cbegin(), path.cend());
    dll = LoadLibraryW(wPath.c_str());
    AssertMsg(dll, STR("{}: cannot load module, {}"), path, GetLastErrorMsg());
}

Dll::Dll(const Dll& other)
    : path(other.path)
{
    if (dll) FreeLibrary(reinterpret_cast<HMODULE>(dll));
    dll = other.dll;
}

Dll::Dll(Dll&& other) noexcept
    : path(std::move(other.path))
{
    if (dll) FreeLibrary(reinterpret_cast<HMODULE>(dll));
    dll = std::move(other.dll);
}

Dll& Dll::operator=(const Dll& other)
{
    if (dll)
        FreeLibrary(reinterpret_cast<HMODULE>(dll));
    
    dll = other.dll;
    path = other.path;
    return *this;
}

Dll& Dll::operator=(Dll&& other) noexcept
{
    if (dll)
        FreeLibrary(reinterpret_cast<HMODULE>(dll));
    
    dll = std::move(other.dll);
    path = std::move(other.path);
    return *this;
}

Dll::~Dll()
{
    FreeLibrary(reinterpret_cast<HMODULE>(dll));
}

void* Dll::GetSymbol(StringView name) const
{
    const auto symbol = FindSymbol(name);
    if (EnsureMsg(symbol, STR("Path: {}, Name: {}, {}"), path, name, GetLastErrorMsg()))
        return symbol;

    return nullptr;
}

void* Dll::FindSymbol(StringView name) const noexcept
{
    const auto buf = CastCharSet<char>(StringView{ name });
    return reinterpret_cast<void*>(GetProcAddress(reinterpret_cast<HMODULE>(dll), buf.c_str()));
}

#endif
