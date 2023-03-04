set(sources
    ${CMAKE_CURRENT_LIST_DIR}/main.cpp
)

target_sources(${CMAKE_PROJECT_NAME} PRIVATE ${sources})

add_custom_target(clang-tidy
    clang-tidy -p ${CMAKE_BINARY_DIR} --header-filter=.* ${sources}
)

add_custom_target(cppcheck ALL
    cppcheck --quiet --enable=all --suppress=missingIncludeSystem --suppress=unmatchedSuppression --inconclusive
    --cppcheck-build-dir=${CMAKE_CURRENT_BINARY_DIR} --error-exitcode=1 --inline-suppr ${CMAKE_CURRENT_LIST_DIR}
)

add_dependencies(check cppcheck) # Do not add clang-tidy here, since it takes some time to run
