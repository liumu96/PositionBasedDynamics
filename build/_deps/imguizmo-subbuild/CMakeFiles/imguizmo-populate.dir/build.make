# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.26.4/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.26.4/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imguizmo-subbuild

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imguizmo-subbuild

# Utility rule file for imguizmo-populate.

# Include any custom commands dependencies for this target.
include CMakeFiles/imguizmo-populate.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/imguizmo-populate.dir/progress.make

CMakeFiles/imguizmo-populate: CMakeFiles/imguizmo-populate-complete

CMakeFiles/imguizmo-populate-complete: imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-install
CMakeFiles/imguizmo-populate-complete: imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-mkdir
CMakeFiles/imguizmo-populate-complete: imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-download
CMakeFiles/imguizmo-populate-complete: imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-update
CMakeFiles/imguizmo-populate-complete: imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-patch
CMakeFiles/imguizmo-populate-complete: imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-configure
CMakeFiles/imguizmo-populate-complete: imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-build
CMakeFiles/imguizmo-populate-complete: imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-install
CMakeFiles/imguizmo-populate-complete: imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-test
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imguizmo-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Completed 'imguizmo-populate'"
	/opt/homebrew/Cellar/cmake/3.26.4/bin/cmake -E make_directory /Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imguizmo-subbuild/CMakeFiles
	/opt/homebrew/Cellar/cmake/3.26.4/bin/cmake -E touch /Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imguizmo-subbuild/CMakeFiles/imguizmo-populate-complete
	/opt/homebrew/Cellar/cmake/3.26.4/bin/cmake -E touch /Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imguizmo-subbuild/imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-done

imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-update:
.PHONY : imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-update

imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-build: imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-configure
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imguizmo-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "No build step for 'imguizmo-populate'"
	cd /Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imguizmo-build && /opt/homebrew/Cellar/cmake/3.26.4/bin/cmake -E echo_append
	cd /Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imguizmo-build && /opt/homebrew/Cellar/cmake/3.26.4/bin/cmake -E touch /Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imguizmo-subbuild/imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-build

imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-configure: imguizmo-populate-prefix/tmp/imguizmo-populate-cfgcmd.txt
imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-configure: imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-patch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imguizmo-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "No configure step for 'imguizmo-populate'"
	cd /Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imguizmo-build && /opt/homebrew/Cellar/cmake/3.26.4/bin/cmake -E echo_append
	cd /Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imguizmo-build && /opt/homebrew/Cellar/cmake/3.26.4/bin/cmake -E touch /Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imguizmo-subbuild/imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-configure

imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-download: imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-gitinfo.txt
imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-download: imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-mkdir
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imguizmo-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Performing download step (git clone) for 'imguizmo-populate'"
	cd /Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps && /opt/homebrew/Cellar/cmake/3.26.4/bin/cmake -P /Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imguizmo-subbuild/imguizmo-populate-prefix/tmp/imguizmo-populate-gitclone.cmake
	cd /Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps && /opt/homebrew/Cellar/cmake/3.26.4/bin/cmake -E touch /Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imguizmo-subbuild/imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-download

imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-install: imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-build
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imguizmo-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "No install step for 'imguizmo-populate'"
	cd /Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imguizmo-build && /opt/homebrew/Cellar/cmake/3.26.4/bin/cmake -E echo_append
	cd /Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imguizmo-build && /opt/homebrew/Cellar/cmake/3.26.4/bin/cmake -E touch /Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imguizmo-subbuild/imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-install

imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-mkdir:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imguizmo-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Creating directories for 'imguizmo-populate'"
	/opt/homebrew/Cellar/cmake/3.26.4/bin/cmake -Dcfgdir= -P /Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imguizmo-subbuild/imguizmo-populate-prefix/tmp/imguizmo-populate-mkdirs.cmake
	/opt/homebrew/Cellar/cmake/3.26.4/bin/cmake -E touch /Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imguizmo-subbuild/imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-mkdir

imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-patch: imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-update
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imguizmo-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "No patch step for 'imguizmo-populate'"
	/opt/homebrew/Cellar/cmake/3.26.4/bin/cmake -E echo_append
	/opt/homebrew/Cellar/cmake/3.26.4/bin/cmake -E touch /Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imguizmo-subbuild/imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-patch

imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-update:
.PHONY : imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-update

imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-test: imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-install
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imguizmo-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "No test step for 'imguizmo-populate'"
	cd /Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imguizmo-build && /opt/homebrew/Cellar/cmake/3.26.4/bin/cmake -E echo_append
	cd /Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imguizmo-build && /opt/homebrew/Cellar/cmake/3.26.4/bin/cmake -E touch /Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imguizmo-subbuild/imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-test

imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-update: imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-download
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imguizmo-subbuild/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Performing update step for 'imguizmo-populate'"
	cd /Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imguizmo-src && /opt/homebrew/Cellar/cmake/3.26.4/bin/cmake -P /Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imguizmo-subbuild/imguizmo-populate-prefix/tmp/imguizmo-populate-gitupdate.cmake

imguizmo-populate: CMakeFiles/imguizmo-populate
imguizmo-populate: CMakeFiles/imguizmo-populate-complete
imguizmo-populate: imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-build
imguizmo-populate: imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-configure
imguizmo-populate: imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-download
imguizmo-populate: imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-install
imguizmo-populate: imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-mkdir
imguizmo-populate: imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-patch
imguizmo-populate: imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-test
imguizmo-populate: imguizmo-populate-prefix/src/imguizmo-populate-stamp/imguizmo-populate-update
imguizmo-populate: CMakeFiles/imguizmo-populate.dir/build.make
.PHONY : imguizmo-populate

# Rule to build all files generated by this target.
CMakeFiles/imguizmo-populate.dir/build: imguizmo-populate
.PHONY : CMakeFiles/imguizmo-populate.dir/build

CMakeFiles/imguizmo-populate.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/imguizmo-populate.dir/cmake_clean.cmake
.PHONY : CMakeFiles/imguizmo-populate.dir/clean

CMakeFiles/imguizmo-populate.dir/depend:
	cd /Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imguizmo-subbuild && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imguizmo-subbuild /Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imguizmo-subbuild /Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imguizmo-subbuild /Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imguizmo-subbuild /Users/liuxing/Documents/GithubCodeSpace/PositionBasedDynamics/build/_deps/imguizmo-subbuild/CMakeFiles/imguizmo-populate.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/imguizmo-populate.dir/depend

