cmake_minimum_required(VERSION 3.23)
project(ConfigManager C)

set(CMAKE_C_STANDARD 99)

add_library(DataStore DataStore.c)
set_target_properties(DataStore PROPERTIES PUBLIC_HEADER DataStore.h)
# export the target
install(TARGETS DataStore
        LIBRARY DESTINATION lib
        PUBLIC_HEADER DESTINATION include)