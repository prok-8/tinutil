# SPDX-FileCopyrightText: 2024 Podpečan Rok <podpecanrok111@gmail.com>
# SPDX-License-Identifier: GPL-3.0-or-later

cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project(tinutil VERSION 1.0.0.0 LANGUAGES CXX)

option(TINUTIL_BUILD_TESTS "Build the tinutil test programs" OFF)

add_subdirectory(tinutil)

if(TINUTIL_BUILD_TESTS)
    add_subdirectory(tests)
endif()
