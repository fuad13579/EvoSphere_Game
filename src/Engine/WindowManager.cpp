#include "Engine/WindowManager.h"// for createWindow

#include <raylib.h>// for InitWindow

namespace EvoSphereGui
{
    bool createWindow(const WindowSettings& settings)
    {
        SetConfigFlags(FLAG_WINDOW_RESIZABLE);// Allows the window to be resized by the user.

        InitWindow(
            settings.width,
            settings.height,
            settings.title
        );// Initializes the window with the specified width, height, and title.

        SetTargetFPS(settings.targetFps);// Sets the target frames per second for the window.

        return IsWindowReady();
    }// Creates a window with the specified settings. Returns true if successful, false otherwise.

    bool shouldCloseWindow()
    {
        return WindowShouldClose();
    }

    void beginFrame()
    {
        BeginDrawing();
        ClearBackground(Color{8, 12, 30, 255});
    }

    void endFrame()
    {
        EndDrawing();
    }

    void closeWindow()
    {
        if (IsWindowReady())
        {
            CloseWindow();
        }
    }
}