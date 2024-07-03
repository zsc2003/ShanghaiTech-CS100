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
} Coord; //typedef重新定义类型名

// Remark: Each enum item corresponds to an integer, starting from 0.
typedef enum { Up, Left, Idle, Right, Down } Direction; //定义一个枚举类型

Direction oppositeDirection(Direction dir) { return (Direction)(4 - dir); } 
//定义一个反方向移动的函数（enum类型的移动方向是对称的）,接受一个已声明的enum变量，并且返回对称的数，在此时为相反的方向
//这里的返回值（return后面的）是(Direction)(4 - dir)，其中(4 - dir)是一个表达式，而(Direction)是进行类型转换，将整形转换为枚举常量
Coord moveOneStep(Coord from, Direction dir) { 
  //是一个函数，接受一个已定义的结构体和枚举类型的参数，返回类型是最前面的结构体Coord（这里最前面的Coord仅仅是表示返回值类型的）
  // Understand the trick here.
  static const int rowDelta[] = {-1, 0, 0, 0, 1};
  static const int colDelta[] = {0, -1, 0, 1, 0};
  //这里是函数内部定义的两个静态数组变量，是为了返回值的时候用到的
  return (Coord){from.row + rowDelta[dir], from.col + colDelta[dir]}; //针对枚举类型，两个静态数组上下搭配使用，比如UP是行-1，列0（不变）
  //定义移动的函数，顾名思义，作用是移动一步，所以仅用静态数组就可以完成，这里的(Coord)是结构体初始化语法，来形成一个新的结构体，
  //{from.row + rowDelta[dir], from.col + colDelta[dir]}作为数据放到结构体里
}

typedef struct {
  Coord pos; //初始化一个结构体（结构体嵌套）表示地图大小
  Direction direction; //定义一个enum类型的成员变量
  char itemBelow;
} Ghost;
//定义个鬼结构体，其中里面的成员是鬼应该具有的性质

typedef enum { GS_Preparing, GS_Running, GS_Win, GS_Lose } GameStatus; //枚举不同的游戏状态

typedef struct { //利用不同结构体的嵌套，表示游戏的基本信息，成员是Game应具有的性质
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

bool isGhost(char c) { return c == '@'; } //定义这几个判断函数（布尔函数），如果是规定的特殊意义的字符，则返回True，利用了bool类型

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
  FILE *mapFileLevel = fopen(mapFileName, "r");
  int rows, columns, numofGousts;
  fscanf(mapFileLevel, "%d %d %d",&rows, &columns, &numofGousts);
  char **grid = (char**)malloc(sizeof(char *)*rows);
  for (int i = 0; i < rows; i++){
    grid[i] = (char *)malloc(sizeof(char)*columns);
  }
  int i = 0, j = 0;
  char ch;
  while (fscanf(mapFileLevel, "%c", &ch) != EOF){
    grid[i][j] = ch;
    j++;
    if (j == columns){
      j = 0;
      i++;
      if (i == rows){
        break;
      }
    }
  }
  //打开文件并读取map中的所有数据
  fclose(mapFileLevel);
  Game game;
  game.numRows = rows;
  game.numCols = columns;
  game.ghostCnt = numofGousts;
  game.foodsCnt = 0;

  game.status = GS_Preparing;
  game.level = level;
  game.score = 0;

  game.pacmanPos.row = 0;
  game.pacmanPos.col = 0;
  
  for (int i = 0; i < MAX_GHOSTS; i++) {
      
      game.ghosts[i].pos.row = 0; 
      game.ghosts[i].pos.col = 0;
      game.ghosts[i].direction = Idle; 
      game.ghosts[i].itemBelow = ' '; 
  }

  game.grid = grid;
  //进行初始化



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
void destroyGame(Game *pGame) {//释放malloc的内存
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
      //遍历每一行和列，使用结构体指针的引用
      switch (pGame->grid[i][j]) {
      case 'C': printf(BRIGHT_YELLOW_TEXT("C")); break;
      case 'B': printf(BLUE_TEXT("#")); break;
      case 'Y': printf(YELLOW_TEXT("#")); break;
      case 'R': printf(RED_TEXT("#")); break;
      case 'G': printf(GREEN_TEXT("#")); break;
      default: putchar(pGame->grid[i][j]); break;
      }
    }//对于每一个元素，打印出显示值
    putchar('\n');//每一行打印完换行
  }
  putchar('\n');
  printf("Level %d\n", pGame->level);
  assert(pGame->score == 0);
  printf("Score: 0\n");
  printf("Food remaining: %d\n", pGame->foodsCnt);
  printf("Pacman wants food! (control by w/a/s/d)\n");
  //打印游戏的初始状态和提示信息
}

