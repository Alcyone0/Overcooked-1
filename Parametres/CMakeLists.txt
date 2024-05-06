cmake_minimum_required(VERSION 3.26)
project(Parametres C)

set(CMAKE_C_STANDARD 99)

add_executable(Parametres main.c)

target_link_libraries(Parametres -lmingw32 -lalleg44)