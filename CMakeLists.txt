cmake_minimum_required(VERSION 2.8)
project(color-map)
find_package(OpenCV REQUIRED)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -O0")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(SOURCE_FILES main.cpp
				 colorMap.cpp
				 projectTests.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})
	
