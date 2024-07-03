#include "CommandController.hpp"
#include "ScoreBoard_v2.hpp"

int main() {
  ScoreBoard scoreBoard("Ma Long", "Fan Zhendong");

  CommandController cmdCtl{"Enter command:", FrameHeight * 2 + 2};

  while (true) {
    auto cmd = cmdCtl.receiveCommand();
    if (cmd == "q" || cmd == "quit")
      break;
    if (cmd == "l+")
      scoreBoard.leftIncPoints();
    else if (cmd == "l-")
      scoreBoard.leftDecPoints();
    else if (cmd == "r+")
      scoreBoard.rightIncPoints();
    else if (cmd == "r-")
      scoreBoard.rightDecPoints();
    else if (cmd == "lg+")
      scoreBoard.leftIncGames();
    else if (cmd == "lg-")
      scoreBoard.leftDecGames();
    else if (cmd == "rg+")
      scoreBoard.rightIncGames();
    else if (cmd == "rg-")
      scoreBoard.rightDecGames();
  }

  return 0;
}