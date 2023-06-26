#ifndef GAMEMANAGER_H__
#define GAMEMANAGER_H__
#include <string>
#include "GameWorld.h"

/**
 * A simple ASCII interface for the Game of Life
 *
 **/

class GameManager
{
public:
    GameManager() = delete;
    ~GameManager() = default;
    GameManager(const GameManager &) = delete;

    GameManager(const std::shared_ptr<GameWorld> &world) : m_world(world) {}

    // Functionalities of the game

    /**
     * @brief Starts the game
     */
    void StartGame();

    /**
     * @brief Updates the game
     */
    void UpdateGame();

    /**
     * @brief Saves the current world to a file like a [plain text](https://conwaylife.com/wiki/Plaintext) .cells file format
     * 
     * Used for OJ to check your answer
     *
     * @param filename The name of the file to save to
     */
    void SaveWorld(const std::string &filename);

    /**
     * @brief Exits the game
     */
    void ExitGame();

    /**
     * @brief Loads a world from a .cells file
     *
     * The format of the file is as follows:
     * Comments start with a ! and are ignored
     * Cells are represented by a O or . (alive or dead respectively)
     * Additional rules can be found in the documentation
     *
     * @param filename The name of the file to load
     */
    bool LoadWorld(const std::string &filename);

    // For interface

    /**
     * Print welcome message
     */
    void PrintWelcomeMessage();

    /**
     * Print the current world
     */
    void PrintWorld();

    void SetGameOver(bool isGameOver) { this->isGameOver = isGameOver; }

    int GetRoundCount() const { return m_round_count; }
    void IncrementRoundCount() { ++m_round_count; }
    bool IsGameOver() { return isGameOver; }

private:
    std::shared_ptr<GameWorld> m_world;
    bool isGameOver = false;
    int m_round_count = 0;
};

#endif
