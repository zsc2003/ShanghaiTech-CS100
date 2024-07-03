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
  const bool mIsFramed;
  int mCurrentDigit;

public:
  DigitPad(TextColor color, int baseRow, int baseCol, bool isFramed = true)
      : mColor{color}, mBaseRow{baseRow}, mBaseCol{baseCol},
        mIsFramed{isFramed}, mCurrentDigit{0} {}

  int getBaseRow() const { return mBaseRow; }

  int getBaseCol() const { return mBaseCol; }

  int getDigit() const { return mCurrentDigit; }

  void print() const {
    PrinterGuard printing;
    ColorGuard withColor{mColor};
    if (mIsFramed)
      detail::printBlock(Frame, mBaseRow, mBaseCol);
    detail::printBlock(ArtDigit[mCurrentDigit], mBaseRow + DigitBaseRow,
                       mBaseCol + DigitBaseCol);
  }

  enum class ScrollDirection { Up, Down };

  void updateAndScroll(int newDigit, ScrollDirection scrollDir) {
    if (newDigit == mCurrentDigit)
      return;

    PrinterGuard printing;
    ColorGuard withColor{mColor};
    int topDigit = scrollDir == ScrollDirection::Up ? mCurrentDigit : newDigit;
    int bottomDigit = mCurrentDigit + newDigit - topDigit;
    for (int tick = 0; tick != DigitHeight + 1; ++tick) {
      int mid = scrollDir == ScrollDirection::Up ? tick : DigitHeight - tick;
      int row = mBaseRow + DigitBaseRow;
      for (int i = mid; i != DigitHeight; ++i) {
        move_cursor(row++, mBaseCol + DigitBaseCol);
        std::cout << ArtDigit[topDigit][i];
      }
      for (int i = 0; i != mid; ++i) {
        move_cursor(row++, mBaseCol + DigitBaseCol);
        std::cout << ArtDigit[bottomDigit][i];
      }
      std::cout << std::flush;
      sleep_ms(MSPerTick);
    }
    mCurrentDigit = newDigit;
  }
};

class Player {
  std::string mName;
  DigitPad mPointsTens;
  DigitPad mPointsOnes;
  DigitPad mGames;

public:
  enum class Side { Left, Right };

  Player(std::string name, Side side)
      : mName{std::move(name)},
        mPointsTens{ColorOfSide(side), 0, TensColOfSide(side)},
        mPointsOnes{ColorOfSide(side), 0, TensColOfSide(side) + FrameWidth},
        mGames{TextColor::Normal, 0, GamesColOfSide(side), false} {}

  void print() const {
    PrinterGuard printing;
    mPointsTens.print();
    mPointsOnes.print();
    mGames.print();
    int beginCol = std::min(mPointsTens.getBaseCol(), mGames.getBaseCol());
    move_cursor(FrameHeight, beginCol + (3 * FrameWidth - mName.size()) / 2);
    std::cout << mName << std::flush;
  }

  int getPoints() const {
    return mPointsTens.getDigit() * 10 + mPointsOnes.getDigit();
  }

  void updatePoints(int delta) {
    if (delta == 0)
      return;
    auto dir = deltaToDirection(delta);
    auto newPoint = getPoints() + delta;
    mPointsOnes.updateAndScroll(newPoint % 10, dir);
    mPointsTens.updateAndScroll(newPoint / 10, dir);
  }

  int getGamesWon() const { return mGames.getDigit(); }

  void updateGames(int delta) {
    if (delta == 0)
      return;
    auto dir = deltaToDirection(delta);
    auto newGames = getGamesWon() + delta;
    mGames.updateAndScroll(newGames, dir);
  }

private:
  static TextColor ColorOfSide(Side side) {
    if (side == Side::Left)
      return TextColor::Red;
    else
      return TextColor::Blue;
  }

  static int TensColOfSide(Side side) {
    if (side == Side::Left)
      return 0;
    else
      return 4 * FrameWidth + ColonWidth;
  }

  static int GamesColOfSide(Side side) {
    if (side == Side::Left)
      return 2 * FrameWidth;
    else
      return 3 * FrameWidth + ColonWidth;
  }

  static DigitPad::ScrollDirection deltaToDirection(int delta) {
    return delta > 0 ? DigitPad::ScrollDirection::Up
                     : DigitPad::ScrollDirection::Down;
  }
};

class ScoreBoard {
  Player mLeft;
  Player mRight;

public:
  ScoreBoard(std::string leftName, std::string rightName)
      : mLeft{std::move(leftName), Player::Side::Left},
        mRight{std::move(rightName), Player::Side::Right} {
    clear_screen();
    PrinterGuard printing;
    mLeft.print();
    mRight.print();
    detail::printBlock(Colon, 0, 3 * FrameWidth);
  }

  void leftIncPoints(int delta = 1) { mLeft.updatePoints(delta); }
  void rightIncPoints(int delta = 1) { mRight.updatePoints(delta); }
  void leftDecPoints(int delta = 1) { mLeft.updatePoints(-delta); }
  void rightDecPoints(int delta = 1) { mRight.updatePoints(-delta); }

  void leftIncGames(int delta = 1) { mLeft.updateGames(delta); }
  void rightIncGames(int delta = 1) { mRight.updateGames(delta); }
  void leftDecGames(int delta = 1) { mLeft.updateGames(-delta); }
  void rightDecGames(int delta = 1) { mRight.updateGames(-delta); }

  ~ScoreBoard() {
    for (int row = FrameHeight; row >= 0; --row) {
      move_cursor(row, 0);
      clear_to_eol();
      sleep_ms(MSPerTick);
    }
  }
};

#endif // SCOREBOARD_HPP