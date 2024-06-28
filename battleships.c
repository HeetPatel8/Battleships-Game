/* ENGGEN131 C Project 2023 - Battleships */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAP_SIZE 6
#define HIT 1000

// Prototype declarations of required functions
void PrintArray(int values[MAP_SIZE][MAP_SIZE]);
void InitialiseMap(int map[MAP_SIZE][MAP_SIZE]);
void AddRandomShip(int size, int map[MAP_SIZE][MAP_SIZE]);
int CountValues(int value, int map[MAP_SIZE][MAP_SIZE]);
int TopLeftPosition(int size, int *row, int *col, int map[MAP_SIZE][MAP_SIZE]);
int IsShipValid(int size, int map[MAP_SIZE][MAP_SIZE]);
void InitialiseRandomMap(int map[MAP_SIZE][MAP_SIZE]);
void FireShot(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE], int row, int col);
int CheckGameOver(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE]);


/******************************************************************************
*******************************************************************************
*******************************************************************************
// Implementations of the required functions should go below
*******************************************************************************
*******************************************************************************
******************************************************************************/

void PrintArray(int values[MAP_SIZE][MAP_SIZE])
{
	int i;
	int j;
	for (i = 0; i < MAP_SIZE; i++) {
		for (j = 0; j < MAP_SIZE; j++) {
			printf("%d ", values[i][j]);
		}
		printf("\n");
	}
}

void InitialiseMap(int map[MAP_SIZE][MAP_SIZE])
{
	int i;
	for (i = 0; i < 2; i++) {
		map[i][0] = 2;
	}
	int j;
	for (j = 1; j < 4; j++) {
		map[2][j] = 3;
	}
	int k;
	for (k = 1; k < MAP_SIZE; k++) {
		map[MAP_SIZE - 6 + k][MAP_SIZE - 1] = 5;
	}
	int l;
	for (l = 0; l < 4; l++) {
		map[MAP_SIZE - 1][l] = 4;
	}
}

void AddRandomShip(int size, int map[MAP_SIZE][MAP_SIZE])
{
	int direction = rand() % 2;
	// for vertical ship placement
	if (direction == 1) {
		int horizontalPos = (rand() % MAP_SIZE);
		int verticalPos = (rand() % (MAP_SIZE - size));
		for (int i = 0; i < size; i++) {
			map[horizontalPos][verticalPos + i] = size;
		}
	}
	//For horizontal ship placement
	else {
		int verticalPos = (rand() % MAP_SIZE);
		int horizontalPos = (rand() % (MAP_SIZE - size));
		for (int j = 0; j < size; j++) {
			map[horizontalPos + j][verticalPos] = size;
		}
	}
}

int CountValues(int value, int map[MAP_SIZE][MAP_SIZE])
{
	int count = 0;
	for (int row = 0; row < MAP_SIZE; row++) {
		for (int col = 0; col < MAP_SIZE; col++) {
			if (map[row][col] == value) {
				count++;
			}
		}
	}
	return count;
}

int TopLeftPosition(int size, int* row, int* col, int map[MAP_SIZE][MAP_SIZE])
{
	for (int rowCheck = 0; rowCheck < MAP_SIZE; rowCheck++) {
		for (int colCheck = 0; colCheck < MAP_SIZE; colCheck++) {
			if (map[rowCheck][colCheck] == size) {
				*row = rowCheck;
				*col = colCheck;
				//Check for direction, horizontal or vertical
				if (map[rowCheck + 1][colCheck] == size) {
					return 2;
				}
				else {
					return 1;
				}


			}
		}
	}
}

