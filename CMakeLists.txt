cmake_minimum_required(VERSION 3.5)
project(qrco)

set(CMAKE_CXX_STANDARD 20)

# Add the bcrypt library
add_subdirectory(Bcrypt.cpp-master)

# Define the executable target
add_executable(qrco main.cpp qrcode.cpp camera.cpp users.cpp)

# Link the bcrypt library to the executable target
target_link_libraries(qrco bcrypt)

set(OpenCV_DIR "C:/opencv/")
find_package(OpenCV REQUIRED)

target_link_libraries(qrco ${OpenCV_LIBS})

file(GLOB OPENCV_DLL_FILES C:/opencv/x64/mingw/bin/*.*dll)
file(COPY ${OPENCV_DLL_FILES} DESTINATION ${CMAKE_BINARY_DIR})
