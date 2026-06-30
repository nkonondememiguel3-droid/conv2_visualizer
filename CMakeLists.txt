cmake_minimum_required(VERSION 3.20)
project(conv2_visualizer)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(SDL3 REQUIRED CONFIG)

# add the nuklear library
add_subdirectory(externals)

add_executable(
	${PROJECT_NAME}
	main.c
	config.c
	widget.c
)

target_link_libraries(
	${PROJECT_NAME} PUBLIC
	nuklear_lib
	m
)
target_include_directories(
	${PROJECT_NAME} PRIVATE
	include/
)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)

