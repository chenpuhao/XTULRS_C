cmake_minimum_required(VERSION 3.31)
project(LRS C)

set(CMAKE_C_STANDARD 11)

# 添加 cJSON 源文件
set(CJSON_DIR ${CMAKE_SOURCE_DIR}/libs)
include_directories(${CJSON_DIR})
set(CJSON_SRC ${CJSON_DIR}/cJSON.c)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON) # Windows下导出所有符号
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

add_library(LRS SHARED main.c ${CJSON_SRC})