# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/e/ubuntu/chat

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/e/ubuntu/chat/build

# Include any dependencies generated for this target.
include src/server/CMakeFiles/chatServer.dir/depend.make

# Include the progress variables for this target.
include src/server/CMakeFiles/chatServer.dir/progress.make

# Include the compile flags for this target's objects.
include src/server/CMakeFiles/chatServer.dir/flags.make

src/server/CMakeFiles/chatServer.dir/ChatServer.cpp.o: src/server/CMakeFiles/chatServer.dir/flags.make
src/server/CMakeFiles/chatServer.dir/ChatServer.cpp.o: ../src/server/ChatServer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/ubuntu/chat/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/server/CMakeFiles/chatServer.dir/ChatServer.cpp.o"
	cd /mnt/e/ubuntu/chat/build/src/server && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/chatServer.dir/ChatServer.cpp.o -c /mnt/e/ubuntu/chat/src/server/ChatServer.cpp

src/server/CMakeFiles/chatServer.dir/ChatServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chatServer.dir/ChatServer.cpp.i"
	cd /mnt/e/ubuntu/chat/build/src/server && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/e/ubuntu/chat/src/server/ChatServer.cpp > CMakeFiles/chatServer.dir/ChatServer.cpp.i

src/server/CMakeFiles/chatServer.dir/ChatServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chatServer.dir/ChatServer.cpp.s"
	cd /mnt/e/ubuntu/chat/build/src/server && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/e/ubuntu/chat/src/server/ChatServer.cpp -o CMakeFiles/chatServer.dir/ChatServer.cpp.s

src/server/CMakeFiles/chatServer.dir/ChatService.cpp.o: src/server/CMakeFiles/chatServer.dir/flags.make
src/server/CMakeFiles/chatServer.dir/ChatService.cpp.o: ../src/server/ChatService.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/ubuntu/chat/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/server/CMakeFiles/chatServer.dir/ChatService.cpp.o"
	cd /mnt/e/ubuntu/chat/build/src/server && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/chatServer.dir/ChatService.cpp.o -c /mnt/e/ubuntu/chat/src/server/ChatService.cpp

src/server/CMakeFiles/chatServer.dir/ChatService.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chatServer.dir/ChatService.cpp.i"
	cd /mnt/e/ubuntu/chat/build/src/server && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/e/ubuntu/chat/src/server/ChatService.cpp > CMakeFiles/chatServer.dir/ChatService.cpp.i

src/server/CMakeFiles/chatServer.dir/ChatService.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chatServer.dir/ChatService.cpp.s"
	cd /mnt/e/ubuntu/chat/build/src/server && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/e/ubuntu/chat/src/server/ChatService.cpp -o CMakeFiles/chatServer.dir/ChatService.cpp.s

src/server/CMakeFiles/chatServer.dir/main.cc.o: src/server/CMakeFiles/chatServer.dir/flags.make
src/server/CMakeFiles/chatServer.dir/main.cc.o: ../src/server/main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/e/ubuntu/chat/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/server/CMakeFiles/chatServer.dir/main.cc.o"
	cd /mnt/e/ubuntu/chat/build/src/server && /usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/chatServer.dir/main.cc.o -c /mnt/e/ubuntu/chat/src/server/main.cc

src/server/CMakeFiles/chatServer.dir/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chatServer.dir/main.cc.i"
	cd /mnt/e/ubuntu/chat/build/src/server && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/e/ubuntu/chat/src/server/main.cc > CMakeFiles/chatServer.dir/main.cc.i

src/server/CMakeFiles/chatServer.dir/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chatServer.dir/main.cc.s"
	cd /mnt/e/ubuntu/chat/build/src/server && /usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/e/ubuntu/chat/src/server/main.cc -o CMakeFiles/chatServer.dir/main.cc.s

# Object files for target chatServer
chatServer_OBJECTS = \
"CMakeFiles/chatServer.dir/ChatServer.cpp.o" \
"CMakeFiles/chatServer.dir/ChatService.cpp.o" \
"CMakeFiles/chatServer.dir/main.cc.o"

# External object files for target chatServer
chatServer_EXTERNAL_OBJECTS =

../bin/chatServer: src/server/CMakeFiles/chatServer.dir/ChatServer.cpp.o
../bin/chatServer: src/server/CMakeFiles/chatServer.dir/ChatService.cpp.o
../bin/chatServer: src/server/CMakeFiles/chatServer.dir/main.cc.o
../bin/chatServer: src/server/CMakeFiles/chatServer.dir/build.make
../bin/chatServer: src/server/CMakeFiles/chatServer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/e/ubuntu/chat/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable ../../../bin/chatServer"
	cd /mnt/e/ubuntu/chat/build/src/server && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/chatServer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/server/CMakeFiles/chatServer.dir/build: ../bin/chatServer

.PHONY : src/server/CMakeFiles/chatServer.dir/build

src/server/CMakeFiles/chatServer.dir/clean:
	cd /mnt/e/ubuntu/chat/build/src/server && $(CMAKE_COMMAND) -P CMakeFiles/chatServer.dir/cmake_clean.cmake
.PHONY : src/server/CMakeFiles/chatServer.dir/clean

src/server/CMakeFiles/chatServer.dir/depend:
	cd /mnt/e/ubuntu/chat/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/e/ubuntu/chat /mnt/e/ubuntu/chat/src/server /mnt/e/ubuntu/chat/build /mnt/e/ubuntu/chat/build/src/server /mnt/e/ubuntu/chat/build/src/server/CMakeFiles/chatServer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/server/CMakeFiles/chatServer.dir/depend

