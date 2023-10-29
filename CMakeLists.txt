cmake_minimum_required(VERSION 3.0)
cmake_policy(VERSION 3.0)

project(position-based-dynamics)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)

IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(Sources 
    src/main.cpp
    src/window.cpp
)

INCLUDE_DIRECTORIES(/System/Library/Frameworks)
# find OpenGL, GLUT, GLEW
find_package(OpenGL REQUIRED)
find_package(GLFW3 REQUIRED)
find_package(GLEW REQUIRED)

# find glm
set(glm_DIR /opt/homebrew/Cellar/glm/0.9.9.8/lib/cmake/glm) # if necessary
find_package(glm REQUIRED)

set(glm_DIR /opt/homebrew/Cellar/eigen/3.4.0_1/share/eigen3/cmake)
find_package (Eigen3 3.3 REQUIRED NO_MODULE)

# set(OpenMesh_DIR /opt/homebrew/Cellar/open-mesh/9.0/lib) # if necessary
find_package(OpenMesh REQUIRED)

include_directories( /opt/homebrew/include)

# copy shaders to binary directory
# file(INSTALL ClothSimulation/shaders/ DESTINATION shaders/)

add_executable(position-based-dynamics ${Sources})

add_library(GLAD "src/glad.c")

target_link_libraries(position-based-dynamics 
    ${OPENGL_LIBRARIES} 
    ${GLFW3_LIBRARY} 
    ${GLEW_LIBRARY} 
    ${OPENMESH_CORE_LIBRARY}
    GLAD
    glm::glm
    Eigen3::Eigen)