# Create ft_containers_lib interface
add_library(ft_container_lib STATIC src/main.cpp)
# Include containers hpp files
target_include_directories(ft_container_lib PUBLIC include)
# Set ft_containers_lib compile option
set_target_properties(ft_container_lib PROPERTIES INTERFACE_LINK_LIBRARIES -Wall -Wextra -Werror -std=c++98 -g3)