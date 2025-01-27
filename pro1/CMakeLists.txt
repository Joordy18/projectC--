cmake_minimum_required(VERSION 3.30)
project(TicTacToc CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "C:/Qt/6.8.1/mingw_64")

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()


add_executable(TicTacToc main.cpp)

set_target_properties(TicTacToc PROPERTIES
        WIN32_EXECUTABLE ON
        MACOSX_BUNDLE ON
)

find_program(WINDEPLOYQT_EXECUTABLE windeployqt HINTS "${QT_BIN_DIR}")

add_custom_command(TARGET TicTacToc
        POST_BUILD
        COMMAND "${WINDEPLOYQT_EXECUTABLE}" "$<TARGET_FILE:TicTacToc>"
)

target_link_libraries(TicTacToc PRIVATE Qt6::Widgets Qt6::Core)