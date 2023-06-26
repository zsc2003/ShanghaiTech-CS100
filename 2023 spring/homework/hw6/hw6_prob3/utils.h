/**
 * @brief CLI for the game
 *
 * This part is derived from https://github.com/MarioTalevski/game-of-life and https://www.codeproject.com/Articles/16431/Add-color-to-your-std-cout
 *
 * @author Vincent Godin, Mario Talevski, Qingcheng Zhao
 *
 */
#ifndef GAMEOFLIFE_UTILS_H
#define GAMEOFLIFE_UTILS_H
#include <iostream>
#include <cstdlib>

#include <fstream>
#include <string>
#include <sstream>

// Move OS defines up here to be used in different places
#if defined(_WIN32) || defined(WIN32) || defined(__MINGW32__) || defined(__BORLANDC__)
#define OS_WIN
#include <windows.h> // Use for windows
// WINDOWS COLORS
inline std::ostream &COLOR_BLUE(std::ostream &s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    return s;
}

inline std::ostream &COLOR_RED(std::ostream &s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
                            FOREGROUND_RED | FOREGROUND_INTENSITY);
    return s;
}

inline std::ostream &COLOR_GREEN(std::ostream &s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
                            FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    return s;
}

inline std::ostream &COLOR_RESET(std::ostream &s)
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdout,
                            FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    return s;
}

#elif defined(linux) || defined(__CYGWIN__)
#include <unistd.h>
#define OS_LINUX

const std::string COLOR_RED = "\033[31m";
const std::string COLOR_GREEN = "\033[32m";
const std::string COLOR_BLUE = "\033[34m";
const std::string COLOR_RESET = "\033[0m";

#elif (defined(__APPLE__) || defined(__OSX__) || defined(__MACOS__)) && defined(__MACH__) // To ensure that we are running on a mondern version of macOS
#include <unistd.h>
#define OS_MAC

const std::string COLOR_RED = "\033[31m";
const std::string COLOR_GREEN = "\033[32m";
const std::string COLOR_BLUE = "\033[34m";
const std::string COLOR_RESET = "\033[0m";

#endif

void PrintWhite(const std::string &str) { std::cout << str; }
void PrintRed(const std::string &str) { std::cout << COLOR_RED << str << COLOR_RESET; }
void PrintGreen(const std::string &str) { std::cout << COLOR_GREEN << str << COLOR_RESET; }
void PrintBlue(const std::string &str) { std::cout << COLOR_BLUE << str << COLOR_RESET; }

enum class KeyCode
{
    // Controls:   1        2
    NONE,
    SAVE, // Save     S
    QUIT  // Esc     Esc
};

// Get keyboard without blocking
KeyCode GetKey()
{
    switch (std::cin.get())
    {
    case 's':
    case 'S':
        return KeyCode::SAVE;
    case 'q':
    case 'Q':
        return KeyCode::QUIT;
    default:
        return KeyCode::NONE;
    }
}

void clearScreen()
{
// Tested and working on Ubuntu and Cygwin
#if defined(OS_WIN)
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    DWORD count;
    DWORD cellCount;
    COORD homeCoords = {0, 0};

    if (hStdOut == INVALID_HANDLE_VALUE)
        return;

    /* Get the number of cells in the current buffer */
    GetConsoleScreenBufferInfo(hStdOut, &csbi);
    cellCount = csbi.dwSize.X * csbi.dwSize.Y;

    /* Fill the entire buffer with spaces */
    FillConsoleOutputCharacter(hStdOut, (TCHAR)' ', cellCount, homeCoords, &count);

    /* Fill the entire buffer with the current colors and attributes */
    FillConsoleOutputAttribute(hStdOut, csbi.wAttributes, cellCount, homeCoords, &count);

    SetConsoleCursorPosition(hStdOut, homeCoords);

#elif defined(OS_LINUX) || defined(OS_MAC)
    std::cout << "\033[2J;"
              << "\033[1;1H"; // Clears screen and moves cursor to home pos on POSIX systems
#endif
}

#endif // GAMEOFLIFE_UTILS_H