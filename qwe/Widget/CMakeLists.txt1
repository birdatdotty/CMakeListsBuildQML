cmake_minimum_required(VERSION 3.12)

project(Widget)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets REQUIRED)

set (sources Widget.cc)
#add_library(Widget SHARED ${sources}) # dynamic lib (*.so)
#add_library(Widget STATIC ${sources}) # static lib (*.a)
#add_library(Widget MODULE ${sources}) # module lib (*.so)
add_library(Widget STATIC ${sources})
target_link_libraries(Widget Qt5::Widgets)

#install(TARGETS ${PROJECT_NAME} DESTINATION lib)
#  DESTINATION ${CMAKE_INSTALL_PREFIX}/lib
#  PERMISSIONS OWNER_EXECUTE)
install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES Widget.h DESTINATION include)
