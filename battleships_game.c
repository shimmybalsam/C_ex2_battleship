//
// Created by Shimmy on 8/12/2018.
//
/**
 * @file battleships_game.c
 * @author  Shimon Balsam <shimon.balsam@mail.huji.ac.il>
 * @version 1.0
 * @date 14 Aug 2018
 *
 * @brief System to play a game of battleships.
 *
 * @section DESCRIPTION
 * The system runs a single game of battleships.
 * Input  : Board size and itterative move input.
 * Process: Scans the board size input, builds a board of that size with hidden ships placed
 * randomly in the background, prints out said board, and in an iterative manner, at every turn,
 * scans player's move input and updates board acordingly.
 * Output : Updated bored and relative message at begining of game and after every move.
 */

// ------------------------------ includes ------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include "battleships.h"

// -------------------------- const definitions -------------------------

// @brief A macro that sets the error message for illegal board size input.
#define ILLEGAL_BOARD_SIZE "Illegal board size, needs to be an int between 5 and 26.\n"

// @brief A macro that sets the error message for an illegal move input.
#define ILLEGAL_INPUT "Invalid move, try again\n"

// @brief A macro that sets the size of the carrier Ship.
#define CARRIER_SIZE 5

// @brief A macro that sets the size of the scouter Ship.
#define SCOUTER_SIZE 4

// @brief A macro that sets the size of the missile Ship.
#define MISSILE_SIZE 3

// @brief A macro that sets the size of the submarine Ship.
#define SUBMARINE_SIZE 3

// @brief A macro that sets the size of the destroyer Ship.
#define DESTROYER_SIZE 2

// @brief A macro that maximum size of hits needed to destroy all ships.
#define MAX_HITS 17

// @brief A macro that sets the error message for not enough memory allocation.
#define MEMORY_FAULT "Not enough memory, sorry!"

// @brief A macro that sets the minimum size of board allowed.
#define MIN_BOARD_SIZE 5

// @brief A macro that sets the maximum size of board allowed.
#define MAX_BOARD_SIZE 26

// @brief A macro that sets the Game over message.
#define GAME_OVER_MSG "Game over"

// @brief A macro that sets the Hit message.
#define HIT_MSG "Hit!"

// @brief A macro that sets the Miss message.
#define MISS_MSG "Miss"

// @brief A macro that sets the Hit and sunk message.
#define SUNK_MSG "Hit and sunk."

// @brief A macro that sets the Already been hit message.
#define ALREADY_HIT_MSG "Already been hit."

// @brief A macro that sets the value of ending due to error return.
#define ERR_RETURN 1

// @brief A macro that sets the value of legal ending return.
#define LEGAL_RETURN 0

// @brief A macro that sets the value of a missed hit return.
#define MISS_RETURN 0

// @brief A macro that sets the value of a hit return.
#define HIT_RETURN 2

// @brief A macro that sets the value of hit and sunk return.
#define SUNK_RETURN 1

// @brief A macro that sets the value of already been hit return.
#define ALREADY_HIT_RETURN -1

// @brief A macro that sets the value of already been missed return.
#define ALREADY_MISS_RETURN -2

// @brief A macro that sets the ascii value of lowercase 'a'.
#define SMALL_A 'a'

// @brief A macro that sets the message to receive board size input.
#define GET_BOARDSIZE_MSG "enter board size: "

// @brief A macro that sets the ready to play message.
#define READY_MSG "Ready to play\n"

// @brief A macro that sets the message to receive coordinates input.
#define GET_COORDINATES_MSG "enter coordinates: "

// ------------------------------ functions -----------------------------

/**
 * Scans the board size input, builds a board of that size with hidden ships placed
 * randomly in the background, prints out said board, and in an iterative manner, at every turn,
 * scans player's move input and updates board acordingly.
 * @return 1 if the input at any round is illegal, otherwaise returns 0 at the end of the game.
 */
int main()
{
    int allHits = 0;
    int boardSize;
    printf("%s", GET_BOARDSIZE_MSG);
    if (scanf("%d", &boardSize) != 1 || boardSize < MIN_BOARD_SIZE || boardSize > MAX_BOARD_SIZE)
    {
        fprintf(stderr, ILLEGAL_BOARD_SIZE);
        return ERR_RETURN;
    }
    else
    {
        Tile** board = makeBoard(boardSize);
        if (board == NULL)
        {
            fprintf(stderr, MEMORY_FAULT);
            return ERR_RETURN;
        }
        Ship* ships = addShips(board, boardSize);
        printf("%s", READY_MSG);
        printBoard(board, boardSize);
        char input[5];
        while (allHits < MAX_HITS)
        {
            printf("%s", GET_COORDINATES_MSG);
            scanf("%s", input);
            if (strcmp(input, "exit") == 0)
            {
                printf("%s", GAME_OVER_MSG);
                return 0;
            }
            else if (strlen(input) != 1)
            {
                printf(ILLEGAL_INPUT);
            }
            else
            {
                int x = (int) input[0] - SMALL_A;
                int y;
                if(scanf("%d", &y) != 1)
                {
                    printf(ILLEGAL_INPUT);
                    continue;
                }
                if (x > boardSize || x < 0 || y > boardSize || y <= 0)
                {
                    printf(ILLEGAL_INPUT);
                    continue;
                }
                y--;
                int hit = checkHit(board, x, y, ships);
                if (hit == MISS_RETURN || hit == ALREADY_MISS_RETURN)
                {
                    printf("%s\n", MISS_MSG);
                }
                else if (hit == SUNK_RETURN)
                {
                    printf("%s\n", SUNK_MSG);
                    allHits++;
                }
                else if (hit == HIT_RETURN)
                {
                    printf("%s\n", HIT_MSG);
                    allHits++;
                }
                else if (hit == ALREADY_HIT_RETURN)
                {
                    printf("%s\n", ALREADY_HIT_MSG);
                }
                printBoard(board, boardSize);
            }
        }
        printf("%s", GAME_OVER_MSG);
        for (int i = 0; i < boardSize; i++)
        {
            free(board[i]);
        }
        free(board);
        free(ships);
    }
    return LEGAL_RETURN;
}