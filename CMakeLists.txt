cmake_minimum_required(VERSION 4.2.0)

project(kimage LANGUAGES CXX VERSION 5.12.26)

# Have CMake export compile commands
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add the library
add_library(${PROJECT_NAME} STATIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src/kimage.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/imageprocessor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/imageprocessor/bmp.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/tools/int_type.cpp
)
# Create the alias
add_library(kimage::kimage ALIAS ${PROJECT_NAME})
# Get rid of the "lib" prefix
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")

# Make the include directory public
target_include_directories(${PROJECT_NAME}
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)
# Target C++ standard 23
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_23)
# If using GNU, taeget stdc++exp
if (MINGW AND CMAKE_CXX_COMPILER_ID STREQUAL GNU)
        target_link_libraries(${PROJECT_NAME} stdc++exp)
endif()

# Examples
if(KI_EXAMPLE)
        message("Building Examples")
        add_subdirectory(example)
endif()

# Tests
if(KI_TEST)
        message("Building Tests")
        enable_testing()
        add_subdirectory(test)
endif()
