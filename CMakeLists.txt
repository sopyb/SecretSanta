cmake_minimum_required(VERSION 3.23)
project(SecretSanta C)

set(CMAKE_C_STANDARD 99)
# build DataStore
add_subdirectory(DataStore)
# build WebServer
add_subdirectory(WebServer)

# add libraries built by subdirectories
link_libraries(DataStore)
#link_libraries(WebServer)

# build SecretSanta as an executable including the libraries
add_executable(SecretSanta main.c)