int IsShipValid(int size, int map[MAP_SIZE][MAP_SIZE])
{
	for (int rowSearch = 0; rowSearch < MAP_SIZE; rowSearch++) {
		for (int colSearch = 0; colSearch < MAP_SIZE; colSearch++) {
			if (map[rowSearch][colSearch] == size) {

				//Determine direction
				if (map[rowSearch + 1][colSearch] == size) {
					//Vertical situation
					//Check above and below ship for perpendicular
					if (rowSearch == 0) {
						if (map[rowSearch + size][colSearch] != 0) {
							return 0;
						}
					}
					else if (map[MAP_SIZE - size][colSearch] == size) {
						if (map[rowSearch - 1][colSearch] != 0) {
							return 0;
						}
					}
					else {
						if ((map[rowSearch - 1][colSearch] != 0) || (map[rowSearch + size][colSearch] != 0)) {
							return 0;
						}
					}

					if (colSearch == 0) {
						for (int shipCheck = 0; shipCheck < size; shipCheck++) {
							if (map[rowSearch + shipCheck][colSearch + 1] != 0) {
								return 0;
							}
						}
					}
					else if (map[rowSearch][MAP_SIZE - 1] == size) {
						for (int shipCheck = 0; shipCheck < size; shipCheck++) {
							if (map[rowSearch + shipCheck][colSearch - 1] != 0) {
								return 0;
							}
						}
					}
					else {
						for (int shipCheck = 0; shipCheck < size; shipCheck++) {
							if ((map[rowSearch + shipCheck][colSearch + 1] != 0) || (map[rowSearch + shipCheck][colSearch - 1] != 0)) {
								return 0;
							}
						}
					}

				}
				else {
					//Horizontal situation
					// Check at either end the front or the back of the ship

					if (colSearch == 0) {
						if (map[rowSearch][colSearch + size] != 0) {
							return 0;
						}
					}
					else if ((colSearch + size) == MAP_SIZE) {
						if (map[rowSearch][colSearch - 1] != 0) {
							return 0;
						}
					}
					else {
						if ((map[rowSearch][colSearch - 1] != 0) || (map[rowSearch][colSearch + size] != 0)) {
							return 0;
						}
					}
					if (rowSearch == 0) {
						for (int shipCheck = 0; shipCheck < size; shipCheck++) {
							if (map[rowSearch + 1][colSearch + shipCheck] != 0) {
								return 0;
							}
						}
					}
					else if ((rowSearch + 1) == MAP_SIZE) {
						for (int shipCheck = 0; shipCheck < size; shipCheck++) {
							if (map[rowSearch - 1][colSearch + shipCheck] != 0) {
								return 0;
							}
						}
					}
					else {
						for (int shipCheck = 0; shipCheck < size; shipCheck++) {
							if ((map[rowSearch + 1][colSearch + shipCheck] != 0) || (map[rowSearch - 1][colSearch + shipCheck] != 0)) {
								return 0;
							}
						}
					}
				}
				return 1;
			}



		}
	}

	int checkingCounter = 0;
	for (int rowPresentCheck = 0; rowPresentCheck < MAP_SIZE; rowPresentCheck++) {
		for (int colPresentCheck = 0; colPresentCheck < MAP_SIZE; colPresentCheck++) {
			if (map[rowPresentCheck][colPresentCheck] == size) {
				checkingCounter++;
			}
		}
	}
	if (checkingCounter == 0) {
		return 0;
	}
	else {
		return 1;
	}
}

void InitialiseRandomMap(int map[MAP_SIZE][MAP_SIZE])
{

	int check = 0;
	while (check != 1) {
		for (int shipSize = 2; shipSize <= 5; shipSize++) {
			AddRandomShip(shipSize, map);
		}
		if (IsShipValid(2, map) && IsShipValid(3, map) && IsShipValid(3, map) && IsShipValid(4, map) && IsShipValid(5, map)) {
			check = 1;
		}
		else {
			for (int resetRow = 0; resetRow < MAP_SIZE; resetRow++) {
				for (int resetCol = 0; resetCol < MAP_SIZE; resetCol++) {
					map[resetRow][resetCol] = 0;
				}
			}
		}
	}
}



