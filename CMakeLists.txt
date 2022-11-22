cmake_minimum_required(VERSION 3.23)
project(SecretSanta C)

set(CMAKE_C_STANDARD 99)

add_executable(SecretSanta main.c WebServer/WebServer.c WebServer/WebServer.h)
