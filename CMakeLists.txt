cmake_minimum_required(VERSION 3.15)
project(MathematicalModeling)

set(PROJECT_EXE ${PROJECT_NAME})
set(PROJECT_LIB "${PROJECT_NAME}_lib")

set(lib_src
        util/tuple_visit.hpp
        util/print.hpp
        lib/Fraction.h
        lib/Fraction.cpp
        week00/CrossRiver.h
        week00/CrossRiver.cpp
        week01/SheepDistribution.h
        week01/SheepDistribution.cpp
        )

set(main_src
        main.cpp
        )

add_library(${PROJECT_LIB} ${lib_src})

add_executable(${PROJECT_EXE} ${main_src})

set_target_properties(${PROJECT_EXE} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )

set_target_properties(${PROJECT_LIB} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )

target_include_directories(${PROJECT_EXE} PRIVATE .)
target_include_directories(${PROJECT_LIB} PRIVATE .)


if (MSVC)
    target_compile_options(${PROJECT_EXE} PRIVATE /W3)
    target_compile_options(${PROJECT_LIB} PRIVATE /W3)
else ()
    target_compile_options(${PROJECT_EXE} PRIVATE -Wall -Wextra -pedantic)
    target_compile_options(${PROJECT_LIB} PRIVATE -Wall -Wextra -pedantic)
endif ()

# This will add the include path, respectively.
target_link_libraries(${PROJECT_EXE} ${PROJECT_LIB})