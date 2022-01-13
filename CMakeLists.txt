cmake_minimum_required(VERSION 3.10)

project(ground_control)

# set debug and release flags.
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall -O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall -O2")

set (CMAKE_CXX_STANDARD 17)

# file(GLOB_RECURSE ground_control_sources CONFIGURE_DEPENDS "src/*.cpp" "lib/*.cpp")
# message(sources="${ground_control_sources}")
set(ground_control_sources
 "include/gui/gui.hpp"
 "include/gui/gui_main.hpp"
 "include/gui/gui_log.hpp"
 "include/gui/gui_scripting.hpp"
 "src/gui/gui.cpp"
 "src/gui/gui_main.cpp"
 "src/gui/gui_log.cpp"
 "src/gui/gui_scripting.cpp"
 "src/main.cpp"
 )

# add serialib
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/serialib)
include_directories(${PROJECT_SOURCE_DIR}/lib/serialib)

# add glfw
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_DOCS OFF)
set(GLFW_INSTALL OFF)
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/glfw)
include_directories(${PROJECT_SOURCE_DIR}/lib/glfw/include)

# add imgui
include_directories(${PROJECT_SOURCE_DIR}/lib/imgui)
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/imgui)

# add lua
include_directories(${PROJECT_SOURCE_DIR}/lib/lua/lua-5.4.3/include)
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/lua)

# add sol2
include_directories(${PROJECT_SOURCE_DIR}/lib/sol2/include)
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/sol2)

# add groundcontrol
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/gdcl)
include_directories(${PROJECT_SOURCE_DIR}/lib/gdcl/include)

include_directories( ${PROJECT_SOURCE_DIR}/include )
include_directories( ${PROJECT_SOURCE_DIR}/lib )
add_executable(ground_control ${ground_control_sources})


# link dynamic link library. (required for chaiscript)
target_link_libraries(ground_control dl)
# link pthread library. (required for chaiscript)
target_link_libraries(ground_control pthread)

# link serialib
target_link_libraries(ground_control serialib)

# link sol2
target_link_libraries(ground_control sol2 lua_static)

# link glfw and imgui
target_link_libraries(ground_control glfw imgui)

# link gdcl
target_link_libraries(ground_control gdcl)