cmake_minimum_required(VERSION 3.15)
FIND_PACKAGE(Threads REQUIRED)
project(runUnitTests)
set(REPO ~/CLionProjects/.repo)

include(CTest)
enable_testing()


include(${REPO}/DownloadProject/DownloadProject.cmake)
download_project(
        PROJ googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG master
        UPDATE_DISCONNECTED 1
)


add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)

execute_process(
        COMMAND bash "-c" "if [ ! -d '${CMAKE_SOURCE_DIR}/test/gtest' ]; then
        python2 ${googletest_SOURCE_DIR}/googletest/scripts/fuse_gtest_files.py ${CMAKE_SOURCE_DIR}/test
        fi"
)
add_executable(runUnitTests unit_tests.cpp test_obst.cpp)
target_link_libraries(runUnitTests gtest gmock ${CMAKE_THREAD_LIBS_INIT})
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS -Wpedantic -Wall -Wextra
        )
add_test(${CMAKE_PROJECT_NAME} runUnitTests)