void FireShot(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE], int row, int col)
{
	int shot_number = 0;
	int ship2row[2], ship2col[2], ship3row[3], ship3col[3], ship4row[4], ship4col[4], ship5row[5], ship5col[5];
	//Determining shot_number
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			if (shots[i][j] != 0) {
				if ((shots[i][j] % 1000) > shot_number) {
					shot_number = shots[i][j] % 1000;
				}
			}
		}
	}

	// Determining existing ship positions
	int tracer;
	for (int shipSize = 2; shipSize <= 5; shipSize++) {
		tracer = 0;
		for (int k = 0; k < MAP_SIZE; k++) {
			for (int l = 0; l < MAP_SIZE; l++) {
				if (map[k][l] == shipSize) {
					if (shipSize == 2) {
						ship2row[tracer] = k;
						ship2col[tracer] = l;
					}
					else if (shipSize == 3) {
						ship3row[tracer] = k;
						ship3col[tracer] = l;
					}
					else if (shipSize == 4) {
						ship4row[tracer] = k;
						ship4col[tracer] = l;
					}
					else if (shipSize == 5) {
						ship5row[tracer] = k;
						ship5col[tracer] = l;
					}
					tracer++;
				}
			}
		}
	}

	if (shots[row][col] != 0) {
		return;
	}

	if (map[row][col] == 0) {
		shot_number++;
		shots[row][col] = shot_number;
	}
	else if (map[row][col] == 2) {
		shot_number++;
		shots[row][col] = 1000 + shot_number;
		if ((shots[ship2row[0]][ship2col[0]] > 1000) && (shots[ship2row[1]][ship2col[1]] > 1000)) {
			shots[ship2row[0]][ship2col[0]] = shots[ship2row[0]][ship2col[0]] + 1000;
			shots[ship2row[1]][ship2col[1]] = shots[ship2row[1]][ship2col[1]] + 1000;
		}
	}
	else if (map[row][col] == 3) {
		shot_number++;
		shots[row][col] = 1000 + shot_number;
		if ((shots[ship3row[0]][ship3col[0]] > 1000) && (shots[ship3row[1]][ship3col[1]] > 1000) && (shots[ship3row[2]][ship3col[2]] > 1000)) {
			shots[ship3row[0]][ship3col[0]] = shots[ship3row[0]][ship3col[0]] + 2000;
			shots[ship3row[1]][ship3col[1]] = shots[ship3row[1]][ship3col[1]] + 2000;
			shots[ship3row[2]][ship3col[2]] = shots[ship3row[2]][ship3col[2]] + 2000;
		}
	}
	else if (map[row][col] == 4) {
		shot_number++;
		shots[row][col] = 1000 + shot_number;
		if ((shots[ship4row[0]][ship4col[0]] > 1000) && (shots[ship4row[1]][ship4col[1]] > 1000) && (shots[ship4row[2]][ship4col[2]]) && (shots[ship4row[3]][ship4col[3]] > 1000)) {
			shots[ship4row[0]][ship4col[0]] = shots[ship4row[0]][ship4col[0]] + 3000;
			shots[ship4row[1]][ship4col[1]] = shots[ship4row[1]][ship4col[1]] + 3000;
			shots[ship4row[2]][ship4col[2]] = shots[ship4row[2]][ship4col[2]] + 3000;
			shots[ship4row[3]][ship4col[3]] = shots[ship4row[3]][ship4col[3]] + 3000;
		}
	}
	else if (map[row][col] == 5) {
		shot_number++;
		shots[row][col] = 1000 + shot_number;
		if ((shots[ship5row[0]][ship5col[0]] > 1000) && (shots[ship5row[1]][ship5col[1]] > 1000) && (shots[ship5row[2]][ship5col[2]]) && (shots[ship5row[3]][ship5col[3]] > 1000) && (shots[ship5row[4]][ship5col[4]] > 1000)) {
			shots[ship5row[0]][ship5col[0]] = shots[ship5row[0]][ship5col[0]] + 4000;
			shots[ship5row[1]][ship5col[1]] = shots[ship5row[1]][ship5col[1]] + 4000;
			shots[ship5row[2]][ship5col[2]] = shots[ship5row[2]][ship5col[2]] + 4000;
			shots[ship5row[3]][ship5col[3]] = shots[ship5row[3]][ship5col[3]] + 4000;
			shots[ship5row[4]][ship5col[4]] = shots[ship5row[4]][ship5col[4]] + 4000;
		}

	}
}


