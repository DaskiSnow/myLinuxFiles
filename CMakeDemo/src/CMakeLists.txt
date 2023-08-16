aux_source_directory (. SRC_LIST)

include_directories (../include)

add_executable (main ${SRC_LIST})

add_compile_options(-std=c++11 -Wall -g)

set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)


