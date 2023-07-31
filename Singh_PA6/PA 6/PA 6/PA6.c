/*
Name: Harmanpreet Singh
Class: CptS 121, Lab Section 23
File: PA6.c
Description: Function definitions to run Battleship program
*/

#include "PA6.h"
//Function Definitions

int welcome_screen_menu(void) {
	char rules[25] = { "Here are the rules:"};

	int option = 0;


	printf("Welcome to Battleship:\n");
	Sleep(200);


	for (int i = 0; rules[i] != '\0'; i++) {
		printf("%c", rules[i]);
		Sleep(50);
	}


	printf("\n1. There are two players: You(Player 1) and the computer(Player 2).\n");
	Sleep(50);
	printf("2. You will decide whether you want to place the ships manually or have them be placed automatically.\n");
	Sleep(50);
	printf("3. It will be decided randomly whether you go first or the computer does.\n");
	Sleep(50);
	printf("4. When it is your turn, you will enter where you want to hit. It will be indicated whether you hit something or you missed.\n");
	Sleep(50);
	printf("5. You and the other player will alternate guessing the places to hit. You cannot guess the same coordinates twice.\n");
	Sleep(50);
	printf("6. The game will continue until one player has sunk all the other player's ships.\n");
	Sleep(50);
	printf("7. To check your stats for the game that you just played, check the 'battleship.log' file.\n");
	Sleep(50);


	printf("Press Enter to continue");
	getchar();
	system("cls");


	printf("Select one of the following: \n1. Enter the coordinated manually\n2. Let the coordinates be determined automatically\n");
	scanf("%d", &option);
	return option;
}

void init_game_board(char game_board[][MAX_COLS], int rows, int cols) {
	int row_index = 0, col_index = 0;
	for (; row_index < rows; row_index++) {
		for (col_index = 0; col_index < cols; col_index++) {
			game_board[row_index][col_index] = '~';
		}
	}
}

void print_game_board(char game_board[][MAX_COLS], int player) {
	int row_index = 0, col_index = 0;
	if (player == PLAYER_1) {
		printf("  0 1 2 3 4 5 6 7 8 9\n");
		for (; row_index < MAX_ROWS; row_index++) {
			printf("%d ", row_index);
			for (col_index = 0; col_index < MAX_COLS; col_index++) {
				printf("%c ", game_board[row_index][col_index]);
			}
			putchar('\n');
		}
	}
	else
	{
		printf("  0 1 2 3 4 5 6 7 8 9\n");
		for (; row_index < MAX_ROWS; row_index++) {
			printf("%d ", row_index);
			for (col_index = 0; col_index < MAX_COLS; col_index++) {
				if (game_board[row_index][col_index] == CARRIER || game_board[row_index][col_index] == BATTLE || game_board[row_index][col_index] == CRUISER || game_board[row_index][col_index] == SUB || game_board[row_index][col_index] == DESTR) {
					printf("~ ");
				}
				else if(game_board[row_index][col_index] == HIT || game_board[row_index][col_index] == MISS|| game_board[row_index][col_index] == '~')
				{
					printf("%c ", game_board[row_index][col_index]);
				}
			}
			putchar('\n');
		}
	}
}

void place_ship(char game_board[][MAX_COLS], Ship ship_arr[], int ship_index, char ship_type) {
	for (int i = 0; i < ship_arr[ship_index].length; i++) {
		game_board[ship_arr[ship_index].coordinate[i].y][ship_arr[ship_index].coordinate[i].x] = ship_type;
	}
}

void move_invalid_placement(char game_board[][MAX_COLS], Ship ship_arr[], int index, int direction) {
	Coordinate random_cell = { 0, 0 };
	int open_cells = 0;

	random_cell.x = rand() % (MAX_ROWS - ship_arr[index].length + 1);
	random_cell.y = rand() % (MAX_COLS - ship_arr[index].length + 1);

	ship_arr[index].coordinate[0].x = random_cell.x;
	ship_arr[index].coordinate[0].y = random_cell.y;

	if (direction == VERTICAL) {
		for (int i = 1; i < ship_arr[index].length; i++) {
			random_cell.y = random_cell.y + 1;
			ship_arr[index].coordinate[i].x = random_cell.x;
			ship_arr[index].coordinate[i].y = random_cell.y;
		}
	}
	else
	{
		for (int i = 1; i < ship_arr[index].length; i++) {
			random_cell.x = random_cell.x + 1;
			ship_arr[index].coordinate[i].x = random_cell.x;
			ship_arr[index].coordinate[i].y = random_cell.y;
		}
	}
	if (!validate_coordinates(game_board, ship_arr, ship_arr[index].length, index)) {
		move_invalid_placement(game_board, ship_arr, index, direction);
	}
}

