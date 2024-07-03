#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

typedef enum { Up, Left, Idle, Right, Down } Direction;

Direction oppositeDirection(Direction dir) { return (Direction)(4 - dir); }

Coord moveOneStep(Coord from, Direction dir) {
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

  int numNodes;
  int *nodeID;
  int **dist;
} Game;

bool isWall(char c) { return c == 'B' || c == 'Y' || c == 'R' || c == 'G'; }

bool isFood(char c) { return c == '.'; }

bool isPacman(char c) { return c == 'C'; }

bool isGhost(char c) { return c == '@'; }

bool isValidPos(const Game *pGame, Coord pos) {
  return pos.row >= 0 && pos.row < pGame->numRows && pos.col >= 0 &&
         pos.col < pGame->numCols;
}

int getNodeID(const Game *pGame, Coord pos) {
  return pGame->nodeID[pos.row * pGame->numCols + pos.col];
}

int getDist(const Game *pGame, Coord from, Coord to) {
  int fromID = getNodeID(pGame, from);
  int toID = getNodeID(pGame, to);
  return fromID != -1 && toID != -1 ? pGame->dist[fromID][toID] : INT_MAX;
}

void calculateDists(Game *pGame) {
  pGame->nodeID = malloc(sizeof(int) * pGame->numRows * pGame->numCols);
  pGame->numNodes = 0;
  for (int r = 0; r != pGame->numRows; ++r)
    for (int c = 0; c != pGame->numCols; ++c) {
      int i = r * pGame->numCols + c;
      if (isWall(pGame->grid[r][c]))
        pGame->nodeID[i] = -1;
      else
        pGame->nodeID[i] = pGame->numNodes++;
    }
  pGame->dist = malloc(sizeof(int *) * pGame->numNodes);
  for (int i = 0; i != pGame->numNodes; ++i) {
    pGame->dist[i] = malloc(sizeof(int) * pGame->numNodes);
    for (int j = 0; j != pGame->numNodes; ++j)
      pGame->dist[i][j] = INT_MAX;
    pGame->dist[i][i] = 0;
  }

  Coord *queue = malloc(sizeof(Coord) * pGame->numNodes);
  bool *visited = malloc(sizeof(bool) * pGame->numNodes);
  for (int rs = 0; rs != pGame->numRows; ++rs)
    for (int cs = 0; cs != pGame->numCols; ++cs) {
      int startID = getNodeID(pGame, (Coord){rs, cs});
      if (startID == -1)
        continue;
      memset(visited, 0, sizeof(bool) * pGame->numNodes);
      visited[startID] = true;
      int head = 0, tail = 1;
      queue[0] = (Coord){rs, cs};
      while (head < tail) {
        Coord x = queue[head++];
        int xID = getNodeID(pGame, x);
        for (int d = 0; d != 5; ++d) {
          if (d == Idle)
            continue;
          Coord to = moveOneStep(x, (Direction)d);
          if (!isValidPos(pGame, to) || isWall(pGame->grid[to.row][to.col]))
            continue;
          int toID = getNodeID(pGame, to);
          if (!visited[toID]) {
            visited[toID] = true;
            queue[tail++] = to;
            pGame->dist[startID][toID] = pGame->dist[startID][xID] + 1;
          }
        }
      }
    }
  free(queue);
  free(visited);
}

Game createGame(int level, const char *mapFileName) {
  FILE *mapFile = fopen(mapFileName, "r");
  if (!mapFile) {
    fprintf(stderr, "Unable to open file %s.\n", mapFileName);
    exit(EXIT_FAILURE);
  }

  Game game = {
      .status = GS_Preparing, .level = level, .score = 0, .foodsCnt = 0};
  fscanf(mapFile, "%d%d%d", &game.numRows, &game.numCols, &game.ghostCnt);
  to_next_line(mapFile);

  game.grid = malloc(sizeof(char *) * game.numRows);
  for (int i = 0; i != game.numRows; ++i)
    game.grid[i] = malloc(game.numCols + 1);

  for (int i = 0; i != game.numRows; ++i) {
    read_line(mapFile, game.grid[i]);
    for (int j = 0; j != game.numCols; ++j) {
      if (isPacman(game.grid[i][j]))
        game.pacmanPos = (Coord){i, j};
      else if (isdigit(game.grid[i][j])) {
        game.ghosts[game.grid[i][j] - '0'].pos = (Coord){i, j};
        game.grid[i][j] = '@';
      } else if (isFood(game.grid[i][j]))
        ++game.foodsCnt;
    }
  }

  for (int i = 0; i != game.ghostCnt; ++i) {
    char buf[10] = {0};
    fscanf(mapFile, "%s", buf);
    switch (buf[0]) {
    case 'u': game.ghosts[i].direction = Up; break;
    case 'd': game.ghosts[i].direction = Down; break;
    case 'l': game.ghosts[i].direction = Left; break;
    case 'r': game.ghosts[i].direction = Right; break;
    default: assert(0 && "Ghost direction invalid");
    }
    game.ghosts[i].itemBelow = ' ';
  }
  fclose(mapFile);

  calculateDists(&game);

  return game;
}

void destroyGame(Game *pGame) {
  for (int i = pGame->numRows - 1; i >= 0; --i)
    free(pGame->grid[i]);
  free(pGame->grid);
  free(pGame->nodeID);
  for (int i = pGame->numNodes - 1; i >= 0; --i)
    free(pGame->dist[i]);
  free(pGame->dist);
}

