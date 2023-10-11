#Specifiying min. req. cmake-version.
cmake_minimum_required(VERSION 3.27.2)

#Setting project name(space)
project(pacMan VERSION 0.1)

#Make sure the version nr is included in full name. 
#Set version above in project and use pacManConfig.h.in
#to give access to version nr for the src code.
configure_file(pacManConfig.h.in pacManConfig.h)

#Add executable files of which the project is built on
add_executable(pacMan ${CMAKE_SOURCE_DIR}/src/main.cpp
                      ${CMAKE_SOURCE_DIR}/src/Game.cpp
                      ${CMAKE_SOURCE_DIR}/src/State.cpp
                      ${CMAKE_SOURCE_DIR}/src/GameState.cpp
                      ${CMAKE_SOURCE_DIR}/src/MainMenuState.cpp
                      ${CMAKE_SOURCE_DIR}/src/Button.cpp
                      ${CMAKE_SOURCE_DIR}/src/Packie.cpp
                      ${CMAKE_SOURCE_DIR}/src/Map.cpp
                      ${CMAKE_SOURCE_DIR}/src/Tile.cpp
                      ${CMAKE_SOURCE_DIR}/src/Pellet.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_BINARY_DIR})

#Specifying settings for compilation and linking
set_property(TARGET pacMan PROPERTY CXX_STANDARD 17)

target_include_directories(pacMan PRIVATE 
    /Users/antonlarsson/SFML/include
    ${CMAKE_SOURCE_DIR}/include
)

#Speicfy which libraries should ne included
target_link_libraries(pacMan
    /Users/antonlarsson/SFML/lib/libsfml-graphics.dylib
    /Users/antonlarsson/SFML/lib/libsfml-window.dylib
    /Users/antonlarsson/SFML/lib/libsfml-system.dylib
    /Users/antonlarsson/SFML/lib/libsfml-audio.dylib
    /Users/antonlarsson/SFML/lib/libsfml-network.dylib)

#Should also work, but getting some error so linking all
#SFML-libraries manually
#set(CMAKE_PREFIX_PATH "/Users/antonlarsson/SFML")
#set(SFML_DIR "/Users/antonlarsson/SFML/")
#find_package(SFML 3.0 COMPONENTS graphics window system audio network REQUIRED)
#target_link_libraries(pacMan sfml-graphics sfml-window sfml-system)

#include(InstallRequiredSystemLibraries)
# set(CPACK_RESOURCE_FILE_LICENSE "{CMAKE_SOURCE_DIR/License.txt}")
# set(CPACK_PACKAGE_VERSION_MAJOR "${}")