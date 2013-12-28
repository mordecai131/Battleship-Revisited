#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

#define MAX_COL 10
#define MAX_ROW 10

typedef enum boolean
{
	FALSE, TRUE
} Boolean;

typedef struct sunk_ships
{
	int sunk_carrier;
	int sunk_battleship;
	int sunk_sub;
	int sunk_destroyer;
	int sunk_patrol;
};

void init_game_board(char player_board[MAX_ROW][MAX_COL]);
void print_gameboard(char player_board[MAX_ROW][MAX_COL]);
int is_valid_option(int option, int max_options, int min_options);
void manually_place_ships_v2(char* ship_name, char symbole, int spaces, char player_board[MAX_ROW][MAX_COL]);
void randomly_place_ships_v2(char symbole, int spaces, char player_board[MAX_ROW][MAX_COL]);
int is_valid_ship_placement(int row, int col, char direction, char player_board[MAX_ROW][MAX_COL]);
void play_game(char player1_board[MAX_ROW][MAX_COL], char player2_board[MAX_ROW][MAX_COL], char shots_board[MAX_ROW][MAX_COL]);
int is_winner(char player_board[MAX_ROW][MAX_COL]);
void check_sunk_ships(char player1_board[MAX_ROW][MAX_COL], char player2_board[MAX_ROW][MAX_COL]);
void run(void);

#endif
