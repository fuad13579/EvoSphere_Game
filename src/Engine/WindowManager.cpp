#include "Engine/WindowManager.h"// for createWindow

#include <raylib.h>// for InitWindow

namespace EvoSphereGui
{
    bool createWindow(const WindowSettings& settings)//passes the window settings to the function and returns a boolean value indicating whether the window was successfully created or not.
    {
        SetConfigFlags(FLAG_WINDOW_RESIZABLE);// Allows the window to be resized by the user.

        InitWindow(
            settings.width,
            settings.height,
            settings.title
        );// Initializes the window with the specified width, height, and title.

        SetTargetFPS(settings.targetFps);// Sets the target frames per second for the window.

        return IsWindowReady();// Returns true if the window is ready to be used, false otherwise.
    }// Creates a window with the specified settings. Returns true if successful, false otherwise.

    bool shouldCloseWindow()
    {
        return WindowShouldClose();// Checks if the window should be closed (e.g., if the user has pressed the close button or the escape key). Returns true if it should, false otherwise.
    }

    void beginFrame()
    {
        BeginDrawing();// Begins the rendering frame, preparing the window for drawing.
        ClearBackground(Color{8, 12, 30, 255});// Clears the background with a specific color (in this case, a dark blue color).
    }

    void endFrame()
    {
        EndDrawing();// Ends the rendering frame, displaying the drawn content on the window.
    }

    void closeWindow()
    {
        if (IsWindowReady())
        {
            CloseWindow();// Closes the window and unloads the OpenGL context if the window is ready.OpenGL is a cross-language, cross-platform application programming interface (API) for rendering 2D and 3D vector graphics. It is typically used to interact with a graphics processing unit (GPU), to achieve hardware-accelerated rendering.
        }
    }
}