int CheckGameOver(int shots[MAP_SIZE][MAP_SIZE], int map[MAP_SIZE][MAP_SIZE])
{
	//Check to see which ship sizes are present on the board
	int ship2counter = 0;
	int ship3counter = 0;
	int ship4counter = 0;
	int ship5counter = 0;
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			if (map[i][j] == 2) {
				ship2counter++;
			}
			else if (map[i][j] == 3) {
				ship3counter++;
			}
			else if (map[i][j] == 4) {
				ship4counter++;
			}
			else if (map[i][j] == 5) {
				ship5counter++;
			}
		}
	}
	// Determine how many of each ship length there is present on the map


	for (int k = 0; k < MAP_SIZE; k++) {
		for (int l = 0; l < MAP_SIZE; l++) {
			if (shots[k][l] != 0) {
				if ((map[k][l] % 6) == 2) {
					ship2counter--;
				}
				else if ((map[k][l] % 6) == 3) {
					ship3counter--;
				}
				else if ((map[k][l] % 6) == 4) {
					ship4counter--;
				}
				else if ((map[k][l] % 6) == 5) {
					ship5counter--;
				}
			}
		}
	}

	if ((ship2counter == 0) && (ship3counter == 0) && (ship4counter == 0) && (ship5counter == 0)) {
		return 1;
	}

	return 0;
}

/******************************************************************************
*******************************************************************************
*******************************************************************************
// Implementations of the required functions should go above
*******************************************************************************
*******************************************************************************
******************************************************************************/

// Provided functions needed for playing the Battleships game:

// First, prototype declarations for the bots:
void GetMoveBot1(int shots[MAP_SIZE][MAP_SIZE], int *row, int *col);
void GetMoveBot2(int shots[MAP_SIZE][MAP_SIZE], int *row, int *col);

// Gets the input for one move from the human player (an alphabetic row and a numeric column)
// This function converts both inputs to numeric values
void GetMoveHuman(int *row, int *col, int player)
{
	char a = ' ';
	int b = -1;
	printf("Player %d: enter move [row/col]: ", player);
	while (!(a >= 'A' && a <= 'Z')) {
		scanf("%c", &a);
	}
	while (!(b >= 0 && b <= 25)) {
		scanf("%d", &b);
	}
	*row = (int)(a - 'A');
	*col = b;
}

// Takes two "shots" arrays as input (which are the visible parts of the game shown to players) and formats them into a string for printing
// The player currently to move is highlighted
void GetDisplayMapString(int shots1[MAP_SIZE][MAP_SIZE], int shots2[MAP_SIZE][MAP_SIZE], int player, char *boardString)
{
	int i, j;
	char numbers[10];
	// Intialise board string to be empty:
	boardString[0] = '\0';
	strcat(boardString, "  ");

	for (i = 0; i < MAP_SIZE; i++) {
		sprintf(numbers, "%d", i%10);
		strcat(boardString, numbers);
	}
	strcat(boardString, "|");
	for (i = 0; i < MAP_SIZE; i++) {
		sprintf(numbers, "%d", i%10);
		strcat(boardString, numbers);
	}
	strcat(boardString, "\n  ");

	for (i = 0; i < MAP_SIZE; i++) {
		strcat(boardString, "-");
	}
	strcat(boardString, "|");
	for (i = 0; i < MAP_SIZE; i++) {
		strcat(boardString, "-");
	}
	strcat(boardString, "\n");

	for (i = 0; i < MAP_SIZE; i++) {
		int len = strlen(boardString);
		boardString[len] = (char)('A' + i);
		boardString[len+1] = '\0';
		strcat(boardString, "|");
		for (j = 0; j < MAP_SIZE; j++) {
			if (shots1[i][j] / HIT > 0) {
				if (shots1[i][j] / HIT == 1) {
					strcat(boardString, "X");
				} else {
					sprintf(numbers, "%d", shots1[i][j] / HIT);
					strcat(boardString, numbers);
				}
			} else if (shots1[i][j] > 0) {
				strcat(boardString, ".");
			} else {
				strcat(boardString, " ");
			}
		}
		strcat(boardString, "|");
		for (j = 0; j < MAP_SIZE; j++) {
			if (shots2[i][j] / HIT > 0) {
				if (shots2[i][j] / HIT == 1) {
					strcat(boardString, "X");
				} else {
					sprintf(numbers, "%d", shots2[i][j] / HIT);
					strcat(boardString, numbers);
				}
			} else if (shots2[i][j] > 0) {
				strcat(boardString, ".");
			} else {
				strcat(boardString, " ");
			}
		}
		strcat(boardString, "|");
		len = strlen(boardString);
		boardString[len] = (char)('A' + i);
		boardString[len+1] = '\0';
		strcat(boardString, "\n");
	}
	if (player == 1) {
		strcat(boardString, "  P1");
		for (i = 0; i < MAP_SIZE-2; i++) {
			strcat(boardString, "*");
		}
	} else {
		for (i = 0; i < MAP_SIZE; i++) {
			strcat(boardString, " ");
		}
		strcat(boardString, "   P2");
		for (i = 0; i < MAP_SIZE-2; i++) {
			strcat(boardString, "*");
		}
	}
	strcat(boardString, "\n");
}

