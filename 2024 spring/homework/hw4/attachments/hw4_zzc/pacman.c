
#include <assert.h>
#include <ctype.h>
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "utils.h"

#define MAX_LEVEL 3

#define MAX_GHOSTS 10
#define MS_PER_GHOST_TICK 500
#define MS_PER_TICK 20
#define MS_LEVEL_CHANGE 1000

typedef struct
{
    int row;
    int col;
} Coord;

typedef enum
{
    Up,
    Left,
    Idle,
    Right,
    Down
} Direction;

Direction oppositeDirection(Direction dir) { return (Direction)(4 - dir); }

Coord moveOneStep(Coord from, Direction dir)
{
    static const int rowDelta[] = {-1, 0, 0, 0, 1};
    static const int colDelta[] = {0, -1, 0, 1, 0};
    return (Coord){from.row + rowDelta[dir], from.col + colDelta[dir]};
}

typedef struct
{
    Coord pos;
    Direction direction;
    char itemBelow;
} Ghost;

typedef enum
{
    GS_Preparing,
    GS_Running,
    GS_Win,
    GS_Lose
} GameStatus;

typedef struct
{
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

bool isGhost(char c) { return (c >= '0' && c <= '9') || c == '@'; }

const char *directionToString(Direction direction)
{
    switch (direction)
    {
    case Up:
        return "Up";
    case Left:
        return "Left";
    case Idle:
        return "Idle";
    case Right:
        return "Right";
    case Down:
        return "Down";
    default:
        return "Invalid direction";
    }
}

Game createGame(int level, const char *mapFileName)
{
    FILE *file;
    file = fopen(mapFileName, "r");
    if (file == NULL)
    {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    Game result_game = {.status = GS_Preparing, .level = level, .score = 0, .foodsCnt = 0};
    fscanf(file, "%d %d %d", &result_game.numRows, &result_game.numCols, &result_game.ghostCnt);

    result_game.grid = (char **)malloc(sizeof(char *) * result_game.numRows);
    for (int i = 0; i != result_game.numRows; i++)
    {
        result_game.grid[i] = (char *)malloc(sizeof(char) * result_game.numCols);
    }
    for (int i = 0; i != result_game.numRows; i++)
    {
        for (int j = 0; j != result_game.numCols; j++)
        {
            result_game.grid[i][j] = fgetc(file);
            if (result_game.grid[i][j] == '\n')
            {
                result_game.grid[i][j] = fgetc(file);
            }
            if (isFood(result_game.grid[i][j]))
                result_game.foodsCnt++;
            else if (isGhost(result_game.grid[i][j]))
            {
                result_game.ghosts[result_game.grid[i][j] - '0'] = (Ghost){
                    .pos = (Coord){.row = i, .col = j},
                    .itemBelow = ' '};
                result_game.grid[i][j] = '@';
            }
            else if (isPacman(result_game.grid[i][j]))
                result_game.pacmanPos = (Coord){.row = i, .col = j};
        }
    }

    for (int i = 0; i != result_game.ghostCnt; i++)
    {
        char tmp_directions[6];
        fscanf(file, " %s", tmp_directions);
        if (strcmp(tmp_directions, "up") == 0)
        {
            result_game.ghosts[i].direction = Up;
        }
        else if (strcmp(tmp_directions, "left") == 0)
        {
            result_game.ghosts[i].direction = Left;
        }
        else if (strcmp(tmp_directions, "right") == 0)
        {
            result_game.ghosts[i].direction = Right;
        }
        else if (strcmp(tmp_directions, "down") == 0)
        {
            result_game.ghosts[i].direction = Down;
        }
    }

    fclose(file);
    return result_game;
}

void destroyGame(Game *pGame)
{
    for (int i = pGame->numRows - 1; i >= 0; --i)
        free(pGame->grid[i]);
    free(pGame->grid);
}

void printInitialGame(const Game *pGame)
{
    clear_screen();
    for (int i = 0; i != pGame->numRows; ++i)
    {
        for (int j = 0; j != pGame->numCols; ++j)
        {
            switch (pGame->grid[i][j])
            {
            case 'C':
                printf(BRIGHT_YELLOW_TEXT("C"));
                break;
            case 'B':
                printf(BLUE_TEXT("#"));
                break;
            case 'Y':
                printf(YELLOW_TEXT("#"));
                break;
            case 'R':
                printf(RED_TEXT("#"));
                break;
            case 'G':
                printf(GREEN_TEXT("#"));
                break;
            default:
                putchar(pGame->grid[i][j]);
                break;
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

void printScoreUpdate(const Game *pGame)
{
    move_cursor(pGame->numRows + 2, 7);
    printf("%d          ", pGame->score);
}

void printFoodUpdate(const Game *pGame)
{
    move_cursor(pGame->numRows + 3, 16);
    printf("%d          ", pGame->foodsCnt);
}

void moveGhosts(Game *pGame)
{
    for (int i = pGame->ghostCnt - 1; i >= 0; i--)
    {
        Coord original_coord = pGame->ghosts[i].pos;
        pGame->grid[original_coord.row][original_coord.col] = pGame->ghosts[i].itemBelow;
        move_cursor(original_coord.row, original_coord.col);
        printf("%c", pGame->grid[original_coord.row][original_coord.col]);
    }
    for (int i = 0; i < pGame->ghostCnt; i++)
    {
        Coord new_coord = moveOneStep(pGame->ghosts[i].pos, pGame->ghosts[i].direction);
        if (new_coord.row < 0 || new_coord.row >= pGame->numRows ||
            new_coord.col < 0 || new_coord.col >= pGame->numCols ||
            isWall(pGame->grid[new_coord.row][new_coord.col]))
        {
            pGame->ghosts[i].direction = oppositeDirection(pGame->ghosts[i].direction);
            new_coord = moveOneStep(pGame->ghosts[i].pos, pGame->ghosts[i].direction);
        }
        char new_itemBelow = pGame->grid[new_coord.row][new_coord.col];
        pGame->ghosts[i].itemBelow = new_itemBelow;
        pGame->ghosts[i].pos = new_coord;
        pGame->grid[new_coord.row][new_coord.col] = '@';
        move_cursor(new_coord.row, new_coord.col);
        printf("%c", pGame->grid[new_coord.row][new_coord.col]);
    }
}

Direction getPacmanMovement(void)
{
    if (kbhit())
    {
        switch (getch())
        {
        case 'w':
            return Up;
        case 's':
            return Down;
        case 'a':
            return Left;
        case 'd':
            return Right;
        }
    }
    return Idle;
}

void movePacman(Game *pGame)
{
    Direction tmp_direction = getPacmanMovement();
    Coord new_coord = moveOneStep(pGame->pacmanPos, tmp_direction);
    if (new_coord.row < 0 || new_coord.row >= pGame->numRows ||
        new_coord.col < 0 || new_coord.col >= pGame->numCols ||
        isWall(pGame->grid[new_coord.row][new_coord.col]))
    {
        return;
    }

    if (isFood(pGame->grid[new_coord.row][new_coord.col]))
    {
        pGame->score += 10;
        pGame->foodsCnt -= 1;
    }

    pGame->grid[pGame->pacmanPos.row][pGame->pacmanPos.col] = ' ';
    move_cursor(pGame->pacmanPos.row, pGame->pacmanPos.col);
    printf("%c", ' ');

    pGame->pacmanPos = new_coord;
    if (!isGhost(pGame->grid[new_coord.row][new_coord.col]))
    {
        pGame->grid[new_coord.row][new_coord.col] = 'C';
        move_cursor(new_coord.row, new_coord.col);
        printf(BRIGHT_YELLOW_TEXT("C"));
    }
}

bool pacmanDies(const Game *pGame)
{
    return isGhost(pGame->grid[pGame->pacmanPos.row][pGame->pacmanPos.col]);
}

bool gameEnds(Game *pGame)
{
    if (pacmanDies(pGame))
    {
        pGame->status = GS_Lose;
        return true;
    }
    if (pGame->foodsCnt == 0)
    {
        pGame->status = GS_Win;
        return true;
    }
    return false;
}

void runGame(Game *pGame)
{
    printInitialGame(pGame);
    pGame->status = GS_Running;
    int ticks = 0;
    while (1)
    {
        sleep_ms(MS_PER_TICK);
        ++ticks;
        movePacman(pGame);
        if (gameEnds(pGame))
            break;
        if (ticks == MS_PER_GHOST_TICK / MS_PER_TICK)
        {
            ticks = 0;
            --pGame->score;
            printScoreUpdate(pGame);
            printFoodUpdate(pGame);
            moveGhosts(pGame);
            if (gameEnds(pGame))
                break;
        }
    }
}

void runOneLevel(int level)
{
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
    return;
}

void runAllLevels(void)
{
    char path[100];
    Game game;
    int level = 0;
    while (level <= 3)
    {
        sprintf(path, "maps/level%d.txt", level);
        game = createGame(level, path);
        runGame(&game);
        assert(game.status == GS_Lose || game.status == GS_Win);
        move_cursor(game.numRows + 4, 0);
        if (game.status == GS_Lose)
        {
            printf("Pacman dies!");
            printf("                                       \n");
            printf("Press r to restart the level, or q to quit.\n");
        }
        else
        {
            printf("You win!");
            printf("                                       \n");
            printf("Press r to start the next level, or q to quit.\n");
            level++;
        }
        destroyGame(&game);
        while (true)
        {
            if (kbhit())
            {
                char if_continue = getch();
                if (if_continue == 'q')
                {
                    return;
                }
                else if (if_continue == 'r')
                {
                    break;
                }
            }
        }
    }
}

int main(int argc, char *argv[])
{
    prepare_game();
    if (argc > 1)
    {
        runOneLevel(atoi(argv[1]));
    }
    else
    {
        runAllLevels();
    }
    return 0;
}
