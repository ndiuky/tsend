cmake_minimum_required(VERSION 3.30)
project(tsend LANGUAGES CXX)

set(root ${CMAKE_CURRENT_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME})

file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${root}/src/*.cpp")
file(GLOB_RECURSE headers CONFIGURE_DEPENDS "${root}/src/*.hpp")

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

target_sources(${PROJECT_NAME} PRIVATE ${sources})
target_sources(${PROJECT_NAME} PRIVATE
	FILE_SET cxx_headers TYPE HEADERS
	BASE_DIRS ${root}/src
	FILES ${headers}
)

target_precompile_headers(${PROJECT_NAME}
PRIVATE
	"$<$<COMPILE_LANGUAGE:CXX>:<cstdint$<ANGLE-R>>"
	"$<$<COMPILE_LANGUAGE:CXX>:<string$<ANGLE-R>>"
	"$<$<COMPILE_LANGUAGE:CXX>:<string_view$<ANGLE-R>>"
)

add_subdirectory(${root}/libs)
target_link_libraries(${PROJECT_NAME} PRIVATE tb::libs)
