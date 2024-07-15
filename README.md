# Matrix-Animation In C






This project simulates the iconic "Matrix" movie raindrop effect in a console environment using C and Windows API.

## Overview

This program generates a matrix-like raindrop animation where characters fall vertically down the console window, reminiscent of scenes from "The Matrix" movie.

## Features

- Random generation of characters resembling the green digital raindrops.
- Smooth animation using console manipulation functions.
- Adjustable animation parameters for speed and density of raindrops.

## Requirements

- Windows operating system (due to the use of Windows API functions).
- C compiler that supports Windows API (e.g., MinGW for Windows).

## Installation

1. Clone the repository:

   git clone https://github.com/PanagiotisKots/Matrix-Animation

    Compile the program using a C compiler (e.g., GCC):


gcc main.c -o matrix_raindrop

Run the executable:


    ./matrix_raindrop

Usage

    The animation will start automatically upon running the executable.
    Press any key to exit the program.

Customization

    You can customize the animation by adjusting constants in the source code (matrix_raindrop.c):
        WIDTH and HEIGHT: Adjust the console window size.
        MAX_SPEED and MIN_SPEED: Control the speed range of raindrops.
        CHARACTERS: Set the characters used to represent raindrops.