void manually_place_ships_on_board(char game_board[][MAX_COLS], Ship ship_arr[]) {
	char position[11] = " ";
	//Coordinate Coor_arr[5];
	int valid = 0;
	//Carrier
	while (strlen(position) != 10 && !valid) {
		ship_arr[CARR_INDEX].name = "Carrier";
		ship_arr[CARR_INDEX].sunk = -1;
		printf("Enter the 5 cells to place the Carrier(c) on:\n");
		scanf("%s", &position);

		for (int i = 0, j = 0; (i + 1) < (CARRIER_LEN*2); i += 2, j++) {
			ship_arr[CARR_INDEX].coordinate[j].y = (position[i]) - '0';
			ship_arr[CARR_INDEX].coordinate[j].x = (position[i + 1]) - '0';
		}
		valid = validate_coordinates(game_board, ship_arr, CARRIER_LEN, CARR_INDEX);
	}
	//Determines if the the Ship is horizontal or vertical depending on the coordinates
	if (ship_arr[CARR_INDEX].coordinate[0].y == ship_arr[CARR_INDEX].coordinate[1].y) {
		ship_arr[CARR_INDEX].direction = HORIZONTAL;
	}
	else {
		ship_arr[CARR_INDEX].direction = VERTICAL;
	}
	place_ship(game_board, ship_arr, CARR_INDEX, CARRIER);
	valid = 0;
	//Battleship
	ship_arr[BATT_INDEX].name = "Battleship";
	ship_arr[BATT_INDEX].sunk = -1;
	while (strlen(position) != 8 && !valid) {
		printf("Enter the 4 cells to place the Battleship(b) on:\n");
		scanf("%s", &position);

		for (int i = 0, j = 0; (i + 1) < (BATTLE_LEN * 2); i += 2, j++) {
			ship_arr[BATT_INDEX].coordinate[j].y = (position[i]) - '0';
			ship_arr[BATT_INDEX].coordinate[j].x = (position[i + 1]) - '0';
		}

		valid = validate_coordinates(game_board, ship_arr, BATTLE_LEN, BATT_INDEX);
	}
	if (ship_arr[BATT_INDEX].coordinate[0].y == ship_arr[BATT_INDEX].coordinate[1].y) {
		ship_arr[BATT_INDEX].direction = HORIZONTAL;
	}
	else {
		ship_arr[BATT_INDEX].direction = VERTICAL;
	}
	place_ship(game_board, ship_arr, BATT_INDEX, BATTLE);
	valid = 0;
	//Cruiser
	ship_arr[CRUS_INDEX].name = "Cruiser";
	ship_arr[CRUS_INDEX].sunk = -1;
	while (strlen(position) != 6 && !valid) {
		printf("Enter the 3 cells to place the Cruiser(r) on:\n");
		scanf("%s", &position);

		for (int i = 0, j = 0; (i + 1) < (CRUISER_LEN * 2); i += 2, j++) {
			ship_arr[CRUS_INDEX].coordinate[j].y = (position[i]) - '0';
			ship_arr[CRUS_INDEX].coordinate[j].x = (position[i + 1]) - '0';
		}

		valid = validate_coordinates(game_board, ship_arr, CRUISER_LEN, CRUS_INDEX);
	}
	if (ship_arr[CRUS_INDEX].coordinate[0].y == ship_arr[CRUS_INDEX].coordinate[1].y) {
		ship_arr[CRUS_INDEX].direction = HORIZONTAL;
	}
	else {
		ship_arr[CRUS_INDEX].direction = VERTICAL;
	}
	place_ship(game_board, ship_arr, CRUS_INDEX, CRUISER);
	//Reseting string for submarine while-loop
	position[2] = '\0';
	valid = 0;
	//Submarine
	ship_arr[SUB_INDEX].name = "Submarine";
	ship_arr[SUB_INDEX].sunk = -1;
	while (strlen(position) != 6 && !valid) {
		printf("Enter the 3 cells to place the Submarine(s) on:\n");
		scanf("%s", &position);

		for (int i = 0, j = 0; (i + 1) < (SUB_LEN * 2); i += 2, j++) {
			ship_arr[SUB_INDEX].coordinate[j].y = (position[i]) - '0';
			ship_arr[SUB_INDEX].coordinate[j].x = (position[i + 1]) - '0';
		}
		valid = validate_coordinates(game_board, ship_arr, SUB_LEN, SUB_INDEX);
	}
	if (ship_arr[SUB_INDEX].coordinate[0].y == ship_arr[SUB_INDEX].coordinate[1].y) {
		ship_arr[SUB_INDEX].direction = HORIZONTAL;
	}
	else {
		ship_arr[SUB_INDEX].direction = VERTICAL;
	}
	place_ship(game_board, ship_arr, SUB_INDEX, SUB);
	valid = 0;
	//Destroyer
	ship_arr[DESTR_INDEX].name = "Destroyer";
	ship_arr[DESTR_INDEX].sunk = -1;
	while (strlen(position) != 4 && !valid) {
		printf("Enter the 2 cells to place the Destroyer(d) on:\n");
		scanf("%s", &position);

		for (int i = 0, j = 0; (i + 1) < (DESTR_LEN * 2); i += 2, j++) {
			ship_arr[DESTR_INDEX].coordinate[j].y = (position[i]) - '0';
			ship_arr[DESTR_INDEX].coordinate[j].x = (position[i + 1]) - '0';
		}
		valid = validate_coordinates(game_board, ship_arr, DESTR_LEN, DESTR_INDEX);
	}
	if (ship_arr[DESTR_INDEX].coordinate[0].y == ship_arr[DESTR_INDEX].coordinate[1].y) {
		ship_arr[DESTR_INDEX].direction = HORIZONTAL;
	}
	else {
		ship_arr[DESTR_INDEX].direction = VERTICAL;
	}
	place_ship(game_board, ship_arr, DESTR_INDEX, DESTR);
}