// Plays one game of Battleships, beginning with the specified starting player
// Game type = 1 (human vs human) or 2 (human vs bot) or 3 (bot vs bot)
int PlayOneGame(int startingPlayer, int gameType)
{
	int row, col, player, gameOver;

	// String to display the boards
	char displayBoardString[(2*MAP_SIZE+5)*(MAP_SIZE+5)];

	// The maps containing the locations of the ships
	int mapPlayer1[MAP_SIZE][MAP_SIZE] = {0};
	int mapPlayer2[MAP_SIZE][MAP_SIZE] = {0};

	// The locations of the shots
	int shotsPlayer1[MAP_SIZE][MAP_SIZE] = {0};
	int shotsPlayer2[MAP_SIZE][MAP_SIZE] = {0};

	player = startingPlayer;
	gameOver = 0;

	// Create random maps for each player
	InitialiseRandomMap(mapPlayer1);
	InitialiseRandomMap(mapPlayer2);

	// Display the board if a human is playing
	if (gameType != 3) {
		GetDisplayMapString(shotsPlayer1, shotsPlayer2, player, displayBoardString);
		printf("%s", displayBoardString);
	}

	// Process one move for the current player
	while (!gameOver) {
		if (gameType == 1) {
			GetMoveHuman(&row, &col, player);
			if (player == 1) {
				FireShot(shotsPlayer1, mapPlayer2, row, col);
				gameOver = CheckGameOver(shotsPlayer1, mapPlayer2);
			} else {
				FireShot(shotsPlayer2, mapPlayer1, row, col);
				gameOver = CheckGameOver(shotsPlayer2, mapPlayer1);
			}
		} else if (gameType == 2) {
			if (player == 1) {
				GetMoveHuman(&row, &col, player);
				FireShot(shotsPlayer1, mapPlayer2, row, col);
				gameOver = CheckGameOver(shotsPlayer1, mapPlayer2);
			} else {
				GetMoveBot1(shotsPlayer2, &row, &col);
				printf("Player 2 (bot) moves: %c%d\n", (char)(row+'A'), col);
				FireShot(shotsPlayer2, mapPlayer1, row, col);
				gameOver = CheckGameOver(shotsPlayer2, mapPlayer1);
			}
		} else {
			if (player == 1) {
				GetMoveBot1(shotsPlayer1, &row, &col);
				FireShot(shotsPlayer1, mapPlayer2, row, col);
				gameOver = CheckGameOver(shotsPlayer1, mapPlayer2);
			} else {
				GetMoveBot2(shotsPlayer2, &row, &col);
				FireShot(shotsPlayer2, mapPlayer1, row, col);
				gameOver = CheckGameOver(shotsPlayer2, mapPlayer1);
			}
		}

		// Swap players
		if (!gameOver) {
			player = 3 - player;
		}
		if (gameType != 3) {
			GetDisplayMapString(shotsPlayer1, shotsPlayer2, player, displayBoardString);
			printf("%s", displayBoardString);
		}
	}
	return player;
}

