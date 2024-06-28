cmake_minimum_required (VERSION 3.29.0)

option(TESTS "Include unit tests" FALSE)
set(CMAKE_SUPPRESS_REGENERATION ON)

if(${CMAKE_CXX_COMPILER})
	message("CMAKE_CXX_COMPILER:" ${CMAKE_CXX_COMPILER})
else()
	message("CMAKE_CXX_COMPILER not set. Can impact project settings.")
endif()
message("")

function(GenerateUnify)
	project (unify)

	set(TARGET_NAME ${PROJECT_NAME})
		
	# Specify build output directories.
	set(PROJECT_BINARY_DIR lib/$(Platform)/$(Configuration)/)
	set(PROJECT_LIBRARY_DIR lib/$(Platform)/$(Configuration)/$(ProjectName)/)
	set(PROJECT_ARCHIVE_DIR lib/$(Platform)/$(Configuration)/)

	if(WIN32)
		# Enable C++17 support.
		add_compile_options(/std:c++17)

		# See https://learn.microsoft.com/en-us/cpp/build/reference/eh-exception-handling-model?view=msvc-170
		add_compile_options(/EHsc)
		
		set(CMAKE_CONFIGURATION_TYPES 
			"DebugWindows;ReleaseWindows"
			CACHE STRING "" FORCE
		)

		add_compile_definitions(
			_UNICODE
			UNICODE
			_LIB
		)
	elseif(APPLE)
		# Enable C++17 support.
		add_compile_options(-std=c++17)
		# Older flag for Xcode: add_compile_options(-std=c++1z)
	endif()

	foreach(CONFIG ${CMAKE_CONFIGURATION_TYPES})
		string(TOUPPER ${CONFIG} CONFIG)
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONFIG} "${PROJECT_BINARY_DIR}")
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONFIG} "${PROJECT_LIBRARY_DIR}")
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CONFIG} "${PROJECT_ARCHIVE_DIR}")
	endforeach(CONFIG CMAKE_CONFIGURATION_TYPES)

	file (GLOB UNIFY_SOURCES "unify/*.h" "unify/*.cpp" "unify/*.inl")
	file (GLOB TEST_SOURCES  "unify/test/*.h" "unify/test/*.cpp" "unify/test/*.inl")
	
	add_compile_definitions(_DEBUG)
	
	add_library(${PROJECT_NAME} ${UNIFY_SOURCES} ${TEST_SOURCES})

	if(WIN32)
		set_target_properties(${PROJECT_NAME} PROPERTIES 
			PREFIX ""
			SUFFIX ".lib"
		)
	endif()

	source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${UNIFY_SOURCES})
	source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TEST_SOURCES})

	include_directories(.)

	#set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT Unify)
endfunction()

function(GenerateUnitTests)
endfunction()

GenerateUnify()

#set_target_properties(ALL_BUILD ZERO_CHECK PROPERTIES
#	EXCLUDE_FROM_ALL 1
#)


if(${TESTS})
	message("Including unit tests...")
	GenerateUnitTests()
endif()