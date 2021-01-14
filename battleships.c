//
// Created by Shimmy on 8/12/2018.
//
/**
 * @file battleships.c
 * @author  Shimon Balsam <shimon.balsam@mail.huji.ac.il>
 * @version 1.0
 * @date 14 Aug 2018
 *
 * @brief System to run battleships functions.
 *
 * @section DESCRIPTION
 * The system runs a the backround functions of the battleship game.
 * Input  : None.
 * Process: The different functions are called on from the main in the battleships_game.c.
 * Output : Prints out the board at every round when called upon by main in battleships_game.c.
 */

// ------------------------------ includes ------------------------------
#include "battleships.h"
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <time.h>

// -------------------------- const definitions -------------------------

// @brief A macro that sets the value of a horizontal ship.
#define HORIZONTAL 1

// @brief A macro that sets the value of a vertical ship.
#define VERTICAL 0

// @brief A macro that sets the size of the carrier ship.
#define CARRIER_SIZE 5

// @brief A macro that sets the size of the scouter ship.
#define SCOUTER_SIZE 4

// @brief A macro that sets the size of the missile ship.
#define MISSILE_SIZE 3

// @brief A macro that sets the size of the submarine ship.
#define SUBMARINE_SIZE 3

// @brief A macro that sets the size of the destroyer ship.
#define DESTROYER_SIZE 2

// @brief A macro that sets the placing of the carrier ship amongst the ships array.
#define CARRIER 0

// @brief A macro that sets the placing of the scouter ship amongst the ships array.
#define SCOUTER 1

// @brief A macro that sets the placing of the missile ship amongst the ships array.
#define MISSILE 2

// @brief A macro that sets the placing of the submarine ship amongst the ships array.
#define SUBMARINE 3

// @brief A macro that sets the placing of the destroyer ship amongst the ships array.
#define DESTROYER 4

// @brief A macro that sets the size of the ships array.
#define AMOUNT_OF_SHIPS 5

// @brief A macro that sets hit symbol as shown to the user on the board.
#define HIT_SYMBOL 'x'

// @brief A macro that sets miss symbol as shown to the user on the board.
#define MISS_SYMBOL 'o'

// @brief A macro that sets empty tile symbol as shown to the user on the board.
#define EMPTY_SYMBOL '_'

// @brief A macro that sets the value of a hit and sunk return.
#define SUNK_RETURN 1

// @brief A macro that sets the value of a hit return.
#define HIT_RETURN 2

// @brief A macro that sets the value of a missed hit return.
#define MISS_RETURN 0

// @brief A macro that sets the value of an already hit return.
#define ALREADY_HIT -1

// @brief A macro that sets the value of an already missed return.
#define ALREADY_MISS -2

// @brief A macro that sets the ascii value of lowercase 'a'.
#define SMALL_A 'a'

// @brief A macro that sets the value of a tile which has a ship on it, in the background.
#define HAS_SHIP 1

// @brief A macro that sets the value of a tile which doesn't have a ship on it, in the background.
#define NO_SHIP 0


// ------------------------------ structs -----------------------------
/**
 * creates a struct of type Ship with parameters:
 * size: size of ship.
 * hits_counter: how many hits left until ship is sunk.
 * direction: is the direction of the ship vertical or horizontal.
 * x: the ships starting point on the horizontal axis.
 * y: the ships starting point on the vertical axis.
 */
typedef struct Ship
{
    int size, hits_counter, direction, x, y;
}Ship;

/**
 * creates a struct of type Tile with parameters:
 * content: the character of the tile shown to user, equivalent to hit/miss/empty.
 * has_ship: a binary flag stating if the tile has a ship placed on it or not.
 */
typedef struct Tile
{
    char content;
    int has_ship;
}Tile;


// ------------------------------ functions -----------------------------

/**
 * Allocates place in the memory for the Board, and builds each Tile in board with it's needed
 * struct parameters.
 * @param size the size of the board.
 * @return the board.
 */
Tile** makeBoard(const int size)
{
    Tile** arr = (Tile**)malloc(size*sizeof(Tile*));
    if (arr == NULL)
    {
        return NULL;
    }
    for(int i = 0; i < size; i++)
    {
        arr[i] = (Tile*)malloc(size*sizeof(Tile));
        if (arr[i] == NULL)
        {
            return NULL;
        }
        for (int j = 0; j < size; j++)
        {
            Tile t = {EMPTY_SYMBOL, NO_SHIP};
            arr[i][j] = t;
        }
    }
    return arr;
}

/**
 * prints the boards state.
 * @param arr the board.
 * @param size the bpard size.
 */
