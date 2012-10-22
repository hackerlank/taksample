cmake_minimum_required(VERSION 2.6)
project(taksample)

macro(set_tak_location)
    add_subdirectory("${ARGN}" "${CMAKE_CURRENT_BINARY_DIR}/tak")
    include_directories("${ARGN}" "${CMAKE_CURRENT_BINARY_DIR}/tak")
endmacro(set_tak_location)



# TODO tak headers should not expose these stuff, when
# it's solved, remove this
if(MSVC)
	include_directories(${CMAKE_SOURCE_DIR}/tak/external/vstudio2k10/SFML-2.0-rc/include)
	include_directories(${CMAKE_SOURCE_DIR}/tak/external/vstudio2k10/glew-1.7.0/include)
	include_directories(${CMAKE_SOURCE_DIR}/tak/external/vstudio2k10/bullet-2.80/include)
	include_directories(${CMAKE_SOURCE_DIR}/tak/external/vstudio2k10/DevIL-SDK-x86-1.7.8/include)
	include_directories(C:/boost/boost_1_51_0)
	link_directories(${CMAKE_SOURCE_DIR}/tak/external/vstudio2k10/glew-1.7.0/lib)
	link_directories(${CMAKE_SOURCE_DIR}/tak/external/vstudio2k10/SFML-2.0-rc/lib)
	link_directories(${CMAKE_SOURCE_DIR}/tak/external/vstudio2k10/DevIL-SDK-x86-1.7.8/lib)
	link_directories(${CMAKE_SOURCE_DIR}/tak/external/vstudio2k10/bullet-2.80/lib)
	link_directories(C:/boost/boost_1_51_0/lib)
	link_directories(C:/boost/boost_1_51_0/stage/lib)
else(MSVC)
	find_package (Bullet REQUIRED)
	include_directories(${BULLET_INCLUDE_DIRS})
endif(MSVC)

set_tak_location("tak")

FILE(GLOB all_headers *.h)
source_group(headers FILES ${all_headers})
FILE(GLOB all_sources *.cpp)
source_group(sources FILES ${all_sources})

#avoid ZERO_CHECK project generated on visual studio
set(CMAKE_SUPPRESS_REGENERATION TRUE)

add_executable(taksample ${all_sources} ${all_headers})
target_link_libraries(taksample tak)
