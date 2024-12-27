cmake_minimum_required(VERSION 3.26)
project(delta)

set(CMAKE_CXX_STANDARD 23)
set(LIBRARY_NAME delta)

find_package(Eigen3 3.3 REQUIRED NO_MODULE)

include_directories(delta)

add_library(${LIBRARY_NAME} STATIC delta/Expression.h
        delta/Expression.cpp
        delta/ExpressionHierarchy.cpp
        delta/ExpressionHierarchy.h
        delta/NumTraits.cpp
        delta/NumTraits.h
        delta/deltaUtils.cpp
        delta/deltaUtils.h
        delta/FullyConnected.cpp
        delta/FullyConnected.h
        delta/Activation.cpp
        delta/Activation.h
        delta/DomainError.cpp
        delta/DomainError.h
        delta/DotProductSelfAttention.h
)

target_include_directories(delta PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/delta)

target_link_libraries(delta PRIVATE Eigen3::Eigen)

add_subdirectory(tests)
