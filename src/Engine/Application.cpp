#include "Engine/Application.h"

#include <raylib.h>

#include "Engine/WindowManager.h"

namespace EvoSphereGui
{
    int runApplication()
    {
        WindowSettings settings;

        if (!createWindow(settings))
        {
            return 1;
        }

        while (!shouldCloseWindow())
        {
            beginFrame();

            DrawText(
                "EVOSPHERE",
                500,
                280,
                40,
                RAYWHITE
            );

            DrawText(
                "GUI Foundation",
                520,
                340,
                24,
                SKYBLUE
            );

            endFrame();
        }

        closeWindow();

        return 0;
    }
}