void automatically_place_ships_on_board(char game_board[][MAX_COLS], Ship ship_arr[], int index) {
	Coordinate random_cell = { 0, 0 };
	int direction;//0 is horizontal, 1 is vertical
	//random cell generated so that the ship doesn't exceed the board bounds
	random_cell.x = rand() % (MAX_ROWS - ship_arr[index].length + 1);
	random_cell.y = rand() % (MAX_COLS - ship_arr[index].length + 1);
	direction = rand() % 2;
	//starting point for the placement of the ship
	ship_arr[index].coordinate[0].x = random_cell.x;
	ship_arr[index].coordinate[0].y = random_cell.y;
	if (direction == VERTICAL) {
		ship_arr[index].direction = VERTICAL;
		for (int i = 1; i < ship_arr[index].length; i++) {
			random_cell.y = random_cell.y + 1;
			ship_arr[index].coordinate[i].x = random_cell.x;
			ship_arr[index].coordinate[i].y = random_cell.y;
		}
	}
	else
	{
		ship_arr[index].direction = HORIZONTAL;
		for (int i = 1; i < ship_arr[index].length; i++) {
			random_cell.x = random_cell.x + 1;
			ship_arr[index].coordinate[i].x = random_cell.x;
			ship_arr[index].coordinate[i].y = random_cell.y;
		}
	}
	if (!validate_coordinates(game_board, ship_arr, ship_arr[index].length, index)) {
		move_invalid_placement(game_board, ship_arr, index, direction);
	}
	place_ship(game_board, ship_arr, index, ship_arr[index].symbol);
}
int validate_coordinates(char game_board[][MAX_COLS], Ship ship_arr[], int size, int index) {
	//Ints that determine if the coordinates are valid:
		//Overlap - 0 if there is overlap, 1 if none
		//within_bounds - 0 if outside bounds, 1 if within

	int overlap = 1, within_bounds = 1;

		for (int i = 0; i < size; i++) {
			if (game_board[ship_arr[index].coordinate[i].y][ship_arr[index].coordinate[i].x] != '~') {
				overlap = 0;
			}
		}


		for (int i = 0; i < size; i++) {
			if ((ship_arr[index].coordinate[i].y >= MAX_ROWS) || (ship_arr[index].coordinate[i].x >= MAX_COLS)) {
				within_bounds = 0;
			}
		}


		if (!within_bounds || !overlap) {
			return 0;
		}
		else {
			return 1;
		}

}

