# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.6.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.6.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/mathias/Desktop/EECS332/Instruments/opencv-2.4.13

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/mathias/Desktop/EECS332/Instruments/opencv-2.4.13/build

# Include any dependencies generated for this target.
include modules/stitching/CMakeFiles/opencv_perf_stitching.dir/depend.make

# Include the progress variables for this target.
include modules/stitching/CMakeFiles/opencv_perf_stitching.dir/progress.make

# Include the compile flags for this target's objects.
include modules/stitching/CMakeFiles/opencv_perf_stitching.dir/flags.make

modules/stitching/CMakeFiles/opencv_perf_stitching.dir/perf/perf_main.cpp.o: modules/stitching/CMakeFiles/opencv_perf_stitching.dir/flags.make
modules/stitching/CMakeFiles/opencv_perf_stitching.dir/perf/perf_main.cpp.o: ../modules/stitching/perf/perf_main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mathias/Desktop/EECS332/Instruments/opencv-2.4.13/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object modules/stitching/CMakeFiles/opencv_perf_stitching.dir/perf/perf_main.cpp.o"
	cd /Users/mathias/Desktop/EECS332/Instruments/opencv-2.4.13/build/modules/stitching && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/opencv_perf_stitching.dir/perf/perf_main.cpp.o -c /Users/mathias/Desktop/EECS332/Instruments/opencv-2.4.13/modules/stitching/perf/perf_main.cpp

modules/stitching/CMakeFiles/opencv_perf_stitching.dir/perf/perf_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/opencv_perf_stitching.dir/perf/perf_main.cpp.i"
	cd /Users/mathias/Desktop/EECS332/Instruments/opencv-2.4.13/build/modules/stitching && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mathias/Desktop/EECS332/Instruments/opencv-2.4.13/modules/stitching/perf/perf_main.cpp > CMakeFiles/opencv_perf_stitching.dir/perf/perf_main.cpp.i

modules/stitching/CMakeFiles/opencv_perf_stitching.dir/perf/perf_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/opencv_perf_stitching.dir/perf/perf_main.cpp.s"
	cd /Users/mathias/Desktop/EECS332/Instruments/opencv-2.4.13/build/modules/stitching && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mathias/Desktop/EECS332/Instruments/opencv-2.4.13/modules/stitching/perf/perf_main.cpp -o CMakeFiles/opencv_perf_stitching.dir/perf/perf_main.cpp.s

modules/stitching/CMakeFiles/opencv_perf_stitching.dir/perf/perf_main.cpp.o.requires:

.PHONY : modules/stitching/CMakeFiles/opencv_perf_stitching.dir/perf/perf_main.cpp.o.requires

modules/stitching/CMakeFiles/opencv_perf_stitching.dir/perf/perf_main.cpp.o.provides: modules/stitching/CMakeFiles/opencv_perf_stitching.dir/perf/perf_main.cpp.o.requires
	$(MAKE) -f modules/stitching/CMakeFiles/opencv_perf_stitching.dir/build.make modules/stitching/CMakeFiles/opencv_perf_stitching.dir/perf/perf_main.cpp.o.provides.build
.PHONY : modules/stitching/CMakeFiles/opencv_perf_stitching.dir/perf/perf_main.cpp.o.provides

modules/stitching/CMakeFiles/opencv_perf_stitching.dir/perf/perf_main.cpp.o.provides.build: modules/stitching/CMakeFiles/opencv_perf_stitching.dir/perf/perf_main.cpp.o


modules/stitching/CMakeFiles/opencv_perf_stitching.dir/perf/perf_stich.cpp.o: modules/stitching/CMakeFiles/opencv_perf_stitching.dir/flags.make
modules/stitching/CMakeFiles/opencv_perf_stitching.dir/perf/perf_stich.cpp.o: ../modules/stitching/perf/perf_stich.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/mathias/Desktop/EECS332/Instruments/opencv-2.4.13/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object modules/stitching/CMakeFiles/opencv_perf_stitching.dir/perf/perf_stich.cpp.o"
	cd /Users/mathias/Desktop/EECS332/Instruments/opencv-2.4.13/build/modules/stitching && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/opencv_perf_stitching.dir/perf/perf_stich.cpp.o -c /Users/mathias/Desktop/EECS332/Instruments/opencv-2.4.13/modules/stitching/perf/perf_stich.cpp

modules/stitching/CMakeFiles/opencv_perf_stitching.dir/perf/perf_stich.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/opencv_perf_stitching.dir/perf/perf_stich.cpp.i"
	cd /Users/mathias/Desktop/EECS332/Instruments/opencv-2.4.13/build/modules/stitching && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/mathias/Desktop/EECS332/Instruments/opencv-2.4.13/modules/stitching/perf/perf_stich.cpp > CMakeFiles/opencv_perf_stitching.dir/perf/perf_stich.cpp.i

modules/stitching/CMakeFiles/opencv_perf_stitching.dir/perf/perf_stich.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/opencv_perf_stitching.dir/perf/perf_stich.cpp.s"
	cd /Users/mathias/Desktop/EECS332/Instruments/opencv-2.4.13/build/modules/stitching && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/mathias/Desktop/EECS332/Instruments/opencv-2.4.13/modules/stitching/perf/perf_stich.cpp -o CMakeFiles/opencv_perf_stitching.dir/perf/perf_stich.cpp.s

modules/stitching/CMakeFiles/opencv_perf_stitching.dir/perf/perf_stich.cpp.o.requires:

