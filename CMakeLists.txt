cmake_minimum_required(VERSION 3.25.2)
project(raytrace)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS true)

add_custom_target(check)
add_executable(${CMAKE_PROJECT_NAME})

if(NOT DIRTY)
    # Add some warnings
    target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE
        -Werror
        -Weverything

        # Now remove the stuff we do not want warnings for
        -Wno-c++98-compat
        -Wno-c++98-compat-extra-semi
        -Wno-pre-c++20-compat-pedantic
        -Wno-gnu-anonymous-struct # Technically UB, but too tasty
        -Wno-nested-anon-types    # Technically UB, but too tasty
        -Wno-weak-vtables         # Weak vtables are fine I guess?
        -Wno-padded               # This is not even a problem?
    )
endif()

target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
    fmt
)

add_subdirectory(src)
