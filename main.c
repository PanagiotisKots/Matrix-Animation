#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

// Width and height of the matrix
#define WIDTH 80
#define HEIGHT 25

// Defines the number of flips in Boolean Array 'switches'
#define FLIPS_PER_LINE 5

// Delay between two successive line prints in milliseconds
#define SLEEP_TIME 50

// Function to set text color
void setColor(int textColor, int bgColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}

// Function to set the console to full screen and configure dimensions
void setConsoleFullScreen() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD newSize;
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    // Get the current console screen buffer info
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    // Set the console window to full screen
    newSize.X = csbi.dwSize.X;
    newSize.Y = csbi.dwSize.Y;
    SetConsoleScreenBufferSize(hConsole, newSize);

    // Adjust the console window size
    SMALL_RECT windowSize = {
        0,
        0,
        (SHORT)(newSize.X - 1),
        (SHORT)(newSize.Y - 1)
    };
    SetConsoleWindowInfo(hConsole, TRUE, &windowSize);

    // Move the cursor to the top-left of the console window
    SetConsoleCursorPosition(hConsole, (COORD){0, 0});
}

int main() {
    int i = 0, x = 0;

    // Seed the random number generator with the current time
    srand(time(NULL));

    // Array to decide whether to print the character or not
    int switches[WIDTH] = {0};

    // Set of characters to print from
    const char ch[] = "1234567890qwertyuiopasdfghjkl"
                      "zxcvbnm,./';[]!@#$%^&*()-=_+";
    const int l = sizeof(ch) - 1;

    // Set console to green text on black background
    setColor(10, 0);

    // Set console to full screen
    setConsoleFullScreen();

    // Indefinite loop
    while (1) {
        // Loop over the width
        // Increment by 2 gives a better effect
        for (i = 0; i < WIDTH; i += 2) {
            // Print character if switches[i] is 1
            // Else print a blank character
            if (switches[i])
                printf("%c ", ch[rand() % l]);
            else
                printf("  ");
        }

        // Flip the defined amount of Boolean values after each line
        for (i = 0; i < FLIPS_PER_LINE; ++i) {
            x = rand() % WIDTH;
            switches[x] = !switches[x];
        }

        // New line
        printf("\n");

        // Sleep for the specified time
        Sleep(SLEEP_TIME);
    }

    return 0;
}