void printScoreUpdate(const Game *pGame) {
  move_cursor(pGame->numRows + 2, 7);
  printf("%d          ", pGame->score);
}

void printFoodUpdate(const Game *pGame) {
  move_cursor(pGame->numRows + 3, 16);
  //移动光标到score位置进行输入更新
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
    for (int i = pGame->ghostCnt - 1; i >= 0; --i) {
        Ghost *pGhost = &pGame->ghosts[i];

        pGame->grid[pGhost->pos.row][pGhost->pos.col] = pGhost->itemBelow;
    }

    for (int i = 0; i < pGame->ghostCnt; ++i) {
        Ghost *pGhost = &pGame->ghosts[i];

        int row = pGhost->pos.row;
        int col = pGhost->pos.col;


        switch (pGhost->direction) {
            case Up:
  
                if (row - 1 >= 0 && !isWall(pGame->grid[row - 1][col])) {
                    pGhost->pos.row--;
                }
                break;
            case Down:
  
                if (row + 1 < pGame->numRows && !isWall(pGame->grid[row + 1][col])) {
                    pGhost->pos.row++;
                }
                break;
            case Left:

                if (col - 1 >= 0 && !isWall(pGame->grid[row][col - 1])) {
                    pGhost->pos.col--;
                }
                break;
            case Right:
            
                if (col + 1 < pGame->numCols && !isWall(pGame->grid[row][col + 1])) {
                    pGhost->pos.col++;
                }
                break;
            default:
                break;
        }


        pGhost->itemBelow = pGame->grid[pGhost->pos.row][pGhost->pos.col];
        pGame->grid[pGhost->pos.row][pGhost->pos.col] = '@';
    }
}


Direction getPacmanMovement(void) {
  if (kbhit()) { //kbhit函数用来检验是否有键盘输入
    switch (getch()) { //获取键盘输入
    case 'w': return Up;
    case 's': return Down;
    case 'a': return Left;
    case 'd': return Right;
    }//因为有return可以直接结束函数所以没有break
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
  Direction direction = getPacmanMovement(); // Get Pacman's movement direction
  Coord nextPos = moveOneStep(pGame->pacmanPos, direction); // Calculate Pacman's next position
  char nextCell = pGame->grid[nextPos.row][nextPos.col]; // Get the content of the next cell
  
  // Handle the case when Pacman moves to an empty cell or a cell with food
  if (!isWall(nextCell)) {
    pGame->grid[pGame->pacmanPos.row][pGame->pacmanPos.col] = ' '; // Clear Pacman's current position
    pGame->pacmanPos = nextPos; // Update Pacman's position to the next position
    pGame->grid[pGame->pacmanPos.row][pGame->pacmanPos.col] = 'C'; // Place Pacman on the grid
    if (isFood(nextCell)) { // If Pacman eats a food
      pGame->foodsCnt--; // Decrease the remaining food count
      pGame->score++; // Increase the score
      } else {
        pGame->score--; // Decrease the score when moving to an empty cell
    }
  }

  // Update the display on the screen
  // (Assuming you have a function to print the game screen)
  printInitialGame(pGame);
}

/**
 * @brief Test if Pacman has died.
 */
bool pacmanDies(const Game *pGame) {
  char cellUnderPacman = pGame->grid[pGame->pacmanPos.row][pGame->pacmanPos.col]; 
  return isGhost(cellUnderPacman) || isWall(cellUnderPacman); 
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
  for (int level = 0; level <= MAX_LEVEL; ++level) {
    runLevel(level);
    char input;
    scanf(" %c", &input);
    if (input == 'q') {
  
      break; 
    }
  }
  return 0;
}
