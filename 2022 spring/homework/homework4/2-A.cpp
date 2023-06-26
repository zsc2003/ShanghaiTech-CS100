#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define FOOD_SCORE 10
#define MAX_GHOSTS 30
#define CAPSULE_DURATION 10
#define CAPSULE_SCORE 50
#define GHOST_SCORE 200

typedef enum gameState{losing, onGoing, winning} GameState;
typedef enum direction{up, down, left, right, idle} Direction;

typedef struct Ghost {
    int pos_x,pos_y;//position of a ghost
    int direc;//direction 1 for up,2 for down, 3 for left, 4 for right
} Ghost;


typedef struct game {
    char** grid;     // a 2-dimensional array of characters to display the game;
    int rows;        // number of rows of the grid;
    int columns;     // number of columns of the grid;
    int posrow,poscolumn;//the position of the 'C'
    int foodCount;   // number of remaining food in the game;
    int score;       // current score;
    GameState state; // the state of the game, one of losing, onGoing, or winning.
	int ghost_num;//number of ghosts
	Ghost* ghost;
} Game;

/* Creates a new game, with given rows and columns.
 * The top-left corner is at row 0 and column 0.
 * Boundary is not included in either rows or columns.
 * You should dynamically allocate space for a Game pointer,
 * dynamically allocate a 2-dimensional char grid,
 * and initialize any other value in your Game structure.
 * Return that pointer to the game you created.
 */
Game* NewGame(int rows, int columns) {
	Game *newgame=(Game*)malloc(sizeof(Game));
	newgame->columns=columns;
	newgame->rows=rows;
	newgame->posrow=-100,newgame->poscolumn=-100;
	newgame->foodCount=0;
	newgame->score=0;
	newgame->state=winning;
	newgame->grid=(char**)malloc(sizeof(char*)*rows);
	for(int i=0;i<rows;i++)
		newgame->grid[i]=(char*)malloc(sizeof(char)*columns);
	for(int i=0;i<rows;i++)
		for(int j=0;j<columns;j++)
			newgame->grid[i][j]=' ';
//part B	
	newgame->ghost_num=0;
	newgame->ghost=(Ghost*)malloc(sizeof(Ghost)*MAX_GHOSTS);
	
    return newgame;
}

/* Ends your game by freeing any memory
 * you dynamically allocated.
 * After that, free the "game" pointer,
 * since it is also dynamically created.
 */

void EndGame(Game* game) {
	for(int i=0;i<game->rows;++i)
		free(game->grid[i]);
	free(game->grid);
	free(game->ghost);
	free(game);
    return; // This is incorrect.
}

/* Adds a wall to the game, at row = r, column = c.
 * Walls should be added only to an empty place.
 * After you successfully add a wall, 
 * you should modify the "grid" to represent
 * the wall by '#'. Then, return true.
 * Return false on failures.
 */

bool AddWall(Game* game, int r, int c) {
	if(r<0||(r>=game->rows)||c<0||(c>=game->columns))
		return false;
	if(game->grid[r][c]!=' ')
		return false; 
	game->grid[r][c]='#';
    return true; // This is not always correct.
}

/* Adds a food to the game, at row = r, column = c.
 * Foods should be added only to an empty place.
 * After you successfully add a food, 
 * you should modify the "grid" to represent
 * the food by '.', also update the "foodCount"
 * correctly. Then, return true.
 * Return false on failures.
 */

bool AddFood(Game* game, int r, int c) {
	if(r<0||r>=game->rows||c<0||c>=game->columns)
		return false;
	if(game->grid[r][c]!=' ')
		return false;
	if(game->foodCount==0)
		game->state=onGoing;
	game->grid[r][c]='.';
	game->foodCount++; 
    return true; // This is not always correct.
}

/* Adds a Pacman to the game! At row = r, column = c.
 * If there is already a Pacman, return false.
 * Pacman should be added only to an empty place.
 * After you successfully add a Pacman,
 * you should modify the "grid" to represent
 * the Pacman by 'C'. Then, return true.
 * Return false on failures.
 */

