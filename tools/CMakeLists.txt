cmake_minimum_required(VERSION 2.6)
project(qore-qt-tools)

# where to look first for cmake modules, before ${CMAKE_ROOT}/Modules/ is checked
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules )

FIND_PACKAGE (Qore REQUIRED)
FIND_PACKAGE (Qt4 REQUIRED)

add_definitions (${QT_DEFINITIONS})
include_directories (${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} ${QT_INCLUDES} )

#add_subdirectory(rcc-qore)
add_subdirectory(uic-qore)