int check_shot(char game_board[][MAX_COLS], Coordinate guess) {
	if (game_board[guess.y][guess.x] != '~') {
		return 1;
	}
	else
	{
		return 0;
	}
}

void get_guess(char game_board[][MAX_COLS], Coordinate *guess) {
	char guess_str[3];
	int valid = 0;
	while (!valid) {
		printf("Enter the coordinates you want to hit:");
		scanf("%s", &guess_str);

		guess->y = guess_str[0] - '0';
		guess->x = guess_str[1] - '0';

		//checks if the coordinate being guessed has been guessed before
		if (game_board[guess->y][guess->x] != HIT && game_board[guess->y][guess->x] != MISS) {
			valid = 1;
		}
		else {
			printf("\nYou've already guessed those coordinates, try again.\n");
		}
	}
}

void output_move(FILE* outfile, int hit_miss, Coordinate guess, int player) {
	if (hit_miss) {
		fprintf(outfile, "Player %d guessed the coordinates (%d, %d). It was a hit!\n", player, guess.x, guess.y);
	}
	else
	{
		fprintf(outfile, "Player %d guessed the coordinates (%d, %d). It was a miss!\n", player, guess.x, guess.y);
	}
}

void update_board(char game_board[][MAX_COLS], int hit_miss, Coordinate guess) {
	if (hit_miss) {
		game_board[guess.y][guess.x] = HIT;
	}
	else {
		game_board[guess.y][guess.x] = MISS;
	}
}

int check_if_sunk_ship(char game_board[][MAX_COLS], Ship ship_arr[]) {
	int number_sunk = 0, hits, length, already_sunk;
	
	for (int index = 0; index < 5; index++) {
		hits = 0;
		length = ship_arr[index].length;
		for (int j = 0; j < length; j++) {
			if (game_board[ship_arr[index].coordinate[j].y][ship_arr[index].coordinate[j].x] == HIT) {
				hits++;
			}
		}
		if (hits == ship_arr[index].length) {
			number_sunk++;
			ship_arr[index].sunk = 1;
		}
	}
	return number_sunk;
}

int is_winner(int sunk_by_P1, int sunk_by_P2) {
	if (sunk_by_P1 == 5 || sunk_by_P2 == 5) {
		return 1;
	}
	else
	{
		return 0;
	}
}

void output_stats(FILE *outfile, int P1_total_shots, int P2_total_shots, int P1_total_hits, int P2_total_hits) {
	int P1_miss, P2_miss;
	P1_miss = P1_total_shots - P1_total_hits;
	P2_miss = P2_total_shots - P1_total_hits;
	//Player 1 stats
	fprintf(outfile, "\nPlayer 1 stats:\n");
	fprintf(outfile, "Total shots: %d\n", P1_total_shots);
	fprintf(outfile, "Total hits: %d\n", P1_total_hits);
	fprintf(outfile, "Total misses: %d\n", P1_miss);
	fprintf(outfile, "Hit to miss ratio: %.2lf%%\n", (double)(P1_total_hits / P1_miss) * 100);

	//Player 2 stats
	fprintf(outfile, "\nPlayer 2 stats:\n");
	fprintf(outfile, "Total shots: %d\n", P2_total_shots);
	fprintf(outfile, "Total hits: %d\n", P2_total_hits);
	fprintf(outfile, "Total misses: %d\n", P2_miss);
	fprintf(outfile, "Hit to miss ratio: %.2lf%%", (double)(P2_total_hits / P2_miss) * 100);
}

