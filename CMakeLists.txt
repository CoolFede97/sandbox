cmake_minimum_required (VERSION 3.8...4.1.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wno-error=array-bounds)

project ("Sandbox")

include(FetchContent)

#-----------------------------------------------------------------------------------------------------

find_package(Lua 5.4 EXACT REQUIRED)

FetchContent_Declare(
    sol2
    GIT_REPOSITORY https://github.com/ThePhD/sol2.git
    GIT_TAG develop
)
FetchContent_MakeAvailable(sol2)

add_executable(Sandbox "sandbox.cpp")
target_include_directories(Sandbox PRIVATE ${LUA_INCLUDE_DIR})

target_link_libraries(Sandbox
    PRIVATE
    sol2
    ${Lua_LIBRARIES}
)
