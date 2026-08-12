#pragma once

namespace EvoSphereGui
{
    struct WindowSettings
    {
        int width = 1280;// Default window width in pixels.
        int height = 720;// Default window height in pixels.
        const char* title = "EvoSphere";// Default window title.
        int targetFps = 60;// Default target frames per second.
    };

    bool createWindow(const WindowSettings& settings);// Creates a window with the specified settings. Returns true if successful, false otherwise.
    bool shouldCloseWindow();// Checks if the window should be closed. Returns true if it should, false otherwise.
    void beginFrame();// Begins the rendering frame.
    void endFrame();// Ends the rendering frame.
    void closeWindow();// Closes the window.

}