function genCMakeTxt(path, data) {
    var name = data["name"]
    var mode = data["mode"];
    var cmake = ""

    cmake += "cmake_minimum_required(VERSION 3.12)\n\n"

    cmake += "project(\""+ name +"\")\n\n"

    cmake += "set(CMAKE_INCLUDE_CURRENT_DIR ON)\n\n"
    cmake += "set(CMAKE_AUTOMOC ON)\n"
    cmake += "set(CMAKE_AUTORCC ON)\n"
    cmake += "set(CMAKE_CXX_STANDARD 17)\n"
    cmake += "set(CMAKE_CXX_STANDARD_REQUIRED ON)\n\n"

    cmake += "find_package(Qt5 COMPONENTS Widgets REQUIRED)\n"
    cmake += "set (sources Widget.cc)\n"


    if (mode === "App")
    {
        cmake += "#add_library(Widget SHARED ${sources}) # dynamic lib (*.so)\n"
        cmake += "#add_library(Widget STATIC ${sources}) # static lib (*.a)\n"
        cmake += "#add_library(Widget MODULE ${sources}) # module lib (*.so)\n"

    }
    else if (mode === "StaticLib")
    {
        cmake += "add_library(Widget STATIC ${sources})\n"
//    cmake += "add_library(Widget STATIC ${sources})\n"
        cmake += "target_link_libraries(Widget Qt5::Widgets)\n\n"

        cmake += "install(TARGETS ${PROJECT_NAME} DESTINATION lib)\n"
        cmake += "install(FILES Widget.h DESTINATION include)\n"
    }
    else
    {
        cmake += "add_library(Widget STATIC ${sources})\n"
//    cmake += "add_library(Widget STATIC ${sources})\n"
        cmake += "target_link_libraries(Widget Qt5::Widgets)\n\n"

        cmake += "install(TARGETS ${PROJECT_NAME} DESTINATION lib)\n"
        cmake += "install(FILES Widget.h DESTINATION include)\n"

    }

    return cmake;
}
