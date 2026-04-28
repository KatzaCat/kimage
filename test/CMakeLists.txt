# Set up names for the tests (unnecessary, but I like doing this >:3)
set(KGF_DEPENDENCY_INJECTION_NAME dependency_injection)
set(KGF_DEPENDENCY_INJECTION_TEST dependency_injection_test)

# Add tests
add_executable(${KGF_DEPENDENCY_INJECTION_NAME} dependency_injection.cpp)
target_link_libraries(${KGF_DEPENDENCY_INJECTION_NAME} PRIVATE kimage::kimage)
target_compile_features(${KGF_DEPENDENCY_INJECTION_NAME} PUBLIC cxx_std_23)
add_test(${KGF_DEPENDENCY_INJECTION_TEST} ${KGF_DEPENDENCY_INJECTION_NAME})
