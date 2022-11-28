cmake_minimum_required(VERSION 3.23)
project(PasswordManager C)

set(CMAKE_C_STANDARD 99)

add_library(PasswordManager PasswordManager.c getline.c)
