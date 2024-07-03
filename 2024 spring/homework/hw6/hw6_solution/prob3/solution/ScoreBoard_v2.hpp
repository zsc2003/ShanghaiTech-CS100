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

class NamePad {
  const std::string mName;
  const int mRow;

public:
  NamePad(std::string name, int row)
      : mName{std::move(name)}, mRow{row} {}

  void print() const {
    PrinterGuard printing;
    move_cursor(mRow, 0);
    std::cout << mName << std::flush;
  }
};

class Player {
  NamePad &mNamePad;
  DigitPad &mPointsTens;
  DigitPad &mPointsOnes;
  DigitPad &mGames;

  using ScrollDir = DigitPad::ScrollDirection;

public:
  Player(NamePad &namePad, DigitPad &pointsTens, DigitPad &pointsOnes,
         DigitPad &games)
      : mNamePad{namePad}, mPointsTens{pointsTens}, mPointsOnes{pointsOnes},
        mGames{games} {}

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
  static DigitPad::ScrollDirection deltaToDirection(int delta) {
    return delta > 0 ? DigitPad::ScrollDirection::Up
                     : DigitPad::ScrollDirection::Down;
  }
};

class ScoreBoard {
  DigitPad mDigits[6];
  NamePad mNames[2];
  Player mLeftPlayer;
  Player mRightPlayer;

  ScoreBoard(std::string &&leftName, std::string &&rightName, int scoreBeginCol)
      : mDigits{{TextColor::Normal, 0, scoreBeginCol, false},
                {TextColor::Red, 0, scoreBeginCol + FrameWidth},
                {TextColor::Red, 0, scoreBeginCol + 2 * FrameWidth},
                {TextColor::Normal, FrameHeight, scoreBeginCol, false},
                {TextColor::Blue, FrameHeight, scoreBeginCol + FrameWidth},
                {TextColor::Blue, FrameHeight, scoreBeginCol + 2 * FrameWidth}},
        mNames{{std::move(leftName), FrameHeight / 2},
               {std::move(rightName), FrameHeight * 3 / 2}},
        mLeftPlayer{mNames[0], mDigits[1], mDigits[2], mDigits[0]},
        mRightPlayer{mNames[1], mDigits[4], mDigits[5], mDigits[3]} {
    clear_screen();
    PrinterGuard printing;
    for (const auto &digit : mDigits)
      digit.print();
    for (const auto &name : mNames)
      name.print();
  }

public:
  ScoreBoard(std::string leftName, std::string rightName)
      : ScoreBoard(std::move(leftName), std::move(rightName), std::max(leftName.size(), rightName.size() + 2)) {}

  void leftIncPoints(int delta = 1) { mLeftPlayer.updatePoints(delta); }
  void rightIncPoints(int delta = 1) { mRightPlayer.updatePoints(delta); }
  void leftDecPoints(int delta = 1) { mLeftPlayer.updatePoints(-delta); }
  void rightDecPoints(int delta = 1) { mRightPlayer.updatePoints(-delta); }

  void leftIncGames(int delta = 1) { mLeftPlayer.updateGames(delta); }
  void rightIncGames(int delta = 1) { mRightPlayer.updateGames(delta); }
  void leftDecGames(int delta = 1) { mLeftPlayer.updateGames(-delta); }
  void rightDecGames(int delta = 1) { mRightPlayer.updateGames(-delta); }

  ~ScoreBoard() {
    for (int row = FrameHeight * 2; row >= 0; --row) {
      move_cursor(row, 0);
      clear_to_eol();
      sleep_ms(MSPerTick);
    }
  }
};

#endif // SCOREBOARD_HPP