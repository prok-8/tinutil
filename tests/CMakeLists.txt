# SPDX-FileCopyrightText: 2024 Podpečan Rok <podpecanrok111@gmail.com>
# SPDX-License-Identifier: GPL-3.0-or-later

include(FetchContent)
FetchContent_Declare(googletest
	GIT_REPOSITORY https://github.com/google/googletest.git
	GIT_TAG b796f7d44681514f58a683a3a71ff17c94edb0c1) # V1.13.0
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)  # For Windows: Prevent overriding the parent project's compiler/linker settings.
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(tinutil_tests
	collection.cpp
	util.cpp)
target_link_libraries(tinutil_tests PRIVATE
	GTest::gtest_main
	tinutil)

if(GCC)
	target_compile_options(tinutil_tests PRIVATE -Wall)
elseif(MSVC)
	target_compile_options(tinutil_tests PRIVATE /Wall)
endif()

include(GoogleTest)
gtest_discover_tests(tinutil_tests)
