#include <iostream>
#include <Windows.h>

const int screenWidth = 80;
const int screenHeight = 25;

CHAR_INFO screenBuffer[screenWidth * screenHeight];

void clearScreenBuffer() {
    for (int i = 0; i < screenWidth * screenHeight; ++i) {
        screenBuffer[i].Char.AsciiChar = ' ';
        screenBuffer[i].Attributes = FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE;
    }
}

void drawPixel(int x, int y, char character, WORD attributes) {
    if (x >= 0 && x < screenWidth && y >= 0 && y < screenHeight) {
        int index = y * screenWidth + x;
        screenBuffer[index].Char.AsciiChar = character;
        screenBuffer[index].Attributes = attributes;
    }
}

void render() {
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD bufferSize = { static_cast<SHORT>(screenWidth), static_cast<SHORT>(screenHeight) };
    COORD bufferCoord = { 0, 0 };
    SMALL_RECT writeRegion = { 0, 0, static_cast<SHORT>(screenWidth - 1), static_cast<SHORT>(screenHeight - 1) };

    WriteConsoleOutput(console, screenBuffer, bufferSize, bufferCoord, &writeRegion);
}

int main() {
    clearScreenBuffer();

    drawPixel(50, 5, 'H', FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    drawPixel(50, 6, 'E', FOREGROUND_RED | FOREGROUND_INTENSITY);
    drawPixel(50, 7, 'L', FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    drawPixel(50, 8, 'L', FOREGROUND_RED | FOREGROUND_INTENSITY);
    drawPixel(50, 9, 'O', FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    drawPixel(50, 10, 'W', FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    drawPixel(50, 11, 'O', FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    drawPixel(50, 12, 'R', FOREGROUND_RED | FOREGROUND_INTENSITY);
    drawPixel(50, 13, 'L', FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    drawPixel(50, 14, 'D', FOREGROUND_RED | FOREGROUND_INTENSITY);

    render();

    // Sleep to see the result (you might want to handle events in a real application)
    Sleep(2000);

    std::cin.get();
}
