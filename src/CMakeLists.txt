

file(GLOB_RECURSE HEADER_LIST "${const_str_SOURCE_DIR}/include/*.hpp")
file(GLOB SOURCE_LIST ${const_str_SOURCE_DIR}/src/*.cpp)

add_library (const_str
	${SOURCE_LIST}  ${HEADER_LIST} 
)

target_include_directories (const_str PUBLIC ${const_str_SOURCE_DIR}/include)

target_compile_features (const_str PUBLIC cxx_std_20)
