# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_SOURCE_DIR = /home/jyxk/Code/OSLab/lab03_SharedMemory/separate

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jyxk/Code/OSLab/lab03_SharedMemory/separate/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/reader.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/reader.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/reader.dir/flags.make

CMakeFiles/reader.dir/reader.c.o: CMakeFiles/reader.dir/flags.make
CMakeFiles/reader.dir/reader.c.o: ../reader.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jyxk/Code/OSLab/lab03_SharedMemory/separate/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/reader.dir/reader.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/reader.dir/reader.c.o   -c /home/jyxk/Code/OSLab/lab03_SharedMemory/separate/reader.c

CMakeFiles/reader.dir/reader.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/reader.dir/reader.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jyxk/Code/OSLab/lab03_SharedMemory/separate/reader.c > CMakeFiles/reader.dir/reader.c.i

CMakeFiles/reader.dir/reader.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/reader.dir/reader.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jyxk/Code/OSLab/lab03_SharedMemory/separate/reader.c -o CMakeFiles/reader.dir/reader.c.s

CMakeFiles/reader.dir/sem.c.o: CMakeFiles/reader.dir/flags.make
CMakeFiles/reader.dir/sem.c.o: ../sem.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jyxk/Code/OSLab/lab03_SharedMemory/separate/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/reader.dir/sem.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/reader.dir/sem.c.o   -c /home/jyxk/Code/OSLab/lab03_SharedMemory/separate/sem.c

CMakeFiles/reader.dir/sem.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/reader.dir/sem.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/jyxk/Code/OSLab/lab03_SharedMemory/separate/sem.c > CMakeFiles/reader.dir/sem.c.i

CMakeFiles/reader.dir/sem.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/reader.dir/sem.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/jyxk/Code/OSLab/lab03_SharedMemory/separate/sem.c -o CMakeFiles/reader.dir/sem.c.s

# Object files for target reader
reader_OBJECTS = \
"CMakeFiles/reader.dir/reader.c.o" \
"CMakeFiles/reader.dir/sem.c.o"

# External object files for target reader
reader_EXTERNAL_OBJECTS =

reader: CMakeFiles/reader.dir/reader.c.o
reader: CMakeFiles/reader.dir/sem.c.o
reader: CMakeFiles/reader.dir/build.make
reader: CMakeFiles/reader.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jyxk/Code/OSLab/lab03_SharedMemory/separate/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable reader"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/reader.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/reader.dir/build: reader

.PHONY : CMakeFiles/reader.dir/build

CMakeFiles/reader.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/reader.dir/cmake_clean.cmake
.PHONY : CMakeFiles/reader.dir/clean

CMakeFiles/reader.dir/depend:
	cd /home/jyxk/Code/OSLab/lab03_SharedMemory/separate/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jyxk/Code/OSLab/lab03_SharedMemory/separate /home/jyxk/Code/OSLab/lab03_SharedMemory/separate /home/jyxk/Code/OSLab/lab03_SharedMemory/separate/cmake-build-debug /home/jyxk/Code/OSLab/lab03_SharedMemory/separate/cmake-build-debug /home/jyxk/Code/OSLab/lab03_SharedMemory/separate/cmake-build-debug/CMakeFiles/reader.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/reader.dir/depend

