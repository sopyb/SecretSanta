cmake_minimum_required(VERSION 3.24)
project(Secret_Santa C)

set(CMAKE_C_STANDARD 17)

add_executable(Secret_Santa main.c modules/admin_interaction/admin_interaction.c modules/general_operations/general_operations.c modules/file_operations/file_operations.c modules/user_interaction/user_interaction.c)
