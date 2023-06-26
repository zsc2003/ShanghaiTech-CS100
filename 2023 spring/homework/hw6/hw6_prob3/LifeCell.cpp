#include "LifeCell.h"
#include "GameSettings.h"

CellPointer CreateCell(const int x, const int y, const int state)
{
    return std::make_shared<LifeCell>(x, y, state);
}