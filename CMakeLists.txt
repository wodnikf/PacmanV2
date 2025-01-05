cmake_minimum_required(VERSION 3.29)
project(Pacman)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(Pacman
        src/GameWindow.cpp
        Headers/GameWindow.h
        Headers/Globals.h
        src/main.cpp
        src/Map.cpp
        Headers/Map.h
        src/Tile.cpp
        Headers/Tile.h
        src/Entity.cpp
        Headers/Entity.h
        src/Player.cpp
        Headers/Player.h
        src/Ghost.cpp
        Headers/Ghost.h
        src/Blinky.cpp
        Headers/Blinky.h
        src/Pathfinder.cpp
        Headers/Pathfinder.h
        src/Pinky.cpp
        Headers/Pinky.h
        src/Inky.cpp
        Headers/Inky.h
        src/Clyde.cpp
        Headers/Clyde.h
        src/Score.cpp
        Headers/Score.h
        src/MainWindow.cpp
        Headers/MainWindow.h
        src/StartPage.cpp
        Headers/StartPage.h
        src/EndPage.cpp
        Headers/EndPage.h
        src/DeathAnimationPage.cpp
        Headers/DeathAnimationPage.h
)
target_link_libraries(Pacman
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

