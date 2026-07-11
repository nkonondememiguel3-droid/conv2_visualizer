cmake_minimum_required(VERSION 3.20)
project(conv2_visualizer)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

if(MSVC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /W4 /EHsc")
    # /O2 is automatically added for Release builds, but if forced:
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} /O2")
else()
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
    set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O2")
endif()
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -O2")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(CMAKE_HOST_WIN32)
	list(APPEND CMAKE_PREFIX_PATH "C:/softwares/SDL3")
endif(CMAKE_HOST_WIN32)

find_package(SDL3 REQUIRED CONFIG)

# add the memory library
add_subdirectory(memory)

# add the nuklear library
add_subdirectory(externals)

add_executable(
	${PROJECT_NAME}
	main.c
	config.c
	widget.c
    app.c
)

target_link_libraries(
	${PROJECT_NAME} PUBLIC
	conv2_lib
	ds_arena
	nuklear_lib
)

if(NOT WIN32)
    target_link_libraries(
        ${PROJECT_NAME} PRIVATE
        m
    )
endif()

target_include_directories(
	${PROJECT_NAME} PRIVATE
	externals/nuklear
)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)

add_library(
	conv2_lib
    tensor.c
    include/operation.h
    operation.c
)
target_include_directories(
	conv2_lib PUBLIC
	include/
)
target_link_libraries(
	conv2_lib PUBLIC
	ds_arena
)
