#Specifiying min. req. cmake-version.
cmake_minimum_required(VERSION 3.27.2)

#Setting project name(space)
project(pacMan VERSION 0.1)

#Make sure the version nr is included in full name. 
#Set version above in project and use pacManConfig.h.in
#to give access to version nr for the src code.
configure_file(pacManConfig.h.in pacManConfig.h)

set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

#Add executable files of which the project is built on
add_executable(${PROJECT_NAME} ${SRC_DIR}/main.cpp
                    ${SRC_DIR}/Game.cpp
                    ${SRC_DIR}/State.cpp
                    ${SRC_DIR}/GameState.cpp
                    ${SRC_DIR}/MainMenuState.cpp
                    ${SRC_DIR}/Button.cpp
                    ${SRC_DIR}/AnimationButton.cpp
                    ${SRC_DIR}/PacMan.cpp
                    ${SRC_DIR}/Map.cpp
                    ${SRC_DIR}/Tile.cpp
                    ${SRC_DIR}/Pellet.cpp
                    ${SRC_DIR}/Ghost.cpp
                    ${SRC_DIR}/Pathfinding.cpp
                    ${SRC_DIR}/PathfindingStrategy.cpp
                    ${SRC_DIR}/HighScoreState.cpp
                    ${SRC_DIR}/Blinky.cpp
                    ${SRC_DIR}/Inky.cpp
                    ${SRC_DIR}/Pinky.cpp
                    ${SRC_DIR}/Clyde.cpp
                    ${SRC_DIR}/Energizer.cpp
                    ${SRC_DIR}/SettingState.cpp
                    ${SRC_DIR}/SliderButton.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR} )

#Specifying settings for compilation and linking
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

target_include_directories(${PROJECT_NAME} PRIVATE 
    /Users/antonlarsson/SFML/include
    ${INCLUDE_DIR}
)

#Speicfy which libraries should ne included
target_link_libraries(pacMan
    /Users/antonlarsson/SFML/lib/libsfml-graphics.dylib
    /Users/antonlarsson/SFML/lib/libsfml-window.dylib
    /Users/antonlarsson/SFML/lib/libsfml-system.dylib
    /Users/antonlarsson/SFML/lib/libsfml-audio.dylib
    /Users/antonlarsson/SFML/lib/libsfml-network.dylib)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
install(FILES "${PROJECT_BINARY_DIR}/pacManConfig.h" DESTINATION include) 
