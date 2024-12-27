find_package(Catch2 3 REQUIRED)
find_package(Eigen3 3 REQUIRED NO_MODULE)
include_directories(${CMAKE_SOURCE_DIR}/delta/delta)

add_executable(tests activationTest.cpp
        derivatives.cpp
)

#add_executable(tests
#        maintests.cpp)

target_link_libraries(tests PRIVATE delta Catch2::Catch2WithMain Eigen3::Eigen)
#target_link_libraries(tests PRIVATE delta Eigen3::Eigen)
