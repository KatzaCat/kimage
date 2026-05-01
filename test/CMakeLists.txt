# Set the destination, and source directory for the images
set(IMAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/images)
set(IMAGE_DESTINATION_DIR ${CMAKE_CURRENT_BINARY_DIR})

# Copy over the image files
file(COPY ${IMAGE_SOURCE_DIR} DESTINATION ${IMAGE_DESTINATION_DIR})

# Set up names for the tests (unnecessary, but I like doing this >:3)
set(KGF_DEPENDENCY_INJECTION_NAME dependency_injection)
set(KGF_DEPENDENCY_INJECTION_TEST dependency_injection_test)

set(KGF_BMP_NAME bmp)
set(KGF_BMP_TEST bmp_test)

# Add tests
add_executable(${KGF_DEPENDENCY_INJECTION_NAME} dependency_injection.cpp)
target_link_libraries(${KGF_DEPENDENCY_INJECTION_NAME} PRIVATE kimage::kimage)
target_compile_features(${KGF_DEPENDENCY_INJECTION_NAME} PUBLIC cxx_std_23)
add_test(NAME ${KGF_DEPENDENCY_INJECTION_TEST} COMMAND ${KGF_DEPENDENCY_INJECTION_NAME} WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(${KGF_BMP_NAME} bmp.cpp)
target_link_libraries(${KGF_BMP_NAME} PRIVATE kimage::kimage)
target_compile_features(${KGF_BMP_NAME} PUBLIC cxx_std_23)
add_test(NAME ${KGF_BMP_TEST} COMMAND ${KGF_BMP_NAME} WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