.PHONY : modules/stitching/CMakeFiles/opencv_perf_stitching.dir/perf/perf_stich.cpp.o.requires

modules/stitching/CMakeFiles/opencv_perf_stitching.dir/perf/perf_stich.cpp.o.provides: modules/stitching/CMakeFiles/opencv_perf_stitching.dir/perf/perf_stich.cpp.o.requires
	$(MAKE) -f modules/stitching/CMakeFiles/opencv_perf_stitching.dir/build.make modules/stitching/CMakeFiles/opencv_perf_stitching.dir/perf/perf_stich.cpp.o.provides.build
.PHONY : modules/stitching/CMakeFiles/opencv_perf_stitching.dir/perf/perf_stich.cpp.o.provides

modules/stitching/CMakeFiles/opencv_perf_stitching.dir/perf/perf_stich.cpp.o.provides.build: modules/stitching/CMakeFiles/opencv_perf_stitching.dir/perf/perf_stich.cpp.o


# Object files for target opencv_perf_stitching
opencv_perf_stitching_OBJECTS = \
"CMakeFiles/opencv_perf_stitching.dir/perf/perf_main.cpp.o" \
"CMakeFiles/opencv_perf_stitching.dir/perf/perf_stich.cpp.o"

# External object files for target opencv_perf_stitching
opencv_perf_stitching_EXTERNAL_OBJECTS =

bin/opencv_perf_stitching: modules/stitching/CMakeFiles/opencv_perf_stitching.dir/perf/perf_main.cpp.o
bin/opencv_perf_stitching: modules/stitching/CMakeFiles/opencv_perf_stitching.dir/perf/perf_stich.cpp.o
bin/opencv_perf_stitching: modules/stitching/CMakeFiles/opencv_perf_stitching.dir/build.make
bin/opencv_perf_stitching: lib/libopencv_stitching.2.4.13.dylib
bin/opencv_perf_stitching: lib/libopencv_ts.a
bin/opencv_perf_stitching: lib/libopencv_nonfree.2.4.13.dylib
bin/opencv_perf_stitching: lib/libopencv_gpu.2.4.13.dylib
bin/opencv_perf_stitching: lib/libopencv_legacy.2.4.13.dylib
bin/opencv_perf_stitching: lib/libopencv_photo.2.4.13.dylib
bin/opencv_perf_stitching: lib/libopencv_ocl.2.4.13.dylib
bin/opencv_perf_stitching: lib/libopencv_ml.2.4.13.dylib
bin/opencv_perf_stitching: lib/libopencv_objdetect.2.4.13.dylib
bin/opencv_perf_stitching: lib/libopencv_calib3d.2.4.13.dylib
bin/opencv_perf_stitching: lib/libopencv_features2d.2.4.13.dylib
bin/opencv_perf_stitching: lib/libopencv_flann.2.4.13.dylib
bin/opencv_perf_stitching: lib/libopencv_highgui.2.4.13.dylib
bin/opencv_perf_stitching: lib/libopencv_video.2.4.13.dylib
bin/opencv_perf_stitching: lib/libopencv_imgproc.2.4.13.dylib
bin/opencv_perf_stitching: lib/libopencv_core.2.4.13.dylib
bin/opencv_perf_stitching: modules/stitching/CMakeFiles/opencv_perf_stitching.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/mathias/Desktop/EECS332/Instruments/opencv-2.4.13/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable ../../bin/opencv_perf_stitching"
	cd /Users/mathias/Desktop/EECS332/Instruments/opencv-2.4.13/build/modules/stitching && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/opencv_perf_stitching.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
modules/stitching/CMakeFiles/opencv_perf_stitching.dir/build: bin/opencv_perf_stitching

.PHONY : modules/stitching/CMakeFiles/opencv_perf_stitching.dir/build

modules/stitching/CMakeFiles/opencv_perf_stitching.dir/requires: modules/stitching/CMakeFiles/opencv_perf_stitching.dir/perf/perf_main.cpp.o.requires
modules/stitching/CMakeFiles/opencv_perf_stitching.dir/requires: modules/stitching/CMakeFiles/opencv_perf_stitching.dir/perf/perf_stich.cpp.o.requires

.PHONY : modules/stitching/CMakeFiles/opencv_perf_stitching.dir/requires

modules/stitching/CMakeFiles/opencv_perf_stitching.dir/clean:
	cd /Users/mathias/Desktop/EECS332/Instruments/opencv-2.4.13/build/modules/stitching && $(CMAKE_COMMAND) -P CMakeFiles/opencv_perf_stitching.dir/cmake_clean.cmake
.PHONY : modules/stitching/CMakeFiles/opencv_perf_stitching.dir/clean

modules/stitching/CMakeFiles/opencv_perf_stitching.dir/depend:
	cd /Users/mathias/Desktop/EECS332/Instruments/opencv-2.4.13/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/mathias/Desktop/EECS332/Instruments/opencv-2.4.13 /Users/mathias/Desktop/EECS332/Instruments/opencv-2.4.13/modules/stitching /Users/mathias/Desktop/EECS332/Instruments/opencv-2.4.13/build /Users/mathias/Desktop/EECS332/Instruments/opencv-2.4.13/build/modules/stitching /Users/mathias/Desktop/EECS332/Instruments/opencv-2.4.13/build/modules/stitching/CMakeFiles/opencv_perf_stitching.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : modules/stitching/CMakeFiles/opencv_perf_stitching.dir/depend

