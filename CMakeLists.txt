cmake_minimum_required(VERSION 3.23)
project(SecretSanta C)

set(CMAKE_C_STANDARD 99)
# add subdirectories
add_subdirectory(DataStore)
add_subdirectory(PasswordManager)
add_subdirectory(Interaction/Admin)
add_subdirectory(Interaction/User)

# add libraries built by subdirectories
link_libraries(DataStore)
link_libraries(PasswordManager)
link_libraries(AdminInteraction)
link_libraries(UserInteraction)

# build SecretSanta as an executable including the libraries
add_executable(SecretSanta main.c colors.h Interaction/GeneralInteraction.c Interaction/GeneralInteraction.h)