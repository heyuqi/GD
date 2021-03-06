#This is the CMake file used to build GDevelop.
#For more information, see the Readme.md file.

cmake_minimum_required(VERSION 2.6)
cmake_policy(SET CMP0011 NEW)

project(GameDevelop)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
IF(NOT WIN32)
	SET(CMAKE_SKIP_BUILD_RPATH  FALSE) #Avoid errors when packaging for linux.
ENDIF()

# Macro for defining an option
macro(gd_set_option var default type docstring)
    if(NOT DEFINED ${var})
        set(${var} ${default})
    endif()
    set(${var} ${${var}} CACHE ${type} ${docstring} FORCE)
endmacro()
gd_set_option(BUILD_CORE TRUE BOOL "TRUE to build GDevelop Core library, FALSE to use the already compiled binaries")
gd_set_option(BUILD_GDCPP TRUE BOOL "TRUE to build GDevelop C++ Platform")
gd_set_option(BUILD_GDJS TRUE BOOL "TRUE to build GDevelop JS Platform")
gd_set_option(BUILD_IDE TRUE BOOL "TRUE to build the IDE")
gd_set_option(BUILD_EXTENSIONS TRUE BOOL "TRUE to build the extensions")
gd_set_option(BUILD_TESTS FALSE BOOL "TRUE to build the tests")
gd_set_option(NO_GUI FALSE BOOL "TRUE to build without any GUI (no wxWidgets GUI, no SFML)")
IF (EMSCRIPTEN)
	set(NO_GUI TRUE) #Force disable gui when compiling with emscripten.
ENDIF()

#Sanity checks
IF ("${CMAKE_BUILD_TYPE}" STREQUAL "")
	message( "CMAKE_BUILD_TYPE is empty, assuming build type is Release" )
	set(CMAKE_BUILD_TYPE Release)
	IF(NOT WIN32)
		SET(CMAKE_SHARED_LINKER_FLAGS "-s") #Force stripping to avoid errors when packaging for linux.
	ENDIF()
ENDIF()
IF(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/ExtLibs/boost")
	message( SEND_ERROR "Boost was not extracted in ExtLibs/boost. Refer to the documentation to get the download link (http://4ian.github.io/GD-Documentation)." )
ENDIF()
IF(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/ExtLibs/SFML")
	message( SEND_ERROR "SFML was not extracted and compiled in ExtLibs/SFML. Refer to the documentation to get the download link (http://4ian.github.io/GD-Documentation)." )
ELSEIF(WIN32)
	IF(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/ExtLibs/SFML/build-mingw-release/lib")
		message("It seems that SFML was not built! Make sure that SFML libraries are built into ExtLibs/SFML/build-mingw-release/lib")
	ENDIF()
ELSEIF(NOT NO_GUI)
	IF(NOT EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/ExtLibs/SFML/build-linux/lib")
		message( SEND_ERROR "It seems that SFML was not built! Make sure that SFML libraries are built into ExtLibs/SFML/build-linux/lib")
	ENDIF()
ENDIF()


#Add all the CMakeLists:
IF(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/Core/CMakeLists.txt" AND BUILD_CORE)
	ADD_SUBDIRECTORY(Core)
ENDIF()
IF(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/GDJS/CMakeLists.txt" AND BUILD_GDJS)
	ADD_SUBDIRECTORY(GDJS)
ENDIF()
IF (NOT EMSCRIPTEN) #Disable GDCpp and the IDE when compiling with emscripten
	IF(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/GDCpp/CMakeLists.txt"  AND BUILD_GDCPP)
		ADD_SUBDIRECTORY(GDCpp)
	ENDIF()
	IF(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/IDE/CMakeLists.txt"  AND BUILD_IDE)
		ADD_SUBDIRECTORY(IDE)
	ENDIF()
ENDIF()
IF(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/Extensions/CMakeLists.txt"  AND BUILD_EXTENSIONS)
	ADD_SUBDIRECTORY(Extensions)
ENDIF()
IF (EMSCRIPTEN)
	IF(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/WebIDE/CMakeLists.txt")
		ADD_SUBDIRECTORY(WebIDE)
	ENDIF()
ENDIF()
