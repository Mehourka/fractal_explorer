# Fractol Project
Welcome to the Fractol project! This repository contains a fractal visualization and exploration program written in C, utilizing the MLX42 library for graphical rendering. The project includes both standard and bonus multi threaded implementations of various fractal types.

<p align="center"><img src="img/sample1.gif" width="400"></p>

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [License](#license)

## Introduction

Fractol is a graphical application that generates and displays fractal images. It supports multiple types of fractals, including Julia, Mandelbrot, and Burning Ship. The project is designed to be a learning tool for understanding fractal mathematics and graphical programming.

## Features

-  **Cpu Rendering**: Single and multi-threaded CPU rendering.
-  **Multiple Fractal Types**: Julia, Mandelbrot, and Burning Ship.
- ️ **Interactive Controls**: Zoom, pan, and adjust fractal parameters using keyboard and mouse.
-  **Customizable Colors**: Adjust the color scheme of the fractals.

## Installation

To build and run the Fractol project, follow these steps:

1. **Clone the repository**:
    ```sh
    git clone https://github.com/yourusername/fractol.git
    cd fractol
    ```

2. **Install dependencies**:
    Ensure you have the necessary libraries installed. For MLX42, follow the instructions in the [MLX42 repository](https://github.com/codam-coding-college/MLX42).

3. **Build the project**:
    ```sh
    make
    ```

## Usage

To run the Fractol program, use the following command:

```sh
./fractol [fractal_type]
```

### Keyboard Controls

| Key               | Action                        |
|-------------------|-------------------------------|
| `ESC`             | Exit the program              |
| `Arrow Keys`      | Pan the view                  |
| `Page Up/Down`    | Zoom in/out                   |
| `I/O`             | Increase/Decrease iterations  |
| `C`               | Change color scheme           |
| `J`               | Toggle Julia set control      |