cmake_minimum_required(VERSION 3.5)
set(CMAKE_CXX_STANDARD 11)
add_subdirectory(libs)
project(EspDspTest)
set(SOURCES
	"signal.cpp")
add_executable(testdsp ${SOURCES})
target_link_libraries(testdsp PUBLIC thirdparty)
