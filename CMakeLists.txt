cmake_minimum_required(VERSION 3.16)

project(position-based-dynamics)

# set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
list(PREPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# Libigl
include(libigl)

# find_package(LIBIGL REQUIRED QUIET)

# setup libigl properly
igl_include(opengl)
igl_include(glfw)
igl_include(imgui)


# include directories
include_directories(${PROJECT_SOURCE_DIR}/shared/include)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${LIBIGL_INCLUDE_DIR})

# include source code
file(GLOB H_FILES ${PROJECT_SOURCE_DIR}/include/*.h)
file(GLOB H_SHARED_FILES ${PROJECT_SOURCE_DIR}/shared/include/*.h)
file(GLOB CPP_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
file(GLOB CPP_SHARED_FILES ${PROJECT_SOURCE_DIR}/shared/src/*.cpp)

# build executable
add_executable(${PROJECT_NAME} main.cpp ${H_FILES} ${H_SHARED_FILES} ${CPP_FILES} ${CPP_SHARED_FILES})
target_link_libraries(${PROJECT_NAME} PUBLIC igl::opengl igl::glfw igl::imgui)