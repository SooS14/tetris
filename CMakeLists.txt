cmake_minimum_required(VERSION 3.7)
include( CMakeParseArguments )

project(TETRIS LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)

function(ADD_PRG)
	set(options OPTIONAL)
	set(oneValueArgs TARGET )
	set(multiValueArgs SOURCES)
	cmake_parse_arguments(ADD_PRG "${options}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN} )

	add_executable(${ADD_PRG_TARGET} "")
	target_sources(${ADD_PRG_TARGET} PUBLIC ${ADD_PRG_SOURCES})

    target_include_directories(${ADD_PRG_TARGET} PUBLIC /usr/include/SDL2)
    target_link_libraries(${ADD_PRG_TARGET} PUBLIC SDL2 SDL2main SDL2_image SDL2_mixer SDL2_ttf)

#   if (${CMAKE_SYSTEM_NAME} MATCHES Linux)
#   	target_include_directories(${ADD_PRG_TARGET} PUBLIC /usr/include/SDL2)
#   	target_link_libraries(${ADD_PRG_TARGET} PUBLIC SDL2 SDL2main)
#	else()
#		target_link_libraries(${ADD_PRG_TARGET} PUBLIC SDL2::SDL2 SDL2::SDL2main)
#	endif()


	target_compile_definitions(${ADD_PRG_TARGET} PUBLIC _USE_MATH_DEFINES)
endfunction()

include_directories(inc)

ADD_PRG(TARGET TETRIS SOURCES src/main.cpp src/game.cpp src/playground.cpp
            src/tetrimino.cpp src/square.cpp src/check.cpp)



#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/bmp_models/start.bmp
#	DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)