void printBoard(Tile** arr, const int size)
{
    printf(" ");
    int i, j, k;
    for (k = 1; k <= size; k++)
    {
        printf(",%d", k);
    }
    printf("\n");
    char line = SMALL_A;
    for (i = 0; i<size; i++)
    {
        printf("%c ", line);
        line++;
        for(j = 0; j < size; j++)
        {
            printf("%c ", arr[i][j].content);
        }
        printf("\n");
    }
}

/**
 * creates a single Ship with needed structs parameters. Finds random place on board for ship
 * and updates the boards tile's which the ships sits on acordingly.
 * @param board tje board
 * @param boardSize the board size
 * @param shipSize the ship's size
 * @return the ship.
 */
Ship makeShip(Tile** board, const int boardSize, const int shipSize)
{
    Ship ship;
    srand((unsigned int)time(NULL));
    ship.size = shipSize;
    ship.hits_counter = shipSize;
    ship.x = 0;
    ship.y = 0;
    int flag = 0;
    while(flag == 0)
    {
        ship.x = rand() % boardSize;
        ship.y = rand() % boardSize;
        ship.direction = rand() % 2;
        flag = 1;
        if (ship.direction == VERTICAL)
        {
            for (int i = 0; i < shipSize; i++)
            {
                if ((ship.x + i) >= boardSize || board[ship.x + i][ship.y].has_ship != NO_SHIP)
                {
                    flag = 0;
                    break;
                }
            }
        }
        else
        {
            for (int i = 0; i < shipSize; i++)
            {
                if ((ship.y + i) >= boardSize || board[ship.x][ship.y + i].has_ship != NO_SHIP)
                {
                    flag = 0;
                    break;
                }
            }
        }
    }
    if (ship.direction == VERTICAL)
    {
        for (int m = 0; m < shipSize; m++)
        {
            board[ship.x + m][ship.y].has_ship = HAS_SHIP;
        }
    }
    else
    {
        for (int m = 0; m < shipSize; m++)
        {
            board[ship.x][ship.y + m].has_ship = HAS_SHIP;
        }
    }
    return ship;
}

/**
 * Adds all the ships of the game to the board.
 * @param board the board.
 * @param boardSize the bpard size.
 * @return an array of all the ships.
 */
Ship* addShips(Tile** board, const int boardSize)
{
    Ship* ships = (Ship*)malloc(AMOUNT_OF_SHIPS*sizeof(Ship));
    ships[CARRIER] = makeShip(board, boardSize, CARRIER_SIZE);
    ships[SCOUTER] = makeShip(board, boardSize, SCOUTER_SIZE);
    ships[MISSILE] = makeShip(board, boardSize, MISSILE_SIZE);
    ships[SUBMARINE] = makeShip(board, boardSize, SUBMARINE_SIZE);
    ships[DESTROYER] = makeShip(board, boardSize, DESTROYER_SIZE);
    return ships;
}

/**
 * checks the user's input vs the placing of ships on board and answers acordingly.
 * @param board the board
 * @param x the letter given by user meaning row.
 * @param y the number given by user meaning column.
 * @param ships the array of ships.
 * @return -1 if already hit, -2 if already missed, 0 if miss, 1 if hit and sunk, 2 if hit.
 */
int checkHit(Tile** board, int x, int y, Ship* ships)
{
    if (board[x][y].content != EMPTY_SYMBOL)
    {
        if (board[x][y].content == HIT_SYMBOL)
        {
            return ALREADY_HIT;
        }
        else
        {
            return ALREADY_MISS;
        }
    }
    if (board[x][y].has_ship == NO_SHIP)
    {
        board[x][y].content = MISS_SYMBOL;
        return MISS_RETURN;
    }
    for (int i = 0; i < AMOUNT_OF_SHIPS; i++)
    {
        if (ships[i].direction == VERTICAL)
        {
            if (y == ships[i].y && x >= ships[i].x && x < ships[i].x + ships[i].size)
            {
                ships[i].hits_counter--;
                board[x][y].content = HIT_SYMBOL;
                if (ships[i].hits_counter == 0)
                {
                    return SUNK_RETURN;
                }
                else
                {
                    return HIT_RETURN;
                }
            }
        }
        else
        {
            if (x == ships[i].x && y >= ships[i].y && y < ships[i].y + ships[i].size)
            {
                ships[i].hits_counter--;
                board[x][y].content = HIT_SYMBOL;
                if (ships[i].hits_counter == 0)
                {
                    return SUNK_RETURN;
                }
                else
                {
                    return HIT_RETURN;
                }
            }
        }
    }
    return 0;
}