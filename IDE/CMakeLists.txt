cmake_minimum_required(VERSION 2.6)
cmake_policy(SET CMP0015 NEW)

project(GDIDE)

#Sanity checks and options
IF ("${CMAKE_BUILD_TYPE}" STREQUAL "")
  	message( "CMAKE_BUILD_TYPE is empty, assuming build type is Release" )
	set(CMAKE_BUILD_TYPE Release)
ENDIF()
if(CMAKE_COMPILER_IS_GNUCXX)
	IF ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
    	set(CMAKE_EXE_LINKER_FLAGS "-s")  ## Strip binary
    ENDIF()
endif()

#Common directories:
###
set(GD_base_dir ${CMAKE_CURRENT_SOURCE_DIR}/..)
set(GDCORE_include_dir ${GD_base_dir}/Core)
set(GDCORE_lib_dir ${GD_base_dir}/Binaries/Output/${CMAKE_BUILD_TYPE}_${CMAKE_SYSTEM_NAME})
set(GDCpp_include_dir ${GD_base_dir}/GDCpp)
set(GDCpp_lib_dir ${GD_base_dir}/Binaries/Output/${CMAKE_BUILD_TYPE}_${CMAKE_SYSTEM_NAME})
set(boost_include_dir ${GD_base_dir}/ExtLibs/boost)
set(sfml_include_dir ${GD_base_dir}/ExtLibs/SFML/include)
IF(WIN32)
	IF(CMAKE_BUILD_TYPE MATCHES DEBUG)
		set(sfml_lib_dir ${GD_base_dir}/ExtLibs/SFML/build-mingw-debug/lib)
	ELSE()
		set(sfml_lib_dir ${GD_base_dir}/ExtLibs/SFML/build-mingw-release/lib)
	ENDIF()
ELSE()
	set(sfml_lib_dir ${GD_base_dir}/ExtLibs/SFML/build-linux/lib)
ENDIF()
IF(WIN32) #Special case for wxWidgets on Windows
	set(wxwidgets_include_dir ${GD_base_dir}/ExtLibs/wxwidgets/include)
	IF(CMAKE_BUILD_TYPE MATCHES DEBUG)
		set(wxwidgets_include_dir ${wxwidgets_include_dir} ${GD_base_dir}/ExtLibs/wxwidgets/lib/gcc_dll/mswud)
	ELSE()
		set(wxwidgets_include_dir ${wxwidgets_include_dir} ${GD_base_dir}/ExtLibs/wxwidgets/lib/gcc_dll/mswu)
	ENDIF(CMAKE_BUILD_TYPE MATCHES DEBUG)
	set(wxwidgets_lib_dir ${GD_base_dir}/ExtLibs/wxwidgets/lib/gcc_dll)
ENDIF(WIN32)

#Dependencies on external libraries:
###
include_directories(${boost_include_dir})
include_directories(${sfml_include_dir})
include_directories(${GDCORE_include_dir})
include_directories(${GDCpp_include_dir})
IF(WIN32) #Special case for wxWidgets on Windows
	include_directories(${wxwidgets_include_dir})
ELSE()
	find_package(wxWidgets COMPONENTS core base adv net ribbon webview stc aui propgrid richtext html xrc REQUIRED)
	include( "${wxWidgets_USE_FILE}" )
	find_package(PkgConfig REQUIRED)
	pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
	include_directories(${GTK3_INCLUDE_DIRS})
	link_directories(${GTK3_LIBRARY_DIRS})
ENDIF(WIN32)

#Defines
###
add_definitions( -DGD_IDE_ONLY )
IF(CMAKE_BUILD_TYPE MATCHES DEBUG)
	add_definitions( -DDEBUG )
	IF(WIN32)
		add_definitions( __WXDEBUG__ )
	ENDIF(WIN32)
