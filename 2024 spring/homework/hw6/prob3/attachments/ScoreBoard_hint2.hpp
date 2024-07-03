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

class NamePad {
  const std::string mName;
  const int mRow;
  const int mBeginCol;
  const int mWidth;

public:
  NamePad(std::string name, int row, int beginCol, int width)
      : mName{std::move(name)}, mRow{row}, mBeginCol{beginCol}, mWidth{width} {}

  void print() const;
};

class Player {
  NamePad &mNamePad;
  DigitPad &mTensPlace;
  DigitPad &mOnesPlace;

  using ScrollDir = DigitPad::ScrollDirection;

public:
  Player(NamePad &namePad, DigitPad &tensPlace, DigitPad &onesPlace)
      : mNamePad{namePad}, mTensPlace{tensPlace}, mOnesPlace{onesPlace} {}

  int getScore() const;

  void updateScore(int delta);
};

class ScoreBoard {
  // As an alternative, one can also create an array of four DigitPads.
  // For example:
  //     DigitPad mDigits[4];
  // To initialize it in a constructor initializer list:
  //    mDigits{{TextColor::Red, 0, 0},
  //            {TextColor::Red, 0, FrameWidth},
  //            {TextColor::Blue, 0, 2 * FrameWidth + ColonWidth},
  //            {TextColor::Blue, 0, 3 * FrameWidth + ColonWidth}}
  DigitPad mLeftTens;
  DigitPad mLeftOnes;
  DigitPad mRightTens;
  DigitPad mRightOnes;

  NamePad mLeftName;
  NamePad mRightName;

  Player mLeftPlayer;
  Player mRightPlayer;

public:
  ScoreBoard(std::string leftName, std::string rightName)
      : mLeftTens{TextColor::Red, 0, 0},
        mLeftOnes{TextColor::Red, 0, FrameWidth},
        mRightTens{TextColor::Blue, 0, 2 * FrameWidth + ColonWidth},
        mRightOnes{TextColor::Blue, 0, 3 * FrameWidth + ColonWidth},
        mLeftName{std::move(leftName), 0, 0, 2 * FrameWidth},
        mRightName{std::move(rightName), 0, 2 * FrameWidth + ColonWidth,
                   2 * FrameWidth},
        mLeftPlayer{mLeftName, mLeftTens, mLeftOnes},
        mRightPlayer{mRightName, mRightTens, mRightOnes} {
    // TODO:
  }

  void leftInc(int delta = 1) { mLeftPlayer.updateScore(delta); }
  void rightInc(int delta = 1) { mRightPlayer.updateScore(delta); }
  void leftDec(int delta = 1) { mLeftPlayer.updateScore(-delta); }
  void rightDec(int delta = 1) { mRightPlayer.updateScore(-delta); }

  ~ScoreBoard() {
    for (int row = FrameHeight; row >= 0; --row) {
      move_cursor(row, 0);
      clear_to_eol();
      sleep_ms(MSPerTick);
    }
  }
};

#endif // SCOREBOARD_HPP