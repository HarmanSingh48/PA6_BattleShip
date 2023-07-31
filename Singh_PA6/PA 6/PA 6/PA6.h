/*
Name: Harmanpreet Singh
Class: CptS 121, Lab Section 23
File: PA6.h
Description: Header file for Battleship program
*/

#ifndef PA6_H
#define PA6_H
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define MAX_ROWS 10
#define MAX_COLS 10

#define CARRIER 'c'
#define CARRIER_LEN 5
#define CARR_INDEX 0

#define BATTLE 'b'
#define BATTLE_LEN 4
#define BATT_INDEX 1 

#define CRUISER 'r'
#define CRUISER_LEN 3
#define CRUS_INDEX 2

#define SUB 's'
#define SUB_LEN	3
#define SUB_INDEX 3

#define DESTR 'd'
#define DESTR_LEN 2
#define DESTR_INDEX 4

#define HIT '*'
#define MISS 'm'

#define HORIZONTAL 0
#define VERTICAL 1

#define PLAYER_1 1
#define PLAYER_2 2

//Structs

typedef struct stats {
	int hits;
	int misses;
	int total_shots;
	double hit_missRatio;
}Stats;

typedef struct coordinate {
	int x;
	int y;
}Coordinate;

typedef struct ship {
	Coordinate coordinate[5];
	int length;
	char symbol;
	char *name;
	int direction;
	int sunk;
}Ship;

//Function Prototypes
/*************************************************************
* Function: welcome_screen()								 *
* Description: 	Prints the inital welcome message for the	 *
* game, including the rules and menu						 *
* Input parameters: None									 *
* Returns: The player's choice of entering coordinates		 *
* 1 if manual or 2 if auto)									 *
* Preconditions: Program is initialized by the user			 *
* Postconditions: The welcome message and menu is printed	 *
* and the player's choice is returned to main				 *
*************************************************************/
int welcome_screen_menu(void);

/*************************************************************
* Function: init_game_board()								 *
* Description: 	Initializes the game board, making all the	 *
* entries in the 2-d array '~' char to represent water		 *
* Input parameters: 2-D array being used as the board, number*
* of rows, and number of columns							 *	
* Returns: None												 *
* Preconditions: A 2-D array is initialized in main to be	 *
* used as the game board									 *
* Postconditions: Every entry in the array is '~'		     *
*************************************************************/
void init_game_board(char game_board[][MAX_COLS], int rows, int cols);
/*************************************************************
* Function: init_game_board()								 *
* Description: 	Prints the contents of the game board and	 *
* the axis for the rows and columns							 *
* Input parameters: 2-D array being used as the board.		 *
* Returns: None												 *
* Preconditions: The game board has been initialized		 *
* Postconditions: The Game Board is printed				     *
*************************************************************/
void print_game_board(char game_board[][MAX_COLS], int player);
/*************************************************************
* Function: place_ships()									 *
* Description: 	Places the given ship type at the coordinates*
* given by the array of coordinates							 *
* Input parameters: The game board, array of ship,	 *
* length of the ship, and the type of ship					 *
* Returns: None												 *
* Preconditions: Coordinates have been validated			 *
* Postconditions: Game board is updated by changing chars	 *
* at the appropriate places									 *
*************************************************************/
void place_ship(char game_board[][MAX_COLS], Ship ship_arr[], int ship_index, char ship_type);
/*************************************************************
* Function: move_invalid_placement()						 *
* Description: Moves a ship from automatic placement if it	 *
* invalid placement from overlapping						 *
* Input parameters: The game board to place the ships on,	 *
* the array of ships, index of ship in ship array, ship type *
* Returns: None												 *
* Preconditions: Ship placed automatically is invalid		 *
* Postconditions: Ships are place in a valid spot		     *
*************************************************************/
void move_invalid_placement(char game_board[][MAX_COLS], Ship ship_arr[], int index, int direction);
/*************************************************************
* Function: manually_place_ships_on_board()					 *
* Description: 	Allows the player to manually place ships on *
* the board													 *
* Input parameters: The game board to place the ships on and *
* the array of ships										 *
* Returns: None												 *
* Preconditions: Board is initialized and user has selected	 *
* to place ships manually									 *
* Postconditions: Ships are place in desired locations	     *
*************************************************************/
void manually_place_ships_on_board(char game_board[][MAX_COLS], Ship ship_arr[]);
/*************************************************************
* Function: automatically_place_ships_on_board()			 *
* Description: automatically places ships on board			 *
* Input parameters: The game board to place the ships on and *
* the array of ships										 *
* Returns: None												 *
* Preconditions: Board is initialized and user has selected	 *
* to place ships automatically								 *
* Postconditions: Ships are place in random locations	     *
*************************************************************/
void automatically_place_ships_on_board(char game_board[][MAX_COLS], Ship ship_arr[], int index);
/*************************************************************
* Function: validate_coordinates()							 *
* Description: 	Checks if the coordinates given by the user	 *
* are valid, based on if the cells are available and if they *
* within the bounds of the board							 *
* Input parameters: The game board, the array of ships		 *
* and the size of the array									 *
* Returns: If the coordinates are valid(1) or not (0)		 *
* Preconditions: Coordinates are given by the user			 *
* Postconditions: 0 if not valid or 1 if valid	     *
*************************************************************/
int validate_coordinates(char game_board[][MAX_COLS], Ship ship_arr[], int size, int index);