ELSEIF ("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
	add_definitions( -DRELEASE )
	add_definitions( -DBOOST_DISABLE_ASSERTS )
ELSE()
	add_definitions( -DDEV )
	add_definitions( -DBOOST_DISABLE_ASSERTS )
ENDIF(CMAKE_BUILD_TYPE MATCHES DEBUG)

IF(WIN32)
	add_definitions( -DWINDOWS )
	add_definitions( "-DGD_CORE_API=__declspec(dllimport)" )
	add_definitions( "-DGD_API=__declspec(dllimport)" )
	add_definitions( -D__GNUWIN32__ )
	add_definitions( -D__WXMSW__ )
	add_definitions( -DwxUSE_UNICODE=1 )
	add_definitions( -DWXUSINGDLL )
ELSE()
	add_definitions( -DLINUX )
	add_definitions( -DGD_API= )
	add_definitions( -DGD_CORE_API= )
	add_definitions(${GTK3_CFLAGS_OTHER})
ENDIF(WIN32)


#The targets
###
include_directories(.)
include_directories(wxstedit/include)
file(GLOB source_files * Dialogs/* wxstedit/src/*)
file(GLOB exe_source_files Launcher/*)

IF(WIN32)
	add_library(GDIDE SHARED ${source_files})
	add_executable(GDIDE_exe WIN32 ${exe_source_files})
	add_executable(GDIDE_dev_exe ${exe_source_files})
ELSE()
	add_executable(GDIDE ${source_files})
ENDIF(WIN32)
set_target_properties(GDIDE PROPERTIES PREFIX "")
set_target_properties(GDIDE PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${GD_base_dir}/Binaries/Output/${CMAKE_BUILD_TYPE}_${CMAKE_SYSTEM_NAME}")
set_target_properties(GDIDE PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${GD_base_dir}/Binaries/Output/${CMAKE_BUILD_TYPE}_${CMAKE_SYSTEM_NAME}")
set_target_properties(GDIDE PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${GD_base_dir}/Binaries/Output/${CMAKE_BUILD_TYPE}_${CMAKE_SYSTEM_NAME}")
IF(WIN32)
set_target_properties(GDIDE_exe PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${GD_base_dir}/Binaries/Output/${CMAKE_BUILD_TYPE}_${CMAKE_SYSTEM_NAME}/")
set_target_properties(GDIDE_dev_exe PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${GD_base_dir}/Binaries/Output/${CMAKE_BUILD_TYPE}_${CMAKE_SYSTEM_NAME}/")
set_target_properties(GDIDE_exe PROPERTIES RUNTIME_OUTPUT_NAME "GDIDE")
set_target_properties(GDIDE_dev_exe PROPERTIES RUNTIME_OUTPUT_NAME "GDIDE_dev")
ENDIF(WIN32)

#Linker files for GDIDE
###
target_link_libraries(GDIDE GDCore)
target_link_libraries(GDIDE GDCpp)
IF(WIN32)
	target_link_libraries(GDIDE ${sfml_lib_dir}/libsfml-audio.a ${sfml_lib_dir}/libsfml-graphics.a ${sfml_lib_dir}/libsfml-window.a ${sfml_lib_dir}/libsfml-network.a ${sfml_lib_dir}/libsfml-system.a)
	target_link_libraries(GDIDE_exe ${sfml_lib_dir}/libsfml-audio.a ${sfml_lib_dir}/libsfml-graphics.a ${sfml_lib_dir}/libsfml-window.a ${sfml_lib_dir}/libsfml-network.a ${sfml_lib_dir}/libsfml-system.a)
	target_link_libraries(GDIDE_dev_exe ${sfml_lib_dir}/libsfml-audio.a ${sfml_lib_dir}/libsfml-graphics.a ${sfml_lib_dir}/libsfml-window.a ${sfml_lib_dir}/libsfml-network.a ${sfml_lib_dir}/libsfml-system.a)
	IF(CMAKE_BUILD_TYPE MATCHES DEBUG)
		target_link_libraries(GDIDE ${wxwidgets_lib_dir}/libwxmsw29ud_stc.a ${wxwidgets_lib_dir}/libwxmsw29ud_webview.a ${wxwidgets_lib_dir}/libwxmsw29ud_xrc.a ${wxwidgets_lib_dir}/libwxmsw29ud_stc.a ${wxwidgets_lib_dir}/libwxmsw29ud_richtext.a ${wxwidgets_lib_dir}/libwxmsw29ud_propgrid.a ${wxwidgets_lib_dir}/libwxmsw29ud_ribbon.a ${wxwidgets_lib_dir}/libwxmsw29ud_aui.a ${wxwidgets_lib_dir}/libwxmsw29ud_adv.a ${wxwidgets_lib_dir}/libwxmsw29ud_html.a ${wxwidgets_lib_dir}/libwxmsw29ud_core.a ${wxwidgets_lib_dir}/libwxbase29ud_xml.a ${wxwidgets_lib_dir}/libwxbase29ud_net.a ${wxwidgets_lib_dir}/libwxexpatd.a ${wxwidgets_lib_dir}/libwxbase29ud.a ${wxwidgets_lib_dir}/libwxpngd.a ${wxwidgets_lib_dir}/libwxjpegd.a ${wxwidgets_lib_dir}/libwxzlibd.a ${wxwidgets_lib_dir}/libwxtiffd.a)
	ELSE()
		target_link_libraries(GDIDE ${wxwidgets_lib_dir}/libwxmsw29u_stc.a ${wxwidgets_lib_dir}/libwxmsw29u_webview.a ${wxwidgets_lib_dir}/libwxmsw29u_xrc.a ${wxwidgets_lib_dir}/libwxmsw29u_stc.a ${wxwidgets_lib_dir}/libwxmsw29u_richtext.a ${wxwidgets_lib_dir}/libwxmsw29u_propgrid.a ${wxwidgets_lib_dir}/libwxmsw29u_ribbon.a ${wxwidgets_lib_dir}/libwxmsw29u_aui.a ${wxwidgets_lib_dir}/libwxmsw29u_adv.a ${wxwidgets_lib_dir}/libwxmsw29u_html.a ${wxwidgets_lib_dir}/libwxmsw29u_core.a ${wxwidgets_lib_dir}/libwxbase29u_xml.a ${wxwidgets_lib_dir}/libwxbase29u_net.a ${wxwidgets_lib_dir}/libwxexpat.a ${wxwidgets_lib_dir}/libwxbase29u.a ${wxwidgets_lib_dir}/libwxpng.a ${wxwidgets_lib_dir}/libwxjpeg.a ${wxwidgets_lib_dir}/libwxzlib.a ${wxwidgets_lib_dir}/libwxtiff.a)
	ENDIF(CMAKE_BUILD_TYPE MATCHES DEBUG)

	target_link_libraries(GDIDE ws2_32 user32 opengl32 glu32)
	target_link_libraries(GDIDE_exe ws2_32 user32 opengl32 glu32)
	target_link_libraries(GDIDE_dev_exe ws2_32 user32 opengl32 glu32)
ELSE()
	target_link_libraries(GDIDE ${sfml_lib_dir}/libsfml-audio.so ${sfml_lib_dir}/libsfml-graphics.so ${sfml_lib_dir}/libsfml-window.so ${sfml_lib_dir}/libsfml-network.so ${sfml_lib_dir}/libsfml-system.so)
	target_link_libraries(GDIDE ${wxWidgets_LIBRARIES})
	target_link_libraries(GDIDE ${GTK3_LIBRARIES})
	target_link_libraries(GDIDE GLU GL)
ENDIF(WIN32)


#Post build tasks
###
IF(EMSCRIPTEN)
	#Nothing.
ELSE()

	#Extra files (icons, examples, game templates, translations...) are stored in the Release_Windows
	#output directory, and need to be copied.
	IF(NOT WIN32)
		add_custom_command(TARGET GDIDE
			POST_BUILD
			COMMAND sh "CopyWindowsToLinuxReleaseFiles.sh" ${CMAKE_BUILD_TYPE}_${CMAKE_SYSTEM_NAME}
			WORKING_DIRECTORY ${GD_base_dir}/scripts)
		add_custom_command(TARGET GDIDE
			POST_BUILD
			COMMAND sh "copyLinuxLibraries.sh" ${GD_base_dir}/Binaries/Output/${CMAKE_BUILD_TYPE}_${CMAKE_SYSTEM_NAME}/
			WORKING_DIRECTORY ${GD_base_dir}/IDE/scripts)
	ENDIF()
ENDIF()
