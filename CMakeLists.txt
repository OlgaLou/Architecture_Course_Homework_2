project(test_solve LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(test_motion_and_rotation main.cpp exeptions.h motion.h motion_tests.h rotation.h rotation_tests.h)

target_link_libraries(test_motion_and_rotation  
  PRIVATE 
    gtest
    gmock
    gtest_main)

enable_testing()

include(FetchContent)
FetchContent_Declare(gtest gmock
  QUIET
  URL https://github.com/google/googletest/archive/release-1.10.0.tar.gz
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(gtest)