cmake_minimum_required(VERSION 3.27.2)
project(pacMan)

add_executable(pacMan ${CMAKE_SOURCE_DIR}/src/main.cpp
                      ${CMAKE_SOURCE_DIR}/src/game.cpp)

set_property(TARGET pacMan PROPERTY CXX_STANDARD 17)

include_directories(/Users/antonlarsson/SFML/include
                    ${CMAKE_SOURCE_DIR}/include )

#set(CMAKE_PREFIX_PATH "/Users/antonlarsson/SFML")
#set(SFML_DIR "/Users/antonlarsson/SFML/")
#find_package(SFML 3.0 COMPONENTS graphics window system REQUIRED)

target_link_libraries(pacMan
    /Users/antonlarsson/SFML/lib/libsfml-graphics.dylib
    /Users/antonlarsson/SFML/lib/libsfml-window.dylib
    /Users/antonlarsson/SFML/lib/libsfml-system.dylib
    # Add any other SFML libraries your project uses here
)


#target_link_libraries(pacMan sfml-graphics sfml-window sfml-system)
