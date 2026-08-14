#include "Engine/Application.h"

#include <raylib.h>

#include "Engine/WindowManager.h"

namespace EvoSphereGui
{
    int runApplication()
    {
        WindowSettings settings;// Default window settings. WindowsSettings is a struct that contains the width, height, title, and target FPS for the window.

        if (!createWindow(settings))
        {
            return 1;// Returns 1 if the window could not be created.
        }

        while (!shouldCloseWindow())// Checks if the window should be closed (e.g., if the user has pressed the close button or the escape key). Returns true if it should, false otherwise.
        {
            beginFrame();// Begins the rendering frame, preparing the window for drawing.

            DrawText(
                "EVOSPHERE",
                500,
                280,
                40,
                RAYWHITE
            );// Draws the text "EVOSPHERE" at position (500, 280) with font size 40 and color RAYWHITE.

            DrawText(
                "GUI Foundation",
                520,
                340,
                24,
                SKYBLUE
            );// Draws the text "GUI Foundation" at position (520, 340) with font size 24 and color SKYBLUE.

            endFrame();// Ends the rendering frame, displaying the drawn content on the window.
        }

        closeWindow();// Closes the window and unloads the OpenGL context.

        return 0;
    }
}