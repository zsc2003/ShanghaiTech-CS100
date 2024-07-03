#ifndef SCOREBOARD_UTILS_HPP
#define SCOREBOARD_UTILS_HPP

#if defined(__MINGW64_VERSION_MAJOR) && __MINGW64_VERSION_MAJOR < 7
#error Your MinGW version is too old. Go to winlibs.com to install the latest MinGW-w64.
#endif

#include <iostream>

#ifdef _WIN32
#include <conio.h>
#include <windows.h>
#else
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#endif // _WIN32

struct PrinterGuard {
  PrinterGuard() {
    if (numOfInstances++ == 0) {
      hide_cursor();
      disable_input_echo();
    }
  }
  ~PrinterGuard() {
    if (--numOfInstances == 0) {
      show_cursor();
      enable_input_echo();
    }
  }

private:
  static int numOfInstances;

  static void hide_cursor() { std::cout << "\033[?25l" << std::flush; }

  static void show_cursor() { std::cout << "\033[?25h" << std::flush; }

  static void disable_input_echo() {
#ifdef _WIN32
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode & ~ENABLE_ECHO_INPUT);
#else
    termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
#endif // _WIN32
  }

  static void enable_input_echo() {
#ifdef _WIN32
    HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
    DWORD mode = 0;
    GetConsoleMode(hStdin, &mode);
    SetConsoleMode(hStdin, mode | ENABLE_ECHO_INPUT);
#else
    termios t;
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
#endif // _WIN32
  }
};

int PrinterGuard::numOfInstances = 0;

void move_cursor(int row, int col) {
  std::cout << "\033[" << row + 1 << ';' << col + 1 << 'f' << std::flush;
}

void clear_screen() {
#ifdef _WIN32
  std::system("cls");
#else
  std::cout << "\033[2J\033[1;1f" << std::flush;
#endif // _WIN32
}

void clear_to_eol() { std::cout << "\033[0K" << std::flush; }

void sleep_ms(long long t) {
#ifdef _WIN32
  Sleep(t);
#else
  usleep(t * 1000);
#endif // _WIN32
}

enum class TextColor { Normal, Red, Blue };

std::ostream &operator<<(std::ostream &os, TextColor color) {
  static constexpr const char *Escapes[] = {"\033[0m", "\033[31m", "\033[34m"};
  os << Escapes[static_cast<int>(color)] << std::flush;
  return os;
}

struct ColorGuard {
  ColorGuard(TextColor color) { std::cout << color << std::flush; }
  ~ColorGuard() { std::cout << TextColor::Normal << std::flush; }
};

namespace detail {

struct Starter {
  Starter() {
    if (!stdout_is_terminal()) {
      std::cerr << "ScoreBoard must be run in a terminal.\n";
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
      std::cerr << "Can't enable virtual terminal processing.\n";
      exit(EXIT_FAILURE);
    }
#endif // _WIN32
  }

  static const Starter starter;

private:
  static bool stdout_is_terminal() {
#ifdef _WIN32
    return GetFileType(GetStdHandle(STD_OUTPUT_HANDLE)) == FILE_TYPE_CHAR;
#else
    return isatty(STDOUT_FILENO);
#endif // _WIN32
  }
};

const Starter Starter::starter{};

} // namespace detail

#endif // SCOREBOARD_UTILS_HPP