bool AddPacman(Game* game, int r, int c) {
	if(r<0||r>=game->rows||c<0||c>=game->columns)
		return false;
	if(game->grid[r][c]!=' ')
		return false;
	if(game->posrow!=-100)
		return false;
	game->grid[r][c]='C';
	game->posrow=r,game->poscolumn=c;
    return true; // This is not always correct.
}

/* Moves Pacman in the given direction.
 * The direction will always be valid.
 * Pacman should stay still if this move
 * will let it hit a wall or boundaries.
 * No matter what move is performed, the
 * game's score should decrease by 1.
 * 
 * If Pacman eats a food, the game's score
 * should increase by FOOD_SCORE. If that 
 * food is the last one in the game, you
 * should mark the game's state as "winning".
 *
 * 
 * FOR PART B:
 * 
 * Pacman is allowed to move onto a grid
 * with a ghost. In that case, Pacman loses,
 * and will not be able to eat the food or capsule
 * under that ghost, if any. Score should
 * still decrease by 1, and you should mark the
 * game's state as "losing".
 * 
 * If Pacman eats a capsule, the game's score
 * should increase by CAPSULE_SCORE, and Pacman
 * will gain CAPSULE_DURATION = 10 turns of 
 * superpower. If that capsule is the last food 
 * in the game, mark the game's state as "winning".
 * 
 */

void MovePacman(Game* game, Direction direction){
//	if(game->state==winning)
//		return;
	game->score--;
	//direction{up, down, left, right, idle}
	int newrow=game->posrow,newcolumn=game->poscolumn;
	if(direction==up)newrow--;
	else if(direction==down)newrow++;
	else if(direction==left)newcolumn--;
	else if(direction==right)newcolumn++;
	if(newrow<0||newrow>=game->rows||newcolumn<0||newcolumn>=game->columns||game->grid[newrow][newcolumn]=='#')
		return;

	if(game->grid[newrow][newcolumn]=='.')
	{
		game->score+=FOOD_SCORE;
		game->foodCount--;
		game->grid[newrow][newcolumn]=' ';
	//	if(game->foodCount==0)
	//		game->state=winning;
	//----why?------- 
	}
	
	
	
	




	game->grid[game->posrow][game->poscolumn]=' ';
	game->grid[newrow][newcolumn]='C';
	game->posrow=newrow,game->poscolumn=newcolumn;	
	
	//ghost , CAPSUL to be continued...
	return;
}

//////////////////////// PART B ////////////////////////


/* Adds a ghost to the game,
 * at row = r, column = c, with given initial direction.
 * you should modify the "grid" to represent the ghost by '@'.
 * Ghosts can be added to an empty place or on a food.
 * For the latter case, the ghost will cover that food on display,
 * represented also by an '@'. 
 * That food must still exist, and that grid should 
 * display '.' when the ghost leaves.
 */
bool AddGhost(Game* game, int r, int c, Direction direction) {
    
	return false; // This is not always correct.
}

/* Moves all ghosts in their own directions.
 * Ghosts should be moved in the order they were added.
 * If a ghost will bump into a wall, another ghost, or a boundary,
 * Its direction will reverse, and it will try to move
 * in the new direction immediately this turn.
 * If it bumps into another wall/ghost/boundary,
 * it won't move for this turn.
 */
void MoveGhosts(Game* game) {
    return; // This is incorrect.
}

/* Adds a capsule to the game, at row = r, column = c.
 * Capsules should be added only to an empty place,
 * or added to a cell with food to upgrade that food.
 * After you successfully add a capsule, return true.
 * Return false on failures.
 *
 * Capsules will grant Pacman CAPSULE_SCORE = 50 and
 * CAPSULE_DURATION = 10 turns of superpower when eaten.
 * 
 * When with superpower, scared ghosts will be displayed in 'x',
 * and will be unable to move every other turn. 
 * (they can move on the turn when Pacman eats a capsule.)
 * When Pacman eats a scared ghost, it earns GHOST_SCORE = 200.
 * 
 * Pacman's superpower activates immediately when it eats a 
 * capsule, and counts down immediately after Pacman's turn,
 * starting from its next turn. In other words, Pacman's superpower
 * ends after 10 turns at the same moment of eating a capsule.
 */
