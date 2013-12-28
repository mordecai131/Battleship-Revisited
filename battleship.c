#include "battleship.h"

void init_game_board(char player_board[MAX_ROW][MAX_COL])
{
	int count_row = 0, count_col = 0;

	for(count_row = 0; count_row < MAX_ROW; count_row++)
	{
		for(count_col = 0; count_col < MAX_COL; count_col++)
		{
			player_board[count_row][count_col] = '~';
		}
	}
}

void print_gameboard(char player_board[MAX_ROW][MAX_COL])
{
	int row = 0, col = 0;

	printf("  0 1 2 3 4 5 6 7 8 9\n");
	for(row = 0; row < MAX_ROW; row++)
	{
		printf("%d ", row);
		for(col = 0; col < MAX_COL; col++)
		{
			printf("%c ", player_board[row][col]);
		}
		printf("\n");
	}
}

int is_valid_option(int option, int max_options, int min_options)
{
	if((option > min_options) && (option < max_options))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void manually_place_ships_v2(char* ship_name, char symbole, int spaces, char player_board[MAX_ROW][MAX_COL])
{
	int row = 0, column = 0, count = 0, valid = FALSE;
	char direction = '\0';

SHIP:
	printf("Here is where you place the %s!!\n\n", ship_name);
	print_gameboard(player_board);
	printf("Please enter the coordinates for where you'd like your %s to start.\nNote: The %s takes %d spaces so be sure to leave enough room to the\nright or below it\n", ship_name, ship_name, spaces);
	scanf("%d%d", &row, &column);
	printf("What direction would you like your ship to face? To the right or down? (r/d):\n");
	scanf(" %c", &direction);
	valid = is_valid_ship_placement(row, column, direction, player_board);
	if(valid == TRUE)
	{
		if(direction == 'r')
		{
			for(count = 0; count < spaces; count++, column++)
			{
				player_board[row][column] = symbole;
			}
		}
		else if(direction == 'd')
		{
			for(count = 0; count < spaces; count++, row++)
			{
				player_board[row][column] = symbole;
			}
		}
		system("cls");
	}
	if(valid == FALSE)
	{
		system("cls");
		printf("Invalid placement! Please try again!\n\n");
		goto SHIP;
	}
}

void randomly_place_ships_v2(char symbole, int spaces, char player_board[MAX_ROW][MAX_COL])
{
	int row = 0, column = 0, count = 0, valid = FALSE; 
	char direction_arry[2] = {'r', 'd'};
	char direction = '\0';

SHIP:
	row = rand() % MAX_ROW;
	column = rand() % MAX_COL;
	direction = direction_arry[rand() % 2];
	valid = is_valid_ship_placement(row, column, direction, player_board);
	if(valid == TRUE)
	{
		if(direction == 'r')
		{
			for(count = 0; count < spaces; count++, column++)
			{
				player_board[row][column] = symbole;
			}
		}
		else if(direction == 'd')
		{
			for(count = 0; count < spaces; count++, row++)
			{
				player_board[row][column] = symbole;
			}
		}
		system("cls");
	}
	if(valid == FALSE)
	{
		system("cls");
		goto SHIP;
	}
}

int is_valid_ship_placement(int row, int col, char direction, char player_board[MAX_ROW][MAX_COL])
{
	int count = 0, valid = FALSE;

	if(direction == 'd')
	{
		for(count = 0; count <= 5; count++, row++)
		{
			if((row < MAX_ROW) && (row >= 0) && (player_board[row][col] == '~'))
			{
				valid = TRUE;
			}
			else 
			{
				valid = FALSE;
				break;
			}
		}
	}

	else if(direction == 'r')
	{
		for(count = 0; count <= 5; count++, col++)
		{
			if((col < MAX_COL) && (col >= 0) && (player_board[row][col] == '~'))
			{
				valid = TRUE;
			}
			else 
			{
				valid  = FALSE; 
				break;
			}
		}
	}
	return valid;
}

void play_game(char player1_board[MAX_ROW][MAX_COL], char player2_board[MAX_ROW][MAX_COL], char shots_board[MAX_ROW][MAX_COL])
{
	int shot_row = 0, shot_col = 0, valid = FALSE;
	char symboles[5] = {'c', 'b', 's', 'd', 'p'};
	int count_player1_shots = 0, count_player2_shots = 0;
	FILE *outfile;

	outfile = fopen("Stats.txt", "a");

	printf("The top board is your hit or miss board which marks the shots you have taken andif you hit or missed player 2's ship. The bottom board is your ships board whichmarks what shots player 2 has taken and if they have hit or missed your ships.\n");
	print_gameboard(shots_board);
	print_gameboard(player1_board);
	printf("As player 1, you get to take the first shot! Please enter where you'd like to\ntake your shot:\n");
	scanf("%d%d", &shot_row, &shot_col);
	if(player2_board[shot_row][shot_col] != '~')
	{
		system("cls");
		printf("\n\nThat's a hit!\n");
		shots_board[shot_row][shot_col] = '*';
		player2_board[shot_row][shot_col] = '*';
	}
	else if(player2_board[shot_row][shot_col] == '~')
	{
		system("cls");
		printf("Sorry, that's a miss\n");
		shots_board[shot_row][shot_col] = 'm';
	}
	print_gameboard(shots_board);
	print_gameboard(player1_board);
	printf("Player 2's turn. Press 'ENTER' to continue\n");
	_getch();
	count_player1_shots++;
	goto PLAYER2;

PLAYER1:
	print_gameboard(shots_board);
	print_gameboard(player1_board);
	printf("Please enter where you'd like to take your shot:\n");
	scanf("%d%d", &shot_row, &shot_col);

	// Scan for hit/miss

	if((player2_board[shot_row][shot_col] == '*') || (player2_board[shot_row][shot_col] == 'm'))
	{
		system("cls");
		printf("You've have already taken a shot here, please chose a different location\n\n");
		goto PLAYER1;
	}
	else if(player2_board[shot_row][shot_col] != '~')
	{
		system("cls");
		printf("That's a hit!\n");
		shots_board[shot_row][shot_col] = '*';
		player2_board[shot_row][shot_col] = '*';
		valid = is_winner(player2_board);
		count_player1_shots++;
		if(valid == TRUE)
		{
			goto WINNER1;
		}
	}
	else if(player2_board[shot_row][shot_col] == '~')
	{
		system("cls");
		printf("Sorry, that's a miss\n");
		shots_board[shot_row][shot_col] = 'm';
		player2_board[shot_row][shot_col] = 'm';
		count_player1_shots++;
	}
	print_gameboard(shots_board);
	print_gameboard(player1_board);
	printf("Player 2's turn. Press 'ENTER' to continue\n");
	_getch();
	goto PLAYER2;
PLAYER2:
	shot_row = rand() % MAX_ROW;
	shot_col = rand() % MAX_COL;

	// Scan for hit/miss
	if((player1_board[shot_row][shot_col] == '*') || (player1_board[shot_row][shot_col] == 'm'))
	{
		system("cls");
		goto PLAYER2;
	}
	else if(player1_board[shot_row][shot_col] != '~')
	{
		system("cls");
		printf("Player 2 hit one of your ships!\n");
		player1_board[shot_row][shot_col] = '*';
		valid = is_winner(player1_board);
		count_player2_shots++;
		if(valid == TRUE)
		{
			goto WINNER2;
		}
	}
	else if(player1_board[shot_row][shot_col] == '~')
	{
		system("cls");
		printf("Player 2 missed!\n");
		player1_board[shot_row][shot_col] = 'm';
		count_player2_shots++;
	}
	print_gameboard(shots_board);
	print_gameboard(player1_board);
	printf("Your turn! Press 'ENTER' to continue");
	_getch();
	system("cls");
	check_sunk_ships(player1_board, player2_board); 
	goto PLAYER1;

WINNER1:
	system("cls");
	printf("Player 1 has won!\n");
	fprintf(outfile, "Winner: Player1\nShots:\nPlayer1: %d\nPlayer2: %d\n\n", count_player1_shots, count_player2_shots);
	fclose(outfile);
	return;

WINNER2:
	system("cls");
	printf("Player 2 has won!\n");
	fprintf(outfile, "Winner: Player1\nShots:\nPlayer1: %d\nPlayer2: %d\n\n", count_player1_shots, count_player2_shots);
	fclose(outfile);
	return;
}

int is_winner(char player_board[MAX_ROW][MAX_COL])
{
	int count_row = 0, count_col = 0, valid = FALSE;

	for(count_row = 0; count_row < MAX_ROW; count_row++)
	{
		for(count_col = 0; count_col < MAX_COL; count_col++)
		{
			if(player_board[count_row][count_col] == '~' || player_board[count_row][count_col] == 'm' || player_board[count_row][count_col] == '*')
			{
				valid = TRUE;
			}
			else 
			{
				valid = FALSE;
				break;
			}
		}
		if(valid == FALSE)
		{
			break;
		}
	}
	return valid;
}

void check_sunk_ships(char player1_board[MAX_ROW][MAX_COL], char player2_board[MAX_ROW][MAX_COL])
{
	int count_row = 0, count_col = 0, count_array = 0, valid = TRUE;
	struct sunk_ships player1, player2;
	char symbole[5] = {'c', 'b', 's', 'd', 'p'};
	int player1_ships[5] = {player1.sunk_carrier = FALSE, player1.sunk_battleship = FALSE, player1.sunk_sub = FALSE, player1.sunk_destroyer = FALSE, player1.sunk_patrol = FALSE};
	int player2_ships[5] = {player2.sunk_carrier = FALSE, player2.sunk_battleship = FALSE, player2.sunk_sub = FALSE, player2.sunk_destroyer = FALSE, player2.sunk_patrol = FALSE};
	char* ship_names[5] = {"Carrier", "Batttleship", "Submarine", "Destroyer", "Patrol"};

	// Check player 1 board for sunk ships

	for(count_array = 0; count_array < 5; count_array++)
	{
		for(count_row = 0; count_row < MAX_ROW; count_row++)
		{
			for(count_col = 0; count_col < MAX_COL; count_col++)
			{
				if(player1_board[count_row][count_col] == symbole[count_array])
				{
					valid = FALSE;
					player1_ships[count_array] = FALSE; // If false then the ship has not been sunk. break out of this for loop
					break;								// Remains in the outter and outter-outter loop. 
				}
				else
				{
					valid = TRUE;
					player1_ships[count_array] = TRUE;
				}
			}
			if(valid == FALSE)
			{
				break;
			}
		}
	}

	for(count_array = 0; count_array < 5; count_array++)
	{
		for(count_row = 0; count_row < MAX_ROW; count_row++)
		{
			for(count_col = 0; count_col < MAX_COL; count_col++)
			{
				if(player2_board[count_row][count_col] == symbole[count_array])
				{
					valid = FALSE;
					player2_ships[count_array] = FALSE; // If false then the ship has not been sunk. break out of this for loop
					break;								// Remains in the outter and outter-outter loop. 
				}
				else
				{
					valid = TRUE;
					player2_ships[count_array] = TRUE;
				}
			}
			if(valid == FALSE)
			{
				break;
			}
		}
	}

	printf("These are the ships that have been sunk on each player's board\n\n");
	printf("Player1\n----------\n");
	for(count_array = 0; count_array < 5; count_array++)
	{
		if(player1_ships[count_array] == TRUE)
		{
			printf("%s\n", ship_names[count_array]);
		}
	}
	printf("\nPlayer2\n----------\n");
	for(count_array = 0; count_array < 5; count_array++)
	{
		if(player2_ships[count_array] == TRUE)
		{
			printf("%s\n", ship_names[count_array]);
		}
	}
	printf("\n\nPress 'ENTER' to continue\n");
	_getch();
	system("cls");
}

void run(void)
{
	char player1_board[MAX_ROW][MAX_COL], shots_taken[MAX_ROW][MAX_COL], player2_board[MAX_ROW][MAX_COL];
	int option = 0, valid = FALSE, count = 0;
	int spaces[5] = {5, 4, 3, 2, 2};
	char symboles[5] = {'c', 'b', 's', 'd', 'p'};
	char* ship_names[5] = {"Carrier", "Battleship", "Submarine", "Destroyer", "Patrol"};

	srand((unsigned int) time(NULL));

	printf("*******************************************\n");
	printf("*           Welcome to Battleship!        *\n");
	printf("*******************************************\n");

	init_game_board(player1_board);
	init_game_board(player2_board);
	init_game_board(shots_taken);
	printf("\n You're player 1 and here is your gameboard!\n\n");
	print_gameboard(player1_board);
	printf("\nAs you can see it has no ships! You have two options:\n");
	
	// Display options menu and check validity of choice

	while(valid == FALSE)
	{
		printf("1: You can manually input each ship individually\n");
		printf("2: Or You can have the ships randomly placed for you\n");
		scanf("%d", &option);
		valid = is_valid_option(option, 3, 0);
		if(valid == FALSE)
		{
			system("cls");
			printf("Sorry that's an invalid option, please choose a valid option\n\n");
		}
	}

	// Start ship placement process

	if(option == 1)
	{
		system("cls");
		for(count = 0; count < 5; count++)
		{
			manually_place_ships_v2(ship_names[count], symboles[count], spaces[count], player1_board);
			randomly_place_ships_v2(symboles[count], spaces[count], player2_board);
		}
	}
	else
	{
		system("cls");
		for(count = 0; count < 5; count++)
		{
			randomly_place_ships_v2(symboles[count], spaces[count], player1_board);
			randomly_place_ships_v2(symboles[count], spaces[count], player2_board);
		}
	}
	print_gameboard(player1_board);
	printf("\nNow that your ships have been placed, it's time to play!\n");
	printf("\nPlease press 'ENTER' to continue");
	_getch();
	system("cls");
	play_game(player1_board, player2_board, shots_taken);
}
