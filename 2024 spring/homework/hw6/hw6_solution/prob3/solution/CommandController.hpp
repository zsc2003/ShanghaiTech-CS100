#ifndef COMMANDCONTROLLER_HPP
#define COMMANDCONTROLLER_HPP

#include "utils.hpp"

class CommandController {
  int mPromptRow;
  int mPromptLength;

public:
  CommandController(std::string_view prompt, int promptRow)
      : mPromptRow{promptRow}, mPromptLength(prompt.size()) {
    move_cursor(promptRow, 0);
    std::cout << prompt << std::flush;
  }
  std::string receiveCommand() const {
    move_cursor(mPromptRow, mPromptLength + 1);
    std::string line;
    std::getline(std::cin, line);
    move_cursor(mPromptRow, mPromptLength + 1);
    clear_to_eol();
    return line;
  }
  ~CommandController() {
    move_cursor(mPromptRow, 0);
    clear_to_eol();
  }
};

#endif // COMMANDCONTROLLER_HPP