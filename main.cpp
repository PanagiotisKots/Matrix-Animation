#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>
#include <string.h>

#define WIDTH 190      // Width of console window
#define HEIGHT 63      // Height of console window
#define MAX_SPEED 15   // Maximum speed of raindrops
#define MIN_SPEED 5    // Minimum speed of raindrops
#define CHARACTERS "010101"

HANDLE console_handle;  // Console handle
COORD screen_size = { WIDTH, HEIGHT };  // Console screen size
CONSOLE_FONT_INFOEX font_info = { sizeof(CONSOLE_FONT_INFOEX) };

typedef struct {
    int x;
    int y;
    int speed;
} Raindrop;

void setupConsole() {
    console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleScreenBufferSize(console_handle, screen_size);
    SetConsoleActiveScreenBuffer(console_handle);

    // Setting console font size
    CONSOLE_FONT_INFOEX font_info;
    GetCurrentConsoleFontEx(console_handle, FALSE, &font_info);
    font_info.dwFontSize.X = 8;   // Width of each character
    font_info.dwFontSize.Y = 16;  // Height of each character
    SetCurrentConsoleFontEx(console_handle, FALSE, &font_info);

    // Set console window size
    SMALL_RECT window_size = { 0, 0, WIDTH - 1, HEIGHT - 1 };
    SetConsoleWindowInfo(console_handle, TRUE, &window_size);
}

void initRaindrop(Raindrop* drop) {
    drop->x = rand() % WIDTH;
    drop->y = -(rand() % HEIGHT);
    drop->speed = MIN_SPEED + rand() % (MAX_SPEED - MIN_SPEED + 1);
}

void fallRaindrop(Raindrop* drop) {
    drop->y += drop->speed;
    if (drop->y >= HEIGHT) {
        drop->y = -(rand() % HEIGHT);
        drop->speed = MIN_SPEED + rand() % (MAX_SPEED - MIN_SPEED + 1);
    }
}

int main() {
    srand((unsigned int)time(NULL));  // Seed random number generator
    setupConsole();  // Setup console window

    Raindrop raindrops[600];  // Array of raindrops (increased density)
    int i;

    // Initialize raindrops
    for (i = 0; i < 600; ++i) {  // Increase to 500 raindrops
        initRaindrop(&raindrops[i]);
    }

    // Main loop
    while (!_kbhit()) {  // Check for keyboard input
        // Render raindrops
        for (i = 0; i < 600; ++i) {  // Adjust loop for 500 raindrops
            Raindrop* drop = &raindrops[i];

            // Erase previous raindrop
            COORD erase_position = { drop->x, drop->y - drop->speed };
            erase_position.Y = (erase_position.Y + HEIGHT) % HEIGHT; // Wrap around if Y goes negative
            SetConsoleCursorPosition(console_handle, erase_position);
            printf(" ");

            // Update raindrop position
            fallRaindrop(drop);

            // Draw new raindrop
            COORD draw_position = { drop->x, drop->y };
            draw_position.Y = (draw_position.Y + HEIGHT) % HEIGHT; // Wrap around if Y goes negative
            SetConsoleCursorPosition(console_handle, draw_position);
            SetConsoleTextAttribute(console_handle, FOREGROUND_GREEN);
            printf("%c", CHARACTERS[rand() % strlen(CHARACTERS)]);
        }

        // Wait for a short time to control animation speed
        Sleep(20);  // Adjust delay for desired animation speed (faster for denser effect)
    }

    // Restore console text color before exiting
    SetConsoleTextAttribute(console_handle, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED);

    return 0;
}

