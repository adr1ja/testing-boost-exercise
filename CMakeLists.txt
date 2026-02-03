cmake_minimum_required(VERSION "3.12")
project("sidemade")

list (APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

find_package(Eigen3 3.2 REQUIRED)
find_package(yaml-cpp 0.6.0 REQUIRED)
find_package(Boost 1.71 REQUIRED unit_test_framework)

include(CTest)

file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS src/*.cpp)
list(REMOVE_ITEM SRC_FILES "${PROJECT_SOURCE_DIR}/src/main.cpp")

add_executable(sidemade ${SRC_FILES} src/main.cpp)
target_link_libraries(sidemade PRIVATE Eigen3::Eigen yaml-cpp)
set_property(TARGET sidemade PROPERTY CXX_STANDARD 11)

file(GLOB_RECURSE TEST_FILES CONFIGURE_DEPENDS tests/*.cpp)

list(REMOVE_ITEM TEST_FILES "${PROJECT_SOURCE_DIR}/tests/test_matrixIO.cpp")

add_executable(testsidemade ${TEST_FILES} ${SRC_FILES})
target_include_directories(testsidemade PRIVATE ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(testsidemade PRIVATE Boost::unit_test_framework Eigen3::Eigen yaml-cpp)

add_test(NAME "MatrixSolverTests" COMMAND testsidemade --run_test=MatrixSolverTests/*)
add_test(NAME "ConfigurationTests" COMMAND testsidemade --run_test=ConfigurationTests/* WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}/tests)

add_executable(my_io_test tests/test_matrixIO.cpp src/matrixIO.cpp src/Configuration.cpp)
target_include_directories(my_io_test PRIVATE ${PROJECT_SOURCE_DIR}/src)
target_link_libraries(my_io_test PRIVATE Boost::unit_test_framework Eigen3::Eigen yaml-cpp)
add_test(NAME "MyMatrixIOTest" COMMAND my_io_test)