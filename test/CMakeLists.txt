# Set the destination, and source directory for the images
set(IMAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/images)
set(IMAGE_DESTINATION_DIR ${CMAKE_CURRENT_BINARY_DIR})

# Copy over the image files
file(COPY ${IMAGE_SOURCE_DIR} DESTINATION ${IMAGE_DESTINATION_DIR})

# Set up names for the tests (unnecessary, but I like doing this >:3)
set(KGF_DEPENDENCY_INJECTION_NAME dependency_injection)
set(KGF_DEPENDENCY_INJECTION_TEST dependency_injection_test)

set(KGF_BMP_1BIT_NAME bmp_1bit)
set(KGF_BMP_1BIT_TEST bmp_1bit_test)

set(KGF_BMP_4BIT_NAME bmp_4bit)
set(KGF_BMP_4BIT_TEST bmp_4bit_test)

set(KGF_BMP_16BIT_NAME bmp_16bit)
set(KGF_BMP_16BIT_TEST bmp_16bit_test)

set(KGF_BMP_24BIT_NAME bmp_24bit)
set(KGF_BMP_24BIT_TEST bmp_24bit_test)

set(KGF_BMP_32BIT_NAME bmp_32bit)
set(KGF_BMP_32BIT_TEST bmp_32bit_test)

set(KGF_BMP_RAW_DATA_NAME bmp_raw_data)
set(KGF_BMP_RAW_DATA_TEST bmp_raw_data_test)

# Add tests
add_executable(${KGF_DEPENDENCY_INJECTION_NAME} dependency_injection.cpp)
target_link_libraries(${KGF_DEPENDENCY_INJECTION_NAME} PRIVATE kimage::kimage)
target_compile_features(${KGF_DEPENDENCY_INJECTION_NAME} PUBLIC cxx_std_23)
add_test(NAME ${KGF_DEPENDENCY_INJECTION_TEST} COMMAND ${KGF_DEPENDENCY_INJECTION_NAME} WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(${KGF_BMP_1BIT_NAME} ${KGF_BMP_1BIT_NAME}.cpp)
target_link_libraries(${KGF_BMP_1BIT_NAME} PRIVATE kimage::kimage)
target_compile_features(${KGF_BMP_1BIT_NAME} PUBLIC cxx_std_23)
add_test(NAME ${KGF_BMP_1BIT_TEST} COMMAND ${KGF_BMP_1BIT_NAME} WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(${KGF_BMP_4BIT_NAME} ${KGF_BMP_4BIT_NAME}.cpp)
target_link_libraries(${KGF_BMP_4BIT_NAME} PRIVATE kimage::kimage)
target_compile_features(${KGF_BMP_4BIT_NAME} PUBLIC cxx_std_23)
add_test(NAME ${KGF_BMP_4BIT_TEST} COMMAND ${KGF_BMP_4BIT_NAME} WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(${KGF_BMP_16BIT_NAME} ${KGF_BMP_16BIT_NAME}.cpp)
target_link_libraries(${KGF_BMP_16BIT_NAME} PRIVATE kimage::kimage)
target_compile_features(${KGF_BMP_16BIT_NAME} PUBLIC cxx_std_23)
add_test(NAME ${KGF_BMP_16BIT_TEST} COMMAND ${KGF_BMP_16BIT_NAME} WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(${KGF_BMP_24BIT_NAME} ${KGF_BMP_24BIT_NAME}.cpp)
target_link_libraries(${KGF_BMP_24BIT_NAME} PRIVATE kimage::kimage)
target_compile_features(${KGF_BMP_24BIT_NAME} PUBLIC cxx_std_23)
add_test(NAME ${KGF_BMP_24BIT_TEST} COMMAND ${KGF_BMP_24BIT_NAME} WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(${KGF_BMP_32BIT_NAME} ${KGF_BMP_32BIT_NAME}.cpp)
target_link_libraries(${KGF_BMP_32BIT_NAME} PRIVATE kimage::kimage)
target_compile_features(${KGF_BMP_32BIT_NAME} PUBLIC cxx_std_23)
add_test(NAME ${KGF_BMP_32BIT_TEST} COMMAND ${KGF_BMP_32BIT_NAME} WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(${KGF_BMP_RAW_DATA_NAME} ${KGF_BMP_RAW_DATA_NAME}.cpp)
target_link_libraries(${KGF_BMP_RAW_DATA_NAME} PRIVATE kimage::kimage)
target_compile_features(${KGF_BMP_RAW_DATA_NAME} PUBLIC cxx_std_23)
add_test(NAME ${KGF_BMP_RAW_DATA_TEST} COMMAND ${KGF_BMP_RAW_DATA_NAME} WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
