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
        GameWindow.cpp
        GameWindow.h
        Globals.h
        main.cpp
        Map.cpp
        Map.h
        Tile.cpp
        Tile.h
        Entity.cpp
        Entity.h
        Player.cpp
        Player.h
        Ghost.cpp
        Ghost.h
        Blinky.cpp
        Blinky.h
        Pathfinder.cpp
        Pathfinder.h
        Pinky.cpp
        Pinky.h
        Inky.cpp
        Inky.h
        Clyde.cpp
        Clyde.h
        Score.cpp
        Score.h
        MainWindow.cpp
        MainWindow.h
        StartPage.cpp
        StartPage.h
        EndPage.cpp
        EndPage.h
        DeathAnimationPage.cpp
        DeathAnimationPage.h
)
target_link_libraries(Pacman
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

