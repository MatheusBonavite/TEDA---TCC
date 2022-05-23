cmake_minimum_required (VERSION 3.5)

project (TEDA_Algorithm)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")

set (source_dir "${PROJECT_SOURCE_DIR}/src/")

set(math_functions_dir "${PROJECT_SOURCE_DIR}/Functions/MathFunctions")

set(db_functions_dir "${PROJECT_SOURCE_DIR}/Functions/DbFunctions")

set(sqlite3_dir "${PROJECT_SOURCE_DIR}/sqlite")

file(GLOB source_files "${source_dir}/*.c")

file(GLOB math_function_files ${math_functions_dir}/*.c)

file(GLOB db_function_files ${db_functions_dir}/*.c)

file(GLOB sqlite3_files ${sqlite3_dir}/sqlite3.c)

add_executable(TEDA_Algorithm ${source_files} ${sqlite3_files} ${db_function_files} ${math_function_files})