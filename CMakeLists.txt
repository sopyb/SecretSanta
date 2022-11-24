cmake_minimum_required(VERSION 3.23)
project(SecretSanta C)

set(CMAKE_C_STANDARD 99)
# add subdirectories
add_subdirectory(DataStore)
add_subdirectory(PasswordManager)
add_subdirectory(UserInterface)

# add libraries built by subdirectories
link_libraries(DataStore)
link_libraries(PasswordManager)
link_libraries(UserInterface)

# build SecretSanta as an executable including the libraries
add_executable(SecretSanta main.c colors.h)

