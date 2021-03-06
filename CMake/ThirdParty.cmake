find_package (BSBase CONFIG REQUIRED)
find_package (BSMath CONFIG REQUIRED)
find_package (fmt CONFIG REQUIRED)
find_package (nlohmann_json CONFIG REQUIRED)
find_package (spdlog CONFIG REQUIRED)
find_package (utf8cpp CONFIG REQUIRED)

if (CMAKE_SYSTEM_NAME MATCHES "Linux")
	find_package (Threads REQUIRED)
endif ()

if (NOT DEFINED BUILD_GAME)
	find_package(GTest)
endif ()