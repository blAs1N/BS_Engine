#pragma once

#include <cassert>

template <class T>
class Accessor
{
protected:
	static T& GetManager() noexcept
	{
		assert(manager != nullptr);
		return *manager;
	}

private:
	friend class Game;
	inline static T* manager = nullptr;
};
