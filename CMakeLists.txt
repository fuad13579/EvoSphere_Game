cmake_minimum_required(VERSION 3.16)#this is the minimum version of CMake required to build this project

project(EvoSphere VERSION 1.0 LANGUAGES CXX)#this is the name of the project and the version

set(CMAKE_CXX_STANDARD 17)#this is the C++ standard to use
set(CMAKE_CXX_STANDARD_REQUIRED ON)#this is to make sure that the C++ standard is used
set(CMAKE_CXX_EXTENSIONS OFF)#this is to make sure that the C++ standard is used without any compiler-specific extensions

#these three are used to set the output directories for the build files

set(EVOSPHERE_SOURCES
    src/main.cpp

    src/Core/Board.cpp
    src/Core/EventCard.cpp
    src/Core/Evoran.cpp
    src/Core/Game.cpp
    src/Core/Guardian.cpp
    src/Core/Player.cpp
    src/Core/Tile.cpp
    src/Core/TurnManager.cpp

    src/Console/ConsoleGame.cpp
    src/Console/ConsoleInput.cpp
    src/Console/ConsoleRenderer.cpp

    src/Systems/BattleSystem.cpp
    src/Systems/CaptureSystem.cpp
    src/Systems/EventSystem.cpp
    src/Systems/EvolutionSystem.cpp
    src/Systems/MovementSystem.cpp
    src/Systems/TeleportSystem.cpp

    src/data/BoardData.cpp
    src/data/EventDatabase.cpp
    src/data/EvoranDatabase.cpp
)#this is the list of source files to compile

add_executable(EvoSphere ${EVOSPHERE_SOURCES})#this is the command to create an executable target called EvoSphere from the source files listed in EVOSPHERE_SOURCES

target_include_directories(EvoSphere
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)#this is the command to add the include directories for the target EvoSphere. The PRIVATE keyword means that the include directories are only used for compiling the target and not for any targets that link to it.

#this if-else statement is used to add compiler options for the target EvoSphere based on the compiler being used. If the compiler is MSVC (Microsoft Visual C++), it adds the /W4 option to enable warning level 4. If the compiler is not MSVC, it adds the -Wall, -Wextra, and -Wpedantic options to enable all warnings, extra warnings, and pedantic warnings respectively.
if(MSVC)
    target_compile_options(EvoSphere PRIVATE /W4)
else()
    target_compile_options(EvoSphere PRIVATE -Wall -Wextra -Wpedantic)
endif()#this is the command to add compiler options for the target EvoSphere. The PRIVATE keyword means that the compiler options are only used for compiling the target and not for any targets that link to it. The if statement checks if the compiler is MSVC (Microsoft Visual C++) and adds the appropriate compiler options for that compiler. If the compiler is not MSVC, it adds the appropriate compiler options for other compilers.
