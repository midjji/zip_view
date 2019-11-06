cmake_minimum_required(VERSION 3.5)
project(mzip)
include(cmake/macros.cmake)

BuildConfig()
WarningConfig()
OptimizationConfig()

include_directories(../../../)

add_executable(test_zip test_mzip.cpp mzip_view.h )
set_property(TARGET test_zip PROPERTY CXX_STANDARD 17)














