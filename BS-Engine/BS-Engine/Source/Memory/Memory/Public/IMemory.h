#pragma once

#include "Macro.h"

INTERFACE_BEGIN(Memory)
	INTERFACE_DEF(void*, Malloc);
	INTERFACE_DEF(void, Free, void*);
INTERFACE_END