#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "utils.h"

#define MAX_LEVEL 3

// To enable more ghosts, we will need to update our map file format.
#define MAX_GHOSTS 10
#define MS_PER_GHOST_TICK 500
#define MS_PER_TICK 20

typedef struct {
  int row;
  int col;
} Coord;

// Remark: Each enum item corresponds to an integer, starting from 0.
typedef enum { Up, Left, Idle, Right, Down } Direction;

Direction oppositeDirection(Direction dir) { return (Direction)(4 - dir); }

Coord moveOneStep(Coord from, Direction dir) {
  // Understand the trick here.
  static const int rowDelta[] = {-1, 0, 0, 0, 1};
  static const int colDelta[] = {0, -1, 0, 1, 0};
  return (Coord){from.row + rowDelta[dir], from.col + colDelta[dir]};
}

typedef struct {
  Coord pos;
  Direction direction;
  char itemBelow;
} Ghost;

typedef enum { GS_Preparing, GS_Running, GS_Win, GS_Lose } GameStatus;

typedef struct {
  GameStatus status;
  int level;
  int score;

  int numRows;
  int numCols;
  int ghostCnt;
  int foodsCnt;

  Coord pacmanPos;

  Ghost ghosts[MAX_GHOSTS];

  char **grid;
} Game;

bool isWall(char c) { return c == 'B' || c == 'Y' || c == 'R' || c == 'G'; }

bool isFood(char c) { return c == '.'; }

bool isPacman(char c) { return c == 'C'; }

bool isGhost(char c) { return c == '@'; }

/**
 * @brief Create a Game object. Level information including the map is read from
 * the file @c mapFileName. Return the Game object created.
 *
 * @param level Level ID.
 * @param mapFileName Path to the map file.
 * @return Game The created Game object.
 */
Game createGame(int level, const char *mapFileName) {
  // TODO: Implement this function.
  // Create a Game object. The information needed should be obtained from the
  // file 'mapFileName'. Every member of the Game object should be correctly
  // set, some of which you need to pay special attention to:
  //   - 'status' should be set to GS_Preparing.
  //   - 'score' should be set to zero.
  //   - 'itemBelow' of each ghost should also be correctly set. This influences
  //   the way you move ghosts. Think about it carefully.
  //   - 'grid' should be a dynamically allocated "2d-array". The function
  //   'printInitialGame' below serves as a hint on the contents of 'grid'.
  // Do not forget to close the file you opened.
}

/**
 * @brief Destroy a Game object. Resources are released.
 *
 * @param pGame
 */
void destroyGame(Game *pGame) {
  for (int i = pGame->numRows - 1; i >= 0; --i)
    free(pGame->grid[i]);
  free(pGame->grid);
  // If your Game has some other resources, they should also be released.
}

void printInitialGame(const Game *pGame) {
  // Called at the beginning of 'runGame'.
  // Your 'createGame' should set the contents of 'grid' correctly to make this
  // function work.
  clear_screen();
  for (int i = 0; i != pGame->numRows; ++i) {
    for (int j = 0; j != pGame->numCols; ++j) {
      switch (pGame->grid[i][j]) {
      case 'C': printf(BRIGHT_YELLOW_TEXT("C")); break;
      case 'B': printf(BLUE_TEXT("#")); break;
      case 'Y': printf(YELLOW_TEXT("#")); break;
      case 'R': printf(RED_TEXT("#")); break;
      case 'G': printf(GREEN_TEXT("#")); break;
      default: putchar(pGame->grid[i][j]); break;
      }
    }
    putchar('\n');
  }
  putchar('\n');
  printf("Level %d\n", pGame->level);
  assert(pGame->score == 0);
  printf("Score: 0\n");
  printf("Food remaining: %d\n", pGame->foodsCnt);
  printf("Pacman wants food! (control by w/a/s/d)\n");
}

void printScoreUpdate(const Game *pGame) {
  move_cursor(pGame->numRows + 2, 7);
  printf("%d          ", pGame->score);
}

void printFoodUpdate(const Game *pGame) {
  move_cursor(pGame->numRows + 3, 16);
  printf("%d          ", pGame->foodsCnt);
}

/**
 * @brief Move all the ghosts by one step. Their @c pos should be updated, and
 * the contents in @c pGame->grid and things printed on the screen should also
 * be updated.
 *
 * @param pGame Pointer to the current Game object.
 */
void moveGhosts(Game *pGame) {
  // TODO: Implement this function.
  // Move all the ghosts by one step. You are encouraged to move ghosts in a
  // smarter way.
  // Note that ghosts may overlap, and they may also overlap with foods. Hints
  // on this:
  //  - The 'itemBelow' member of Ghost may be of great help.
  //  - A possible way to handle overlapping objects correctly is to first
  //  remove all the ghosts in reverse order, and then put the ghosts on their
  //  new positions in order.
}

Direction getPacmanMovement(void) {
  if (kbhit()) {
    switch (getch()) {
    case 'w': return Up;
    case 's': return Down;
    case 'a': return Left;
    case 'd': return Right;
    }
  }
  // Note that 'Idle' is also returned when no keyboard hit occurs.
  return Idle;
}

/**
 * @brief Move the Pacman by one step, following the user's control obtained by
 * @c getPacmanMovement(). Pacman's position should be updated, and the contents
 * in @c pGame->grid and things printed on the screen should also be updated. If
 * the Pacman eats a food through this step, the related information stored and
 * printed should also be updated.
 *
 * @param pGame Pointer to the current Game object.
 */
void movePacman(Game *pGame) {
  // TODO: Implement this function.
  // Note that Pacman may be moved to a position containing a food or a ghost.
  // These cases should be handled carefully.
}

/**
 * @brief Test if Pacman has died.
 */
bool pacmanDies(const Game *pGame) {
  // TODO: Implement this function.
}

/**
 * @brief Test if the game has ended. If so, update the @c status and return
 * true; otherwise return false.
 *
 * @param pGame Pointer to the current Game object.
 */
bool gameEnds(Game *pGame) {
  if (pacmanDies(pGame)) {
    pGame->status = GS_Lose;
    return true;
  }
  if (pGame->foodsCnt == 0) {
    pGame->status = GS_Win;
    return true;
  }
  return false;
}

void runGame(Game *pGame) {
  printInitialGame(pGame);
  pGame->status = GS_Running;
  int ticks = 0;
  while (1) {
    sleep_ms(MS_PER_TICK);
    ++ticks;
    movePacman(pGame);
    if (gameEnds(pGame))
      break;
    if (ticks == MS_PER_GHOST_TICK / MS_PER_TICK) {
      ticks = 0;
      --pGame->score;
      printScoreUpdate(pGame);
      moveGhosts(pGame);
      if (gameEnds(pGame))
        break;
    }
  }
}

void runLevel(int level) {
  char path[100];
  sprintf(path, "maps/level%d.txt", level);
  Game game = createGame(level, path);
  runGame(&game);
  assert(game.status == GS_Lose || game.status == GS_Win);
  move_cursor(game.numRows + 4, 0);
  if (game.status == GS_Lose)
    printf("Pacman dies!");
  else
    printf("You win!");
  printf("                                       \n");
  destroyGame(&game);
}

int main(void) {
  prepare_game();
  // TODO: Run more levels?
  runLevel(3);
  return 0;
}