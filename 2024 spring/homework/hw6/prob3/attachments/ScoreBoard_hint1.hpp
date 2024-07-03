#ifndef SCOREBOARD_HPP
#define SCOREBOARD_HPP

#include "ArtDigits.hpp"
#include "utils.hpp"

inline constexpr auto MSPerTick = 50;

namespace detail {

template <std::size_t Height, std::size_t Width>
static void printBlock(const char (&object)[Height][Width], int baseRow,
                       int baseCol) {
  for (int row = 0; row != Height; ++row) {
    move_cursor(baseRow + row, baseCol);
    std::cout << object[row];
  }
  std::cout << std::flush;
}

} // namespace detail

class DigitPad {
  const TextColor mColor;
  const int mBaseRow;
  const int mBaseCol;
  int mCurrentDigit;

public:
  DigitPad(TextColor color, int baseRow, int baseCol);

  int getBaseRow() const;

  int getBaseCol() const;

  int getDigit() const;

  void print() const;

  enum class ScrollDirection { Up, Down };

  void updateAndScroll(int newDigit, ScrollDirection scrollDir);
};

class Player {
  std::string mName;
  DigitPad mTensPlace;
  DigitPad mOnesPlace;

public:
  enum class Side { Left, Right };

  Player(std::string name, Side side)
      : mName{std::move(name)},
        mTensPlace{ColorOfSide(side), 0, BaseColOfSide(side)},
        mOnesPlace{ColorOfSide(side), 0, BaseColOfSide(side) + FrameWidth} {}

  int getScore() const;

  void print() const;

  void updateScore(int delta);

private:
  static TextColor ColorOfSide(Side side);

  static int BaseColOfSide(Side side);
};

class ScoreBoard {
  Player mLeft;
  Player mRight;

public:
  ScoreBoard(std::string leftName, std::string rightName)
      : mLeft{std::move(leftName), Player::Side::Left},
        mRight{std::move(rightName), Player::Side::Right} {
    // TODO:
  }

  void leftInc(int delta = 1) { mLeft.updateScore(delta); }
  void rightInc(int delta = 1) { mRight.updateScore(delta); }
  void leftDec(int delta = 1) { mLeft.updateScore(-delta); }
  void rightDec(int delta = 1) { mRight.updateScore(-delta); }

  ~ScoreBoard() {
    for (int row = FrameHeight; row >= 0; --row) {
      move_cursor(row, 0);
      clear_to_eol();
      sleep_ms(MSPerTick);
    }
  }
};

#endif // SCOREBOARD_HPP