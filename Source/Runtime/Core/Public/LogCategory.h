#pragma once

#include "CharSet.h"

struct LogCategory final
{
	String name;
};

#define DECLARE_LOG_CATEGORY(name) extern const LogCategory name;
#define DEFINE_LOG_CATEGORY(name) const LogCategory name{ STR(#name) };