bool AddCapsule(Game *game, int r, int c) {
    return false; // This is not always correct.
}


///////////////////////////////////////////////////////////////////////////////
/////////////////// Please submit all code above to OJ ////////////////////////
///////////////////////////////////////////////////////////////////////////////

// Declarations of provided functions
void PlayGame(Game* game);

int main(){
    Game* game = NewGame(8, 8);
	AddFood(game,1,1);AddFood(game,1,2);AddFood(game,1,3);AddFood(game,1,4);
	AddFood(game,5,5);
	AddFood(game,2,2);
	AddWall(game,7,7);
	AddFood(game,4,1);AddFood(game,4,2);AddFood(game,4,3);AddFood(game,4,4);
	AddPacman(game,3,3);
	AddPacman(game,2,2);
	AddPacman(game,1,5);
	AddWall(game,4,4);
	AddFood(game,0,0);
	AddWall(game,1,1);
	// Add walls, foods, and pacman here.
	
	//第二题5678的点地图行=列
    
	PlayGame(game);
}

///////////////////////////////////////////////////////////////////////////////
//////////////////////// DO NOT MODIFY ANY CODE BELOW! ////////////////////////
///////////////////////////////////////////////////////////////////////////////

/* This function prints the game grid with boundary,
 * and any message depending on game state.
 * Please make sure that, after any action is done,
 * game->state, game->score, and game->foodCount
 * are correctly updated.
 */
#ifdef _WIN32

#include <windows.h>

#endif // _WIN32

void PrintGame(Game* game){
    if(!game || !game->grid) return;

// If Windows, clear console.
#ifdef _WIN32 
    system("cls");
#else
// Clears terminal screen
    fflush(stdout);
    system("clear");
#endif
    
    // The game grid
    printf(" ");
    for(int i = 0; i < game->columns; i++)
        printf("_");
    printf(" \n");

    for(int i = 0; i < game->rows; i++){
        printf("|");
        for(int j = 0; j < game->columns; j++)
            printf("%c", game->grid[i][j]);
        printf("|\n");
    }
    printf("\\");
    for(int i = 0; i < game->columns; i++)
        printf("-");
    printf("/\n\n");

    // Messages on different states
    switch(game->state){
    case losing:
        printf("Pacman died! Your score: %d\n", game->score);
        break;
    case onGoing:
        printf("Score: %d\n", game->score);
        printf("There are %d foods remaining!\n", game->foodCount);
        printf("Pacman wants food! (control by w/a/s/d/i, confirm by Enter)\n\n");
        break;
    case winning:
        printf("Victory! Your score: %d\n", game->score);
        break;
    default:
        printf("ERROR: invalid game state!\n");
    }
}

/* Plays the game, and calls EndGame on winning or losing.
 */
void PlayGame(Game* game){
    
    // Prints the initial grid
    PrintGame(game);

    // Main loop of game. Terminates when the game ends.
    while(true){
        // We only care about one charater, but should eat the whole line of input.
        char input[127];
        input[0] = '\0';
        scanf("%[^\n]", input);
        // Handles the '\n'.
        getchar();
        Direction direction;
        switch(input[0]){
        case 'w':
        case 'W':
            direction = up; break;
        case 'a':
        case 'A':
            direction = left; break;
        case 's':
        case 'S':
            direction = down; break;
        case 'd':
        case 'D':
            direction = right; break;
        case 'i':
        case 'I':
            direction = idle; break;
        default:
            PrintGame(game);
            continue;
        }

        // Pacman moves first.
        MovePacman(game, direction);

        // Wins if Pacman eats all the food, loses if Pacman bumps into a ghost.
        if(game->state != onGoing){
            break;
        }
        
        // If you haven't implemented ghosts, this does nothing.
        MoveGhosts(game);

        // Loses if a ghost kills Pacman.
        if(game->state != onGoing){
            break;
        }
        PrintGame(game);
    }

    // End game message
    PrintGame(game);
    printf("Press Enter to exit.\n");
    EndGame(game);
    getchar();
}