// Play a Battleships tournament
// If the tournament is between a human and a bot, only one game is played
// If the tournament is between two bots, the number of games is requested
void PlayBattleships(void)
{
	int gameType, numberOfGames, result;
	int i, wins1, wins2, player;

	// Get play options:
	printf("Options:\n");
	printf(" [1] = Human vs. Human\n");
	printf(" [2] = Human vs. Bot1\n");
	printf(" [3] = Bot1 vs. Bot2\n");
	printf("Choose game type: ");
	scanf("%d", &gameType);
	numberOfGames = 1;
	result = 0;

	// If two bots are playing a tournament, let the user choose how many games
	if (gameType == 3) {
		printf("Number of games: ");
		scanf("%d", &numberOfGames);
	}

	// Set win counts to zero
	wins1 = 0;
	wins2 = 0;

	// Player 1 will always start the first game
	// If a tournament is played (between two bots), the starting player alternates
	player = 1;

	for (i = 0; i < numberOfGames; i++) {
		result = PlayOneGame(player, gameType);
		if (result == 1) {
			wins1++;
		} else {
			wins2++;
		}
		// Switch the starting player for the next game
		player = 3 - player;
	}

	// Show the outcome (of a single game or tournament)
	if (numberOfGames == 1) {
		printf("\nGame over! Congratulations! Winner is Player %d\n\n", result);
	} else {
		printf("\nTournament over! Games played = %d\nPlayer 1 wins = %d / Player 2 wins = %d\n\n", numberOfGames, wins1, wins2);
	}
}

// The main function for the Battleships program
int main(void)
{
	// Initialise the seed for the random number generator
	srand((unsigned int)time(NULL));

	printf("ENGGEN131 - C Project 2023\n");
	printf("                          ... presents ...\n");
	printf(" ___    __   _____ _____  _     ____  __   _     _   ___   __  \n");
	printf("| |_)  / /\\   | |   | |  | |   | |_  ( (` | |_| | | | |_) ( (` \n");
	printf("|_|_) /_/--\\  |_|   |_|  |_|__ |_|__ _)_) |_| | |_| |_|   _)_) \n");
	printf("\n                __/___            \n");
	printf("          _____/______|           \n");
	printf("  _______/_____\\_______\\_____     \n");
	printf("  \\              < < <       |    \n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("\n");

	PlayBattleships();

	return 0;
}

/******************************************************************************
*******************************************************************************
*******************************************************************************
// Implementations of the two bots can be provided below
// The existing implementations are naive:
// - Bot 1 simply takes random shots (without checking for repeated shots)
// - Bot 2 also takes random shots (but makes a single test on each turn for a repeated shot)
*******************************************************************************
*******************************************************************************
******************************************************************************/

// Strategy for Bot 1
void GetMoveBot1(int shots[MAP_SIZE][MAP_SIZE], int *row, int *col)
{
	int rand_row;
	int rand_col;

	rand_row = shots[0][0]; // to prevent compiler warning (because otherwise "shots" array is not accessed)
	rand_row = rand() % MAP_SIZE;
	rand_col = rand() % MAP_SIZE;

	*row = rand_row;
	*col = rand_col;
}

// Strategy for Bot 2
void GetMoveBot2(int shots[MAP_SIZE][MAP_SIZE], int *row, int *col)
{
	int rand_row;
	int rand_col;

	rand_row = shots[0][0]; // to prevent compiler warning (because otherwise "shots" array is not accessed)
	rand_row = rand() % MAP_SIZE;
	rand_col = rand() % MAP_SIZE;

	// If the shot has been tried before, try one more time
	if (shots[rand_row][rand_col] > 0) {
		rand_row = rand() % MAP_SIZE;
		rand_col = rand() % MAP_SIZE;
	}

	*row = rand_row;
	*col = rand_col;
}













