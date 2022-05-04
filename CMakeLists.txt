cmake_minimum_required(VERSION 3.9)
 
PROJECT(PlusImageStreaming)

find_package(VTK REQUIRED)
include(${VTK_USE_FILE})

find_package(PlusLib REQUIRED)
include (${PlusLib_USE_FILE})

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5 COMPONENTS Widgets Core Gui Xml REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB UI_FILES *.ui)
file(GLOB QT_WRAP *.h)
file(GLOB CXX_FILES *.cxx)
file(GLOB CPP_FILES *.cpp)

# CMAKE_AUTOMOC in ON so the MOC headers will be automatically wrapped.
add_executable(PlusImageStreaming MACOSX_BUNDLE
${CXX_FILES} ${CPP_FILES} ${UISrcs} ${QT_WRAP})

target_link_libraries(PlusImageStreaming ${VTK_LIBRARIES}
Qt5::Widgets
vtkGUISupportQt
vtkPlusServer
PlusWidgets
vtkPlusCommon
vtkPlusCalibration)
