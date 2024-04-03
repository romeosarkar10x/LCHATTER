cmake_minimum_required(VERSION 3.10)

project(LCHATTER)

# Set C++20 as the standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

set(IMGUI_DIR "Frontend/Frontend_Imgui/externals/imgui")
set(FRONTEND_SRC_DIR "Frontend/Frontend_ImGui/src")
set(BACKEND_SRC_DIR "Backend/Src")

message(STATUS "The value of MY_VARIABLE is: ${FRONTEND_SRC_DIR}")

include_directories(${IMGUI_DIR} ${IMGUI_DIR}/backends)

set(SOURCES
${FRONTEND_SRC_DIR}/Main.cpp
${IMGUI_DIR}/imgui.cpp
${IMGUI_DIR}/imgui_demo.cpp
${IMGUI_DIR}/imgui_draw.cpp
${IMGUI_DIR}/imgui_tables.cpp
${IMGUI_DIR}/imgui_widgets.cpp
${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

# Include all .cpp files from the BACKEND_SRC_DIR directory recursively
file(GLOB_RECURSE BACKEND_SOURCES ${BACKEND_SRC_DIR}/*.cpp)

# Append the backend sources to the main SOURCES variable
list(APPEND SOURCES ${BACKEND_SOURCES})

add_executable(LCHATTER ${SOURCES})  # Create the executable
target_link_libraries(LCHATTER PRIVATE glfw OpenGL::GL ws2_32)
