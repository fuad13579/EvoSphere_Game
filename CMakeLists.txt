cmake_minimum_required(VERSION 3.16)//this is the minimum version of cmake that is required to build this project

project(EvoSphere VERSION 1.0 LANGUAGES CXX)//this sets the project name to EvoSphere, the version to 1.0, and specifies that the project uses C++ as the programming language

set(CMAKE_CXX_STANDARD 17)//this sets the C++ standard to C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)//this ensures that the specified C++ standard is required and will not fall back to an older standard
set(CMAKE_CXX_EXTENSIONS OFF)//this disables compiler-specific extensions, ensuring that the code adheres to the C++ standard
//we need these three because we want to use C++17 features and ensure that the code is portable across different compilers
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
)//this sets the source files for the EvoSphere project, including the main.cpp file and various other source files organized into different directories (Core, Console, Systems, data)

add_executable(EvoSphere ${EVOSPHERE_SOURCES})

target_include_directories(EvoSphere
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)//this sets the include directories for the EvoSphere target, specifying that the include directory is located in the project's source directory
//this if-else block checks if the compiler is MSVC (Microsoft Visual C++). If it is, it sets the compiler options to enable warning level 4 (/W4). If it is not MSVC, it sets the compiler options to enable all warnings (-Wall), extra warnings (-Wextra), and pedantic warnings (-Wpedantic). This ensures that the code is compiled with a high level of warning checks, which can help catch potential issues in the code.
if(MSVC)
    target_compile_options(EvoSphere PRIVATE /W4)
else()
    target_compile_options(EvoSphere PRIVATE -Wall -Wextra -Wpedantic)
endif()//this sets the link libraries for the EvoSphere target, specifying that the SDL2 and SDL2_image libraries should be linked. This ensures that the necessary libraries are included in the final executable.

