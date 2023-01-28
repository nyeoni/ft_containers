# ref https://github.com/google/googletest/tree/main/googletest

# Project version
cmake_minimum_required(VERSION 3.5)
cmake_policy(SET CMP0048 NEW)

# set the project name and version
project(ft_container VERSION 0.1)

# 라이브러리 파일은 빌드 디렉토리 안에 lib 폴더에 출력.
# CMAKE_BINARY_DIR -> build
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 실행 파일은 빌드 디렉토리 안에 bin 폴더에 출력.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# test directory 추가
add_subdirectory(stl)
add_subdirectory(test)