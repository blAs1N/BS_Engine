# Source/Runtime/Engine

register_library ()

target_link_libraries (Engine PUBLIC Framework PRIVATE Input Thread Window)