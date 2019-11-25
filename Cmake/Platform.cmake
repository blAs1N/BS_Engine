# Create defines based on platform
if (CMAKE_SYSTEM_NAME MATCHES "Windows") 
	set (PLATFORM_WINDOWS 1) 
elseif (CMAKE_SYSTEM_NAME MATCHES "Linux")
	set (PLATFORM_LINUX 1)
elseif (CMAKE_SYSTEM_NAME MATCHES "Darwin")
	set (PLATFORM_MAC 1)
endif ()

# Determine target architecture
if ((CMAKE_SYSTEM_PROCESSOR MATCHES "AMD64" OR CMAKE_SYSTEM_PROCESSOR MATCHES "x86") AND CMAKE_SIZEOF_VOID_P EQUAL 8)
	set (ARCH_X64 1)
elseif (CMAKE_SYSTEM_PROCESSOR MATCHES "AMD64" AND CMAKE_SIZEOF_VOID_P EQUAL 4)
	set (ARCH_X86 1)
endif ()

# Determine compiler
if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
	set (COMPILER_MSVC 1)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
	set (COMPILER_CLANG 1)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
	set (COMPILER_GCC 1)
endif()