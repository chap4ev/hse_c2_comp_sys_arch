# set minimum cmake version
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# project name and language
project(hw2 LANGUAGES CXX)

set(BUILD_DIR "${CMAKE_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BUILD_DIR}/../bin/")

# Source files list
set(SOURCE_FILES
        # Headers
        src/util/rnd.h
        src/util/pair.h
        src/encryption/cycle_encryption.h
        src/encryption/char_replace_encryption.h
        src/encryption/int_replace_encryption.h
        src/encryption/encrypted_text.h
        src/container/container.h

        # Sources
        src/encryption/cycle_encryption.cpp
        src/encryption/char_replace_encryption.cpp
        src/encryption/int_replace_encryption.cpp
        src/encryption/encrypted_text.cpp
        src/container/container.cpp
        src/main.cpp
        )

add_executable(hw2 ${SOURCE_FILES})
