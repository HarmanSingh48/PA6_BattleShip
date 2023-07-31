/*
Name: Harmanpreet Singh
Class: CptS 121, Lab Section 23
File: main.c
Description: Main file to run Battleship program
*/
#include "PA6.h"

int main(void) {
	srand((unsigned int)time(NULL));

	//Misc variable declarations
	int option, first_player, winner = 0, hit_miss, sunk_by_P1 = 0, sunk_by_P2 = 0, P1_total_shots = 0, P2_total_shots = 0, P1_hits = 0, P2_hits= 0;
	int P1_sunk_ships[5] = { -1, -1, -1, -1 ,-1 }, P2_sunk_ships[5] = { -1, -1, -1, -1, -1 };
	Coordinate P1_guess = { -1, -1 }, P2_guess = {-1, -1};
	//Declaring and initializing Boards
	char P1_board[MAX_ROWS][MAX_COLS], P2_board[MAX_ROWS][MAX_COLS];

	//Array of ships for location of player ships
	Ship P1_Ships[5], P2_Ships[5];

	init_game_board(P1_board, MAX_ROWS, MAX_COLS);
	init_game_board(P2_board, MAX_ROWS, MAX_COLS);

	
	//Initializing .log file

	FILE* log_file = fopen("battleship.log", "w");

	option = welcome_screen_menu();



	if (option == 1) {//The user chose to enter the coordinates manually
		fprintf(log_file,"Player 1 decided to place ships manually.\n");
		manually_place_ships_on_board(P1_board, P1_Ships);
		/*for (int i = 0; i <= 3; i++) {
			printf("Placeing Ships.");
			Sleep("100");
			printf(".");
			Sleep("100");
		}*/
		print_game_board(P1_board, 0);
	}
	else
	{
		fprintf(log_file, "Player 1 decided to place ships automatically.\n");
		//Automatically Placing ships
		//Carrier
		P1_Ships[CARR_INDEX].length = CARRIER_LEN;
		P1_Ships[CARR_INDEX].symbol = CARRIER;
		P1_Ships[CARR_INDEX].name = "Carrier";
		P1_Ships[CARR_INDEX].sunk = -1;
		automatically_place_ships_on_board(P1_board, P1_Ships, CARR_INDEX);
		//Battleship
		P1_Ships[BATT_INDEX].length = BATTLE_LEN;
		P1_Ships[BATT_INDEX].symbol = BATTLE;
		P1_Ships[BATT_INDEX].name = "Battleship";
		P1_Ships[BATT_INDEX].sunk = -1;
		automatically_place_ships_on_board(P1_board, P1_Ships, BATT_INDEX);
		//Cruiser
		P1_Ships[CRUS_INDEX].length = CRUISER_LEN;
		P1_Ships[CRUS_INDEX].symbol = CRUISER;
		P1_Ships[CRUS_INDEX].name = "Cruiser";
		P1_Ships[CRUS_INDEX].sunk = -1;
		automatically_place_ships_on_board(P1_board, P1_Ships, CRUS_INDEX);
		//Submarine
		P1_Ships[SUB_INDEX].length = SUB_LEN;
		P1_Ships[SUB_INDEX].symbol = SUB;
		P1_Ships[SUB_INDEX].name = "Submarine";
		P1_Ships[SUB_INDEX].sunk = -1;
		
		automatically_place_ships_on_board(P1_board, P1_Ships, SUB_INDEX);
		//Destroyer
		P1_Ships[DESTR_INDEX].length = DESTR_LEN;
		P1_Ships[DESTR_INDEX].symbol = DESTR;
		P1_Ships[DESTR_INDEX].name = "Destroyer";
		P1_Ships[DESTR_INDEX].sunk = -1;
		automatically_place_ships_on_board(P1_board, P1_Ships, DESTR_INDEX);
	}

	//Automatically Placing ships for computer
	//Carrier
	P2_Ships[CARR_INDEX].length = CARRIER_LEN;
	P2_Ships[CARR_INDEX].symbol = CARRIER;
	P2_Ships[CARR_INDEX].name = "Carrier";
	P2_Ships[CARR_INDEX].sunk = -1;
	automatically_place_ships_on_board(P2_board, P2_Ships, CARR_INDEX);
	//Battleship
	P2_Ships[BATT_INDEX].length = BATTLE_LEN;
	P2_Ships[BATT_INDEX].symbol = BATTLE;
	P2_Ships[BATT_INDEX].name = "Battleship";
	P2_Ships[BATT_INDEX].sunk = -1;
	automatically_place_ships_on_board(P2_board, P2_Ships, BATT_INDEX);
	//Cruiser
	P2_Ships[CRUS_INDEX].length = CRUISER_LEN;
	P2_Ships[CRUS_INDEX].symbol = CRUISER;
	P2_Ships[CRUS_INDEX].name = "Cruiser";
	P2_Ships[CRUS_INDEX].sunk = -1;
	automatically_place_ships_on_board(P2_board, P2_Ships, CRUS_INDEX);
	//Submarine
	P2_Ships[SUB_INDEX].length = SUB_LEN;
	P2_Ships[SUB_INDEX].symbol = SUB;
	P2_Ships[SUB_INDEX].name = "Submarine";
	P2_Ships[SUB_INDEX].sunk = -1;
	automatically_place_ships_on_board(P2_board, P2_Ships, SUB_INDEX);
	//Destroyer
	P2_Ships[DESTR_INDEX].length = DESTR_LEN;
	P2_Ships[DESTR_INDEX].symbol = DESTR;
	P2_Ships[DESTR_INDEX].name = "Destroyer";
	P2_Ships[DESTR_INDEX].sunk = -1;
	automatically_place_ships_on_board(P2_board, P2_Ships, DESTR_INDEX);

	first_player = rand() % 2 + 1;//Decides if player or computer goes first. player if 0, computer if 1


	if (first_player == PLAYER_1) {
		fprintf(log_file, "Player 1 was randomly selected to go first\n");
		printf("Player 1 was randomly selected to go first\n");
		while (!winner) {
			//Printing Boards
			print_game_board(P1_board, PLAYER_1);
			print_game_board(P2_board, PLAYER_2);

			//Player 1 Guessing and checking
			get_guess(P2_board, &P1_guess);
			P1_total_shots++;
			hit_miss = check_shot(P2_board, P1_guess);
			if (hit_miss) {
				P1_hits++;
			}
			update_board(P2_board, hit_miss, P1_guess);
			output_move(log_file, hit_miss, P1_guess, PLAYER_1);

			//Player 2 guessing and checking
			P2_guess.x = rand() % MAX_ROWS;
			P2_guess.y = rand() % MAX_COLS;
			P2_total_shots++;
			hit_miss = check_shot(P1_board, P2_guess);
			if (hit_miss) {
				P2_hits++;
			}
			update_board(P1_board, hit_miss, P2_guess);
			output_move(log_file, hit_miss, P2_guess, PLAYER_2);

			//Checking if a ship was sunk this round
			sunk_by_P1 = check_if_sunk_ship(P2_board, P2_Ships);
			

			
			//checking for a winner
			winner = is_winner(sunk_by_P1, sunk_by_P2);

			
			winner = is_winner(sunk_by_P1, sunk_by_P2);

			system("cls");

			//Displaying what was sunk
			for (int i = 0; i < 5; i++) {
				if (P2_sunk_ships[i] != P2_Ships[i].sunk) {
					P2_sunk_ships[i] = P2_Ships[i].sunk;
					printf("You sunk a %s!\n", P2_Ships[i].name);
					fprintf(log_file, "\nSunk %s", P2_Ships[i].name);
				}
			}

			sunk_by_P2 = check_if_sunk_ship(P1_board, P1_Ships);
			for (int i = 0; i < 5; i++) {
				if (P1_sunk_ships[i] != P1_Ships[i].sunk) {
					P1_sunk_ships[i] = P1_Ships[i].sunk;
					printf("Your %s was sunk!\n", P1_Ships[i].name);
					fprintf(log_file, "\nSunk %s\n", P1_Ships[i].name);
				}
			}
		}
		
	}
	else {
		fprintf(log_file, "The computer was randomly selected to go first\n");
		printf("The computer was randomly selected to go first\n");
		while (!winner) {
			//Printing Boards
			print_game_board(P1_board, PLAYER_1);
			print_game_board(P2_board, PLAYER_2);

			//Player 2 guessing and checking
			P2_guess.x = rand() % MAX_ROWS;
			P2_guess.y = rand() % MAX_COLS;
			P2_total_shots++;
			hit_miss = check_shot(P1_board, P2_guess);
			if (hit_miss) {
				P2_hits++;
			}
			update_board(P1_board, hit_miss, P2_guess);
			output_move(log_file, hit_miss, P2_guess, PLAYER_2);

			//Player 1 guessing and checking
			get_guess(P2_board, &P1_guess);
			P1_total_shots++;
			hit_miss = check_shot(P2_board, P1_guess);
			if (hit_miss) {
				P2_hits++;
			}
			update_board(P2_board, hit_miss, P1_guess);
			output_move(log_file, hit_miss, P1_guess, PLAYER_1);

			//Checking if a ship was sunk this round
			sunk_by_P1 = check_if_sunk_ship(P2_board, P2_Ships);

			sunk_by_P2 = check_if_sunk_ship(P1_board, P1_Ships);

			//checking for a winner
			winner = is_winner(sunk_by_P1, sunk_by_P2);
			winner = is_winner(sunk_by_P1, sunk_by_P2);

			//Clearing screen
			system("cls");

			//Printing updated boards
			print_game_board(P1_board, PLAYER_1);
			print_game_board(P2_board, PLAYER_2);

			//clearing screen between turns
			system("cls");
			
			//displaying what was sunk
			for (int i = 0; i < 5; i++) {
				if (P2_sunk_ships[i] != P2_Ships[i].sunk) {
					P2_sunk_ships[i] = 1;
					printf("You sunk a %s!\n", P2_Ships[i].name);
					fprintf(log_file, "\nSunk %s", P2_Ships[i].name);
				}
			}

			sunk_by_P2 = check_if_sunk_ship(P1_board, P1_Ships);
			for (int i = 0; i < 5; i++) {
				if (P1_sunk_ships[i] != P1_Ships[i].sunk) {
					P1_sunk_ships[i] = P1_Ships[i].sunk;
					printf("Your %s was sunk!\n", P1_Ships[i].name);
					fprintf(log_file, "\nSunk %s\n", P1_Ships[i].name);
				}
			}

		}
	}
	//End of game display and outputting stats
	if (sunk_by_P1 == 5) {

		printf("Congrats! You Won!\n Remember to check your stats in the log file.");
	}
	else if(sunk_by_P2 == 5)
	{
		printf("You lost! The computer beat you! How did that even happen? I didn't even code any fancy AI behavior.\nYou must really suck!" 
			"Anyway, remember to check your stats to see how bad you are.");
	}
	output_stats(log_file, P1_total_shots, P2_total_shots, P1_hits, P2_hits);
	fclose(log_file);

	return 0;
}