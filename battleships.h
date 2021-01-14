//
// Created by Shimmy on 8/12/2018.
//

/**
 * @file battleships.c
 * @author  Shimon Balsam <shimon.balsam@mail.huji.ac.il>
 * @version 1.0
 * @date 14 Aug 2018
 *
 * @brief System to declare battleships functions to be implemented in battleships.c and
 * call upon from battlehships_game.c.
 *
 * @section DESCRIPTION
 * The system declares the background functions of the battleship game which will be implemented
 * in battleships.c.
 * Input  : None.
 * Process: Declarations only.
 * Output : None.
 */

#ifndef EX2_BATTLESHIPS_H
#define EX2_BATTLESHIPS_H

/**
 * creates a struct of type Tile with parameters:
 * content: the character of the tile shown to user, equivalent to hit/miss/empty.
 * has_ship: a binary flag stating if the tile has a ship placed on it or not.
 */typedef struct Tile Tile;

/**
 * creates a struct of type Ship with parameters:
 * size: size of ship.
 * hits_counter: how many hits left until ship is sunk.
 * direction: is the direction of the ship vertical or horizontal.
 * x: the ships starting point on the horizontal axis.
 * y: the ships starting point on the vertical axis.
 */
typedef struct Ship Ship;

/**
 * Allocates place in the memory for the Board, and builds each Tile in board with it's needed
 * struct parameters.
 * @param size the size of the board.
 * @return the board.
 */Tile** makeBoard(int size);

/**
 * prints the boards state.
 * @param arr the board.
 * @param size the bpard size.
 */
void printBoard(Tile** arr, int size);

/**
 * creates a single Ship with needed structs parameters. Finds random place on board for ship
 * and updates the boards tile's which the ships sits on acordingly.
 * @param board tje board
 * @param boardSize the board size
 * @param shipSize the ship's size
 * @return the ship.
 */
Ship makeShip(Tile** board, int boardSize, int shipSize);

/**
 * Adds all the ships of the game to the board.
 * @param board the board.
 * @param boardSize the bpard size.
 * @return an array of all the ships.
 */
Ship* addShips(Tile** board, int boardSize);

/**
 * checks the user's input vs the placing of ships on board and answers acordingly.
 * @param board the board
 * @param x the letter given by user meaning row.
 * @param y the number given by user meaning column.
 * @param ships the array of ships.
 * @return -1 if already hit, -2 if already missed, 0 if miss, 1 if hit and sunk, 2 if hit.
 */
int checkHit(Tile** board, int x, int y, Ship* ships);

#endif //EX2_BATTLESHIPS_H
