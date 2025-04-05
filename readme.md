# Simple SFML Shape Editor with ImGui

This project is a basic interactive application built using the SFML (Simple and Fast Multimedia Library) for rendering graphics and ImGui (Dear ImGui) for creating a user interface. It allows you to load, visualize, and manipulate simple geometric shapes (circles and rectangles) through a graphical menu.

## Features

* **Loading Entities from Configuration File:** The application loads shape definitions (type, name, position, speed, color, and dimensions) from a `config.txt` file.
* **Shape Rendering:** Displays the loaded shapes on a window.
* **ImGui Interface:** Provides an interactive menu to:
    * Select individual shapes from a dropdown list.
    * Toggle the visibility of the selected shape.
    * Change the color of the selected shape using a color picker.
    * Adjust the horizontal and vertical speed of the selected shape using sliders.
    * Modify the radius of a selected circle using a slider.
    * Modify the width and height of a selected rectangle using sliders.
* **Basic Animation:** Shapes move within the window boundaries and bounce off the edges.

## Dependencies

Before building and running this project, ensure you have the following libraries installed and linked in your development environment:

* **SFML (>= 2.5):** For window creation, event handling, and drawing shapes.
* **ImGui:** For creating the interactive user interface.
* **SFML-ImGui:** A bridge library that integrates ImGui with SFML.

You will need to configure your build system (e.g., CMake, Makefiles, or your IDE's project settings) to include the necessary headers and link against these libraries.

## Building and Running

1.  **Clone the repository (if applicable) or copy the source code files.** Ensure that the provided C++ code (`main.cpp`) is in your project directory.
2.  **Create a `config.txt` file** in the same directory as your executable. This file will define the shapes to be loaded. See the "Configuration File Format" section below for details.
3.  **Configure your build system:** Link against the SFML libraries (graphics, window, system), the ImGui library, and the SFML-ImGui library. Include the necessary header directories for these libraries.
4.  **Build the project:** Compile the `main.cpp` file.
5.  **Run the executable:** The application window should open, displaying the loaded shapes and the ImGui menu.

## Configuration File Format (`config.txt`)

The `config.txt` file is used to define the initial state of the application, including the window size and the entities (shapes) to be loaded. Each entry in the file is identified by a tag.

### Window Configuration

To set the initial window dimensions, use the `Window` tag followed by the width and height (both integers):
Window 800 600

### Font Configuration (Currently Not Used)

There is a section in the code for loading font information, but it is not currently used in the application's functionality. The format is:
Font <font_file_name> <font_size> <colorR> <colorG> <colorB>

