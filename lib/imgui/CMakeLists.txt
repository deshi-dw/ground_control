cmake_minimum_required(VERSION 3.11)

project(imgui
  LANGUAGES CXX
)

add_library(imgui
 imconfig.h
 imgui.h
 imgui_internal.h
 imstb_rectpack.h
 imstb_textedit.h
 imstb_truetype.h
 backends/imgui_impl_glfw.h
 backends/imgui_impl_opengl3.h
 backends/imgui_impl_opengl3_loader.h
 imgui.cpp
 imgui_draw.cpp
 imgui_widgets.cpp
 imgui_tables.cpp
 imgui_demo.cpp
 backends/imgui_impl_glfw.cpp
 backends/imgui_impl_opengl3.cpp
 misc/cpp/imgui_stdlib.h
 misc/cpp/imgui_stdlib.cpp
)

target_link_libraries(imgui GL)