/*************************************************************
* Function: check_shot()									 *
* Description: checks if a shot is a miss or a hit			 *
* Input parameters: The game board and the coordinate to check*
* Returns: 1 if the shot is a hit or 0 if shot is a miss	 *
* Preconditions: Coordinate is guessed by user and validate	 *
* Postconditions: Whether the shot is a hit or not is returned*
*************************************************************/
int check_shot(char game_board[][MAX_COLS], Coordinate coordinate);
/*************************************************************
* Function: get_geuss()										 *
* Description: gets the guess from the player				 *
* Input parameters: The game board and the coordinate struct *
* Returns: none												 *
* Preconditions: It is Player 1's turn						 *
* Postconditions: The coordinate is updated with the guess	 *
*************************************************************/
void get_guess(char game_board[][MAX_COLS], Coordinate *guess);
/*************************************************************
* Function: output_move()									 *
* Description: Prints player's guess and whether it was a	 *
* miss or not to the log file								 *
* Input parameters: Output file, hit or miss, the guess, and *
* which player made the move								 *
* Returns: none												 *
* Preconditions: A player has made a move					 *
* Postconditions: Log file is updated appropriately			 *
*************************************************************/
void output_move(FILE* outfile, int hit_miss, Coordinate guess, int player);
/*************************************************************
* Function: update_board()									 *
* Description: Updates the board of the opposing player after*
* a move													 *
* Input parameters: The gameboard, hit or miss, and the guess*
* coordinates												 *
* Returns: none												 *
* Preconditions: A player has made a move and it was checked *
* Postconditions: Game board is updated appropriately		 *
*************************************************************/
void update_board(char game_board[][MAX_COLS], int hit_miss, Coordinate guess);
/*************************************************************
* Function: check_if_sunk_ship()							 *
* Description: Checks if a ship has been sunk				 *
* Input parameters: The gameboard and the ship array 		 *
* Returns: Number of ships that have been sunk				 *
* Preconditions: Game board has ship on it					 *
* Postconditions: Number of sunk ships is returned			 *
*************************************************************/
int check_if_sunk_ship(char game_board[][MAX_COLS], Ship ship_arr[]);
/*************************************************************
* Function: is_winner()										 *
* Description: Checks if there exists a winner				 *
* Input parameters: Number of ships sunk by both players	 *
* Returns: 0 if there is no winner, 1 if there is			 *
* Preconditions: none										 *
* Postconditions: 0 or 1 is returned						 *
*************************************************************/
int is_winner(int sunk_by_P1, int sunk_by_P2);

void output_stats(FILE *outifle, int P1_total_shots, int P2_total_shots, int P1_total_hits, int P2_total_hits);


#endif // !PA6_H
