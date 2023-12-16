# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imgui-src"
  "/Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imgui-build"
  "/Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imgui-subbuild/imgui-populate-prefix"
  "/Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imgui-subbuild/imgui-populate-prefix/tmp"
  "/Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imgui-subbuild/imgui-populate-prefix/src/imgui-populate-stamp"
  "/Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imgui-subbuild/imgui-populate-prefix/src"
  "/Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imgui-subbuild/imgui-populate-prefix/src/imgui-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imgui-subbuild/imgui-populate-prefix/src/imgui-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imgui-subbuild/imgui-populate-prefix/src/imgui-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
