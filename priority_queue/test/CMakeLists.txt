FIND_PACKAGE(Threads REQUIRED)

set(REPO ~/CLionProjects/.repo)

include(CTest)
enable_testing()


include(${REPO}/DownloadProject/DownloadProject.cmake)
download_project(
        PROJ                googletest
        GIT_REPOSITORY      https://github.com/google/googletest.git
        GIT_TAG             master
        UPDATE_DISCONNECTED 1
)

add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR} EXCLUDE_FROM_ALL)
add_executable(runUnitTests unit_tests.cpp test_pqueue.cpp test_linkedlist.cpp)
target_link_libraries(runUnitTests gtest gmock ${CMAKE_THREAD_LIBS_INIT})
add_test(runUnitTests runUnitTests)