#include <algorithm>
#include <cctype>
#include <string>
#include "GameWorld.h"

GameWorld::GameWorld(const int width, const int height, const std::shared_ptr<LifeRuleBase> &rule)
    : m_map(height, WorldMapRow(width)),
      m_mapNext(height, WorldMapRow(width)),
      m_rule(rule),
      m_width(width),
      m_height(height)
{
    for (int i = 0; i < GetHeight(); ++i)
    {
        for (int j = 0; j < GetWidth(); ++j)
        {
            m_map[i][j] = CreateCell(i, j, CELL_STATE_DEAD);
        }
    }
}

GameWorld::GameWorld(const int width, const int height, std::string rule_type)
    : m_map(height, WorldMapRow(width)),
      m_mapNext(height, WorldMapRow(width)),
      m_width(width),
      m_height(height)
{
    // Convert rule_type to lower case
    std::transform(rule_type.cbegin(), rule_type.cend(), rule_type.begin(), [](unsigned char c)
                   { return std::tolower(c); });

    if (rule_type == "colorised")
        m_rule = std::make_shared<LifeRuleColorised>();
    else if (rule_type == "generations")
        m_rule = std::make_shared<LifeRuleGenerations>();
    else if (rule_type == "extended")
        m_rule = std::make_shared<LifeRuleExtended>();
    else if (rule_type == "weighted")
        m_rule = std::make_shared<LifeRuleWeighted>();
    else if (rule_type == "base")
        m_rule = std::make_shared<LifeRuleBase>();
    else
        throw std::invalid_argument("Invalid rule type");
    for (int i = 0; i < GetHeight(); ++i)
    {
        for (int j = 0; j < GetWidth(); ++j)
        {
            m_map[i][j] = CreateCell(i, j, CELL_STATE_DEAD);
        }
    }
}

void GameWorld::Update()
{
    for (int row = 0; row < GetHeight(); ++row)
    {
        for (int col = 0; col < GetWidth(); ++col)
        {
            const auto neighbors = GetNeighbors(row, col);
            m_mapNext[row][col] = std::make_shared<LifeCell>(*m_map[row][col]);
            CellUpdate(m_mapNext[row][col], neighbors);
        }
    }
    std::swap(m_mapNext, m_map);
}

std::string GameWorld::GetWorldStr() const
{
    std::string world_str;
    for (const WorldMapRow &row : m_map)
    {
        for (const CellPointer &cell : row)
        {
            if (GetRuleName() == "Generations")
            {
                world_str += std::to_string(cell->GetState());
            }
            else
            {
                switch (cell->GetState())
                {
                case CELL_STATE_DEAD:
                    world_str += ".";
                    break;
                case CELL_STATE_RED:
                    world_str += "R";
                    break;
                case CELL_STATE_BLUE:
                    world_str += "B";
                    break;
                case CELL_STATE_ALIVE:
                default:
                    world_str += "O";
                    break;
                }
            }
        }
        world_str += "\n";
    }
    return world_str;
}