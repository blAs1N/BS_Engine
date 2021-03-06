#pragma once

#include "CharSet.h"

// The warning is unnecessary because the path variable is used internally.
#pragma warning(disable: 4251)

#ifndef NDEBUG
namespace Impl
{
    [[nodiscard]] CORE_API bool IsDebuggingImpl() noexcept;
}
#endif

[[nodiscard]] NO_ODR bool IsDebugging() noexcept
{
#ifdef NDEBUG
    return false;
#else
    return Impl::IsDebuggingImpl();
#endif
}

class CORE_API Dll final
{
public:
    explicit Dll(StringView inPame);

    Dll(const Dll& other);
    Dll(Dll&& other) noexcept;

    Dll& operator=(const Dll& other);
    Dll& operator=(Dll&& other) noexcept;

    ~Dll();

    [[nodiscard]] void* GetSymbol(StringView name) const;
    [[nodiscard]] void* FindSymbol(StringView name) const noexcept;

    template <class T>
    [[nodiscard]] T& GetSymbol(StringView name) const
    {
        return *reinterpret_cast<T*>(GetSymbol(name));
    }

    template <class T>
    [[nodiscard]] T* FindSymbol(StringView name) const noexcept
    {
        return reinterpret_cast<T*>(FindSymbol(name));
    }

    template <class Fn, class... Args>
    decltype(auto) Call(StringView name, Args&&... args) const
    {
        return GetSymbol<Fn>(name)(std::forward<Args>(args)...);
    }

private:
    void* dll;
    String path;
};