void printInitialGame(const Game *pGame) {
  clear_screen();
  for (int i = 0; i != pGame->numRows; ++i) {
    for (int j = 0; j != pGame->numCols; ++j) {
      switch (pGame->grid[i][j]) {
      case 'C': printf(BRIGHT_YELLOW_TEXT("C")); break;
      case 'B': printf(BRIGHT_BLUE_TEXT("#")); break;
      case 'Y': printf(YELLOW_TEXT("#")); break;
      case 'R': printf(RED_TEXT("#")); break;
      case 'G': printf(GREEN_TEXT("#")); break;
      default: putchar(pGame->grid[i][j]); break;
      }
    }
    putchar('\n');
  }
  putchar('\n');
  assert(pGame->score == 0);
  printf("Level %d\n", pGame->level);
  printf("Score: 0\n");
  printf("Food remaining: %d\n", pGame->foodsCnt);
  printf("Pacman wants food! (control by w/a/s/d)\n");
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
  return Idle;
}

void printScoreUpdate(const Game *pGame) {
  move_cursor(pGame->numRows + 2, 7);
  printf("%d          ", pGame->score);
}

void printFoodUpdate(const Game *pGame) {
  move_cursor(pGame->numRows + 3, 16);
  printf("%d          ", pGame->foodsCnt);
}

void moveOneGhost(Game *pGame, Ghost *pGhost) {
  Coord newPos = moveOneStep(pGhost->pos, pGhost->direction);
  if (!isValidPos(pGame, newPos) ||
      isWall(pGame->grid[newPos.row][newPos.col])) {
    pGhost->direction = oppositeDirection(pGhost->direction);
    newPos = moveOneStep(pGhost->pos, pGhost->direction);
  }
  assert(!isWall(pGame->grid[newPos.row][newPos.col]));
  pGhost->itemBelow = pGame->grid[newPos.row][newPos.col];
  pGhost->pos = newPos;
}

void moveOneGhostSmart(Game *pGame, Ghost *pGhost) {
  Coord newPos = pGhost->pos;
  int minDist = getDist(pGame, pGhost->pos, pGame->pacmanPos);
  for (int d = 0; d != 5; ++d) {
    Coord p = moveOneStep(pGhost->pos, (Direction)d);
    if (isValidPos(pGame, p) && !isWall(pGame->grid[p.row][p.col])) {
      int dist = getDist(pGame, p, pGame->pacmanPos);
      if (dist < minDist) {
        newPos = p;
        minDist = dist;
      }
    }
  }
  pGhost->itemBelow = pGame->grid[newPos.row][newPos.col];
  pGhost->pos = newPos;
}

void moveGhosts(Game *pGame) {
  // Since ghosts may overlap, we first remove all the ghosts in reverse order.
  for (int i = pGame->ghostCnt - 1; i >= 0; --i) {
    Ghost *pGhost = pGame->ghosts + i;
    pGame->grid[pGhost->pos.row][pGhost->pos.col] = pGhost->itemBelow;
    move_cursor(pGhost->pos.row, pGhost->pos.col);
    putchar(pGhost->itemBelow);
  }
  for (int i = 0; i != pGame->ghostCnt; ++i) {
    Ghost *pGhost = pGame->ghosts + i;
    moveOneGhostSmart(pGame, pGhost);
    pGame->grid[pGhost->pos.row][pGhost->pos.col] = '@';
    move_cursor(pGhost->pos.row, pGhost->pos.col);
    putchar('@');
  }
}

void movePacman(Game *pGame) {
  // Erase the character at the original position
  Coord *pos = &pGame->pacmanPos;
  pGame->grid[pos->row][pos->col] = ' ';
  move_cursor(pos->row, pos->col);
  putchar(' ');
  // Move to the new position
  Direction dir = getPacmanMovement();
  Coord newPos = moveOneStep(*pos, dir);
  if (!isValidPos(pGame, newPos) || isWall(pGame->grid[newPos.row][newPos.col]))
    newPos = *pos;
  *pos = newPos;
  // Eats the food
  if (isFood(pGame->grid[pos->row][pos->col])) {
    pGame->score += 10;
    printScoreUpdate(pGame);
    --pGame->foodsCnt;
    printFoodUpdate(pGame);
  }
  if (!isGhost(pGame->grid[pos->row][pos->col])) {
    pGame->grid[pos->row][pos->col] = 'C';
    move_cursor(pos->row, pos->col);
    printf(BRIGHT_YELLOW_TEXT("C"));
  }
}

bool pacmanDies(const Game *pGame) {
  return !isPacman(pGame->grid[pGame->pacmanPos.row][pGame->pacmanPos.col]);
}

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

// Returns whether the player wins.
bool runLevel(int level) {
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
  bool win = game.status == GS_Win;
  destroyGame(&game);
  return win;
}

// Returns 0 on Enter, 1 on 'q' or 'Q'.
int enterOrQuit(void) {
  while (1) {
    if (kbhit()) {
      int key = getch();
      if (key == '\n' || key == '\r')
        return 0;
      else if (key == 'q' || key == 'Q')
        return 1;
    }
  }
}

void runAllLevels(void) {
  int level = 0;
  while (1) {
    bool wins = runLevel(level);
    if (wins) {
      if (level == MAX_LEVEL) {
        printf("Congratulations! You have passed all the levels.\n");
        break;
      } else {
        printf("Press Enter to enter the next level, or q to quit.\n");
        if (enterOrQuit() == 0)
          ++level;
        else
          break;
      }
    } else {
      printf("Press Enter to restart the level, or q to quit.\n");
      if (enterOrQuit() == 1)
        break;
    }
  }
}

int main(int argc, char **argv) {
  prepare_game();
  if (argc == 2) {
    int level = atoi(argv[1]);
    runLevel(level);
  } else
    runAllLevels();
  return 0;
}