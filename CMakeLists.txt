set(PROJECT_NAME "DICOMeter")

cmake_minimum_required(VERSION 3.24)
project(${PROJECT_NAME})
set(CMAKE_CXX_STANDARD 20)
set(INSTALLATION_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/bin/${CMAKE_BUILD_TYPE}")

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:__cplusplus") # may be required as a workaround in case DCMTK complains about missing C++ 11 features on Visual Studio's compiler

find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui)
find_package(DCMTK REQUIRED)

add_subdirectory(DICOMeter)