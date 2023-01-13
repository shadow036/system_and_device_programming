cmake_minimum_required(VERSION 3.5)

project(alternate_channel LANGUAGES C)

add_executable(alternate_channel main.c)

install(TARGETS alternate_channel
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
