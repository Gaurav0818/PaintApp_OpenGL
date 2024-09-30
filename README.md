# Paint App

## Overview

Paint App is a simple drawing application built using OpenGL and GLFW. It provides various drawing tools such as pencil, eraser, line, rectangle, circle, and bucket fill. Users can select different colors and brush sizes to create their artwork.

## Features

- **Drawing Tools**: 
  - Pencil Tool
  - Eraser Tool
  - Line Tool
  - Rectangle Tool
  - Circle Tool
  - Bucket Tool

- **Color Selection**: Choose from a variety of colors.
- **Brush Size Adjustment**: Increase or decrease the brush size.
- **Undo Functionality**: Undo the last action.
- **FPS Display**: Shows the current frames per second.

## Dependencies

- **GLFW**: For window creation and input handling.
- **GLEW**: For managing OpenGL extensions.

## Building the Project

To build the project, run the `GenerateProject.bat` script. This will generate the Visual Studio 2022 project files using Premake.

```bat
call vendor\premake\premake5.exe vs2022
PAUSE
```

## Running the Application

After building the project, run the executable to start the Paint App. Use the following controls to interact with the application:

### Tool Selection 
you can use both GUI and Keyboard for tool selection 

- **Pencil Tool**: Press `P`
- **Eraser Tool**: Press `Backspace`
- **Line Tool**: Press `L`
- **Rectangle Tool**: Press `K`
- **Bucket Tool**: Press `B`
- **Circle Tool**: Press `O`

### Color Selection
you can use both GUI and Keyboard for color selection
- **White**: Press `1`
- **Black**: Press `2`
- **Red**: Press `3`
- **Green**: Press `4`
- **Blue**: Press `5`
- **Yellow**: Press `6`
- **Cyan**: Press `7`
- **Magenta**: Press `8`
- **Gray**: Press `9`
- **Orange**: Press `0`
- **Purple**: Press `Q`
- **Pink**: Press `W`
- **Brown**: Press `E`

### Brush Size Adjustment

- **Increase Brush Size**: Press `Arrow Up`
- **Decrease Brush Size**: Press `Arrow Down`

### Undo

- **Undo Last Action**: Press `Ctrl + Z`

## License

This project is licensed under the MIT License. See the `LICENSE` file for more details.
