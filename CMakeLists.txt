cmake_minimum_required(VERSION 3.0.0)
project(SoliCurses VERSION 0.1.0)

include(CTest)
enable_testing()

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

add_executable(SoliCurses main.cpp)
target_link_libraries(SoliCurses ${CURSES_LIBRARIES})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
