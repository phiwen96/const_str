file(GLOB HEADER_LIST CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/../include/const_str/*.hpp")


foreach(file ${HEADER_LIST})
    source_group (TREE ${CMAKE_CURRENT_LIST_DIR}/../include/const_str
        PREFIX "include"               
        FILES  ${file}
    )
endforeach()


file(GLOB SOURCE_LIST CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/*.cpp")

foreach(file ${SOURCE_LIST})
    source_group (TREE ${CMAKE_CURRENT_LIST_DIR}
        PREFIX "src"               
        FILES  ${file}
    )
endforeach()



add_library (const_str
	${SOURCE_LIST}  ${HEADER_LIST} 
	# ALIAS const_str::const_str
)

set_target_properties (
	const_str 

	PROPERTIES
  		CXX_STANDARD 20
  		CXX_STANDARD_REQUIRED ON
  		CXX_EXTENSIONS OFF

	FOLDER
		""
)
# Make override a feature requirement only if available
target_compile_features (const_str 
	PUBLIC
  		$<$<COMPILE_FEATURES:cxx_override>:cxx_override>
)
# Define the foo_OVERRIDE symbol so it provides the
# override keyword if available or empty otherwise
target_compile_definitions (const_str 
	# PUBLIC
  	# 	$<$<COMPILE_FEATURES:cxx_override>:-Dconst_str_OVERRIDE=override>
  	# 	$<$<NOT:$<COMPILE_FEATURES:cxx_override>>:-Dconst_str_OVERRIDE>

	PRIVATE 
		"$<$<CONFIG:DEBUG>:DEBUG> $<$<CONFIG:RELEASE>:RELEASE>"
)


# target_compile_definitions (lib PRIVATE "$<$<CONFIG:DEBUG>:DEBUG> $<$<CONFIG:RELEASE>:RELEASE>")


# target_sources (ph_concepts PRIVATE in/platform.hpp)

set_target_properties (const_str PROPERTIES CXX_STANDARD 20)
target_compile_features (const_str PUBLIC cxx_std_20)

ph_precompile (TARGET const_str PRIVATE PCH ${std_pch})

# add_library (const_str ALIAS const_str::const_str)
# target_link_libraries (lib PRIVATE    ${Vulkan_LIBRARIES} glfw)
# target_link_libraries (lib PRIVATE const_str)

target_include_directories (const_str PUBLIC ${CMAKE_PROJECT_SOURCE_DIR}/include ph_concepts)
target_link_libraries (const_str PUBLIC ph_concepts)

# target_include_directories (ph_concepts PRIVATE ${Boost_INCLUDE_DIRS})

target_compile_features (const_str PUBLIC cxx_std_20)

# target_compile_options(ph_concepts PUBLIC "-ast-dump  -fsyntax-only")


target_include_directories(const_str PRIVATE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../include/const_str>
    $<INSTALL_INTERFACE:include/const_str>
)

target_include_directories(const_str PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}/../include>
    $<INSTALL_INTERFACE:include>
)

if (PROJECT_NAME STREQUAL PROJECT_NAME)
    # set_target_properties (lib PROPERTIES FOLDER "lib/")
else ()
    set_target_properties (const_str PROPERTIES FOLDER "dependencies/const_str")
endif ()



# IDE()