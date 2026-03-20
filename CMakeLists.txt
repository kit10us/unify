cmake_minimum_required (VERSION 3.29.0)

option(TESTS "Include unit tests" FALSE)
set(CMAKE_SUPPRESS_REGENERATION ON)

if(${CMAKE_CXX_COMPILER})
	message("CMAKE_CXX_COMPILER:" ${CMAKE_CXX_COMPILER})
else()
	message("CMAKE_CXX_COMPILER not set. Can impact project settings.")
endif()
message("")

include(cmakeutil/Functions.txt)

project(unify CXX)

function(GenerateMain)

	set(TARGET_NAME ${PROJECT_NAME})
	set(NAMESPACE "unify")
	
	AddStandardCompileOptions(${TARGET_NAME})


	file (GLOB MAIN_SOURCES "${NAMESPACE}/*.h" "${NAMESPACE}/*.cpp" "${NAMESPACE}/*.inl")
	file (GLOB TEST_SOURCES "${NAMESPACE}/test/*.h" "${NAMESPACE}/test/*.cpp" "${NAMESPACE}/test/*.inl")
	
	add_library(${PROJECT_NAME} ${MAIN_SOURCES} ${TEST_SOURCES})
	
	# Remove unwanted compiler defintions
	remove_definitions(
		${UPPER_TARGET_NAME}_EXPORTS
	)

	AddStandardCompileDefinitions(${TARGET_NAME})
	
	if(WIN32)
		set_target_properties(${PROJECT_NAME} PROPERTIES 
			PREFIX ""
			SUFFIX ".lib"
		)
	endif()

	source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${MAIN_SOURCES})
	source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${TEST_SOURCES})

	include_directories(.)
endfunction()

function(GenerateUnitTests)
endfunction()

GenerateMain()

if(${TESTS})
	message("Including unit tests...")
	GenerateUnitTests()
endif()