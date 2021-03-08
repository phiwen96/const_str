

file(GLOB_RECURSE HEADER_LIST "${const_str_SOURCE_DIR}/include/*.hpp")
file(GLOB SOURCE_LIST ${const_str_SOURCE_DIR}/src/*.cpp)

add_library (const_str
	${SOURCE_LIST}  ${HEADER_LIST} 
)

add_library (ph::const_str ALIAS const_str)

target_include_directories (const_str PUBLIC ${const_str_SOURCE_DIR}/include)

target_compile_features (const_str PUBLIC cxx_std_20)


target_include_directories(const_str PRIVATE
    $<BUILD_INTERFACE:${const_str_SOURCE_DIR}/include/const_str>
    $<INSTALL_INTERFACE:include/const_str>
)

target_include_directories(const_str PUBLIC
    $<BUILD_INTERFACE:${const_str_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)