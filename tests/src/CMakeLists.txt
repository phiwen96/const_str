# set (${self} test_${PROJECT_NAME})

message("adding tests...")

if (NOT TARGET Catch2)
	include (FetchContent)

	FetchContent_Declare(
		Catch2
		GIT_REPOSITORY https://github.com/catchorg/Catch2.git
		GIT_TAG        v2.13.1)

	FetchContent_MakeAvailable (Catch2)
endif ()


file(GLOB_RECURSE HEADER_LIST "../include/*.hpp")
file(GLOB SOURCE_LIST *.cpp)


# set (deps )
# macro (ph_add_test name)
	add_executable (test_const_str ${SOURCE_LIST} ${HEADER_LIST})
	# set_target_properties(test_const_str          PROPERTIES FOLDER "main/${PROJECT_NAME}/tests")
	# source_group (bajs//kiss test_${name}.cpp)
	source_group(TREE ${CMAKE_CURRENT_LIST_DIR}
            PREFIX "sources"               
            FILES  ${SOURCE_LIST}
        )

	# source_group(TREE "ph_data_structures/include/*.hpp"
    #         PREFIX "include"               
    #         FILES  ${HEADER_LIST}
    #     )
	# set_target_properties(test_${name} PROPERTIES PROJECT_LABEL "test_${name}Foo Tastic")
	target_link_libraries (test_const_str PUBLIC const_str Catch2::Catch2)
	target_include_directories (test_const_str PUBLIC ../include)
	ph_precompile (TARGET test_const_str PUBLIC PCH ${std_pch})

	if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
	# message("kuk")
		# set_target_properties(test_const_str          PROPERTIES FOLDER "main/const_str/tests")
	else ()
		# message("kuk")

		# set_target_properties(test_const_str          PROPERTIES FOLDER "dependencies/tests/const_str")
	endif()		
# endmacro ()

# Create_cpp_tests (
# 	TARGETS 
# 		"concepts"
# 		"uni"
# 		"vari"
# 		"typelist"
# )

# ph_add_test (concepts)
# ph_add_test (uni)
# ph_add_test (vari)
# ph_add_test (typelist)
# ph_add_test (typetraits)
# ph_add_test (Arithmetic)
# ph_add_test (Array)
# ph_add_test (Bool)
# ph_add_test (Char)
# ph_add_test (Floating)
# ph_add_test (Function)
# ph_add_test (Fundamental)
# ph_add_test (Integer)
# ph_add_test (Iterator)
# ph_add_test (Number)
# ph_add_test (Pointer)
# ph_add_test (Range)
# ph_add_test (Reference)
# ph_add_test (Signed)
# ph_add_test (Size)
# ph_add_test (Unsigned)




# add_test(NAME testName
#   COMMAND command [arg...]
#   [CONFIGURATIONS config1 [config2...]]
#   [WORKING_DIRECTORY dir]
# )

