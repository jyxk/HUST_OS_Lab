# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/jyxk/Software/clion-2018.2.5/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/jyxk/Software/clion-2018.2.5/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jyxk/Code/OSLab/lab02_Thread/mutex

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jyxk/Code/OSLab/lab02_Thread/mutex/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/mutex.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mutex.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mutex.dir/flags.make

CMakeFiles/mutex.dir/main.c.o: CMakeFiles/mutex.dir/flags.make
CMakeFiles/mutex.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jyxk/Code/OSLab/lab02_Thread/mutex/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/mutex.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mutex.dir/main.c.o   -c /home/jyxk/Code/OSLab/lab02_Thread/mutex/main.c

CMakeFiles/mutex.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mutex.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jyxk/Code/OSLab/lab02_Thread/mutex/main.c > CMakeFiles/mutex.dir/main.c.i

CMakeFiles/mutex.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mutex.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jyxk/Code/OSLab/lab02_Thread/mutex/main.c -o CMakeFiles/mutex.dir/main.c.s

CMakeFiles/mutex.dir/sync.c.o: CMakeFiles/mutex.dir/flags.make
CMakeFiles/mutex.dir/sync.c.o: ../sync.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jyxk/Code/OSLab/lab02_Thread/mutex/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/mutex.dir/sync.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mutex.dir/sync.c.o   -c /home/jyxk/Code/OSLab/lab02_Thread/mutex/sync.c

CMakeFiles/mutex.dir/sync.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mutex.dir/sync.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jyxk/Code/OSLab/lab02_Thread/mutex/sync.c > CMakeFiles/mutex.dir/sync.c.i

CMakeFiles/mutex.dir/sync.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mutex.dir/sync.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jyxk/Code/OSLab/lab02_Thread/mutex/sync.c -o CMakeFiles/mutex.dir/sync.c.s

# Object files for target mutex
mutex_OBJECTS = \
"CMakeFiles/mutex.dir/main.c.o" \
"CMakeFiles/mutex.dir/sync.c.o"

# External object files for target mutex
mutex_EXTERNAL_OBJECTS =

mutex: CMakeFiles/mutex.dir/main.c.o
mutex: CMakeFiles/mutex.dir/sync.c.o
mutex: CMakeFiles/mutex.dir/build.make
mutex: CMakeFiles/mutex.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jyxk/Code/OSLab/lab02_Thread/mutex/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable mutex"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mutex.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mutex.dir/build: mutex

.PHONY : CMakeFiles/mutex.dir/build

CMakeFiles/mutex.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mutex.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mutex.dir/clean

CMakeFiles/mutex.dir/depend:
	cd /home/jyxk/Code/OSLab/lab02_Thread/mutex/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jyxk/Code/OSLab/lab02_Thread/mutex /home/jyxk/Code/OSLab/lab02_Thread/mutex /home/jyxk/Code/OSLab/lab02_Thread/mutex/cmake-build-debug /home/jyxk/Code/OSLab/lab02_Thread/mutex/cmake-build-debug /home/jyxk/Code/OSLab/lab02_Thread/mutex/cmake-build-debug/CMakeFiles/mutex.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mutex.dir/depend

