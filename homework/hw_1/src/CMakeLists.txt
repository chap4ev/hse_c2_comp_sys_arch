# set minimum cmake version
cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

# project name and language
project(hw1 LANGUAGES CXX)

set(BUILD_DIR "${CMAKE_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${BUILD_DIR}/../bin")

set(BINARY_DIR "${CMAKE_BINARY_DIR}")

# Source files list
set(SOURCE_FILES
    # Headers
    rnd.h
    pair.h
    cycleEncryption.h
    charReplaceEncryption.h
    intReplaceEncryption.h
    encryptedText.h
    container.h

    # Sources
    cycleEncryption.cpp
    charReplaceEncryption.cpp
    intReplaceEncryption.cpp
    encryptedText.cpp
    container.cpp
    main.cpp
)

add_executable(hw1 ${SOURCE_FILES})
