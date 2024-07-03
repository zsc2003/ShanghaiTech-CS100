#ifndef PACMAN_UTILS_H
#define PACMAN_UTILS_H

#if defined(__MINGW64_VERSION_MAJOR) && __MINGW64_VERSION_MAJOR < 7
#error Your MinGW version is too old. Go to winlibs.com to install the latest MinGW-w64.
#endif

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

// Test whether the keyboard has been stroke. Returns 1 if there is a keyboard
// stroke, or 0 if there is none.
int kbhit(void) {
  struct termios oldt;
  tcgetattr(STDIN_FILENO, &oldt);
  struct termios newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);

  int oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  int ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if (ch != EOF) {
    ungetc(ch, stdin);
    return 1;
  }
  return 0;
}

// Get a character from input without showing it.
int getch(void) {
  struct termios oldt;
  tcgetattr(STDIN_FILENO, &oldt);
  struct termios newt = oldt;
  newt.c_lflag &= ~ICANON;
  newt.c_lflag &= ~ECHO;
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  int ch = getchar();
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  return ch;
}
#endif // _WIN32

void hide_cursor(void) { printf("\033[?25l"); }

void show_cursor(void) { printf("\033[?25h"); }

void disable_input_echo(void) {
#ifdef _WIN32
  HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
  DWORD mode = 0;
  GetConsoleMode(hStdin, &mode);
  SetConsoleMode(hStdin, mode & ~ENABLE_ECHO_INPUT);
#else
  struct termios t;
  tcgetattr(STDIN_FILENO, &t);
  t.c_lflag &= ~ECHO;
  tcsetattr(STDIN_FILENO, TCSANOW, &t);
#endif // _WIN32
}

void enable_input_echo(void) {
#ifdef _WIN32
  HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
  DWORD mode = 0;
  GetConsoleMode(hStdin, &mode);
  SetConsoleMode(hStdin, mode | ENABLE_ECHO_INPUT);
#else
  struct termios t;
  tcgetattr(STDIN_FILENO, &t);
  t.c_lflag |= ECHO;
  tcsetattr(STDIN_FILENO, TCSANOW, &t);
#endif // _WIN32
}

bool stdout_is_terminal(void) {
#ifdef _WIN32
  return GetFileType(GetStdHandle(STD_OUTPUT_HANDLE)) == FILE_TYPE_CHAR;
#else
  return isatty(STDOUT_FILENO);
#endif // _WIN32
}

void prepare_game(void) {
  if (!stdout_is_terminal()) {
    fputs("pacman must be run in a terminal.", stderr);
    exit(EXIT_FAILURE);
  }

#ifdef _WIN32
  HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
  if (hStd == INVALID_HANDLE_VALUE) {
    exit(EXIT_FAILURE);
  }
  DWORD dwMode = 0;
  if (!GetConsoleMode(hStd, &dwMode)) {
    exit(EXIT_FAILURE);
  }
  dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
  if (!SetConsoleMode(hStd, dwMode)) {
    fputs("Can't enable virtual terminal processing.", stderr);
    exit(EXIT_FAILURE);
  }
#endif // _WIN32

  hide_cursor();
  atexit(show_cursor);

  disable_input_echo();
  setbuf(stdout, NULL);
}

void move_cursor(int row, int col) {
  printf("%c[%d;%df", 0x1B, row + 1, col + 1);
}

void clear_screen(void) { printf("\033[2J\033[1;1f"); }

void sleep_ms(long long t) {
#ifdef _WIN32
  Sleep(t);
#else
  usleep(t * 1000);
#endif // _WIN32
}

#define ANSI_ESCAPE_RED "31"
#define ANSI_ESCAPE_GREEN "32"
#define ANSI_ESCAPE_YELLOW "33"
#define ANSI_ESCAPE_BLUE "34"
#define ANSI_ESCAPE_BRIGHT_YELLOW "93"
#define ANSI_ESCAPE_BRIGHT_BLUE "94"
#define ANSI_ESCAPE_NORMAL "0"

#define SET_COLOR(color) "\033[" ANSI_ESCAPE_##color "m"

#define COLORED(color, text) (SET_COLOR(color) text SET_COLOR(NORMAL))

#define RED_TEXT(text) COLORED(RED, text)
#define GREEN_TEXT(text) COLORED(GREEN, text)
#define YELLOW_TEXT(text) COLORED(YELLOW, text)
#define BLUE_TEXT(text) COLORED(BLUE, text)
#define BRIGHT_YELLOW_TEXT(text) COLORED(BRIGHT_YELLOW, text)
#define BRIGHT_BLUE_TEXT(text) COLORED(BRIGHT_BLUE, text)

void to_next_line(FILE *stream) {
  int ch = fgetc(stream);
  while (ch != EOF && ch != '\n')
    ch = fgetc(stream);
}

void read_line(FILE *stream, char *line) {
  int ch = fgetc(stream);
  while (ch != EOF && ch != '\n') {
    *line++ = (char)ch;
    ch = fgetc(stream);
  }
  *line = '\0';
}

#endif // PACMAN_UTILS_H
