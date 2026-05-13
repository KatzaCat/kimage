# Set the destination, and source directory for the images
set(IMAGE_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/images)
set(IMAGE_DESTINATION_DIR ${CMAKE_CURRENT_BINARY_DIR})

# Copy over the image files
file(COPY ${IMAGE_SOURCE_DIR} DESTINATION ${IMAGE_DESTINATION_DIR})

if(KI_EXAMPLE_RUN STREQUAL bmp_sdl)
        set(EXAMPLE_NAME bmp_sdl)

        add_executable(${EXAMPLE_NAME} ${EXAMPLE_NAME}.cpp)
        target_link_libraries(${EXAMPLE_NAME} PRIVATE kimage::kimage)
        target_compile_features(${EXAMPLE_NAME} PUBLIC cxx_std_23)

        include(FetchContent)

        FetchContent_Declare(
                SDL
                GIT_REPOSITORY https://github.com/libsdl-org/SDL
                GIT_TAG        release-3.4.x
        )

        FetchContent_MakeAvailable(SDL)

        target_link_libraries(${EXAMPLE_NAME} PRIVATE SDL3::SDL3)
endif()
