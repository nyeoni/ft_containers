# Download googletest
include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.0
)

FetchContent_MakeAvailable(googletest)

# Add test files
# file 나중에 사용할 것
file(GLOB TEST_FILES *.cpp)
add_executable(ft_container_test type_traits_test.cpp vector_test.cpp)
target_compile_options(ft_container_test PRIVATE -std=c++98 -Wall -Wextra -Werror)

target_link_libraries(ft_container_test PRIVATE ft_container_lib gtest gmock gtest_main)