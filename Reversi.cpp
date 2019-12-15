#include <iostream>
#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <cstdlib>

using namespace std;

const int boardSize = 8;
char grid[boardSize][boardSize], pos[2];
int X, Y = 0;
char W = 'W';
char B = 'B';
char S = ' ';

bool whiteTurn = true; //This changes turns
bool endGame = true; // Ends the game if false
bool invalidMove = true; // Boolean changes if the move is invalid
bool PreviousPass = false;  // Boolean changes if there were 2 consecutive passes

void initializeGrid() {

	for (int r = 0; r < boardSize; r++)
	{
		for (int c = 0; c < 8; c++)
		{
			if (c == 3 && r == 4 || c == 4 && r == 3)
			{
				grid[c][r] = W;
			}
			else if (c == 3 && r == 3 || c == 4 && r == 4)
			{
				grid[c][r] = B;
			}
			else {
				grid[c][r] = S;
			}
		}

	}
	cout << endl;
	return;
}

void displayGame() {
	system("CLS");

	if (whiteTurn)
	{
		cout << "WHITE TURN" << endl;
	}
	else
	{
		cout << "BLACK TURN" << endl;
	}
	cout << endl;
	cout << "  A B C D E F G H" << endl;
	cout << "  ----------------" << endl;

	for (int row = 0; row < boardSize; row++)
	{
		cout << row + 1 << '|';
		for (int col = 0; col < boardSize; col++)
		{
			cout << grid[col][row] << '|';
		}
		cout << endl;
	}
	cout << "  ----------------" << endl;
}

void enterMove() {
	cout << endl << "Quit (Q)" << endl << "Pass (P)" << endl;
inputRestart:
	cout << "Enter letter: " << endl;
	cin >> pos[0];
	cout << endl;

	if (pos[0] == 'A' || pos[0] == 'a')
	{
		X = 0;
	}

	else if (pos[0] == 'B' || pos[0] == 'b')
	{
		X = 1;
	}

	else if (pos[0] == 'C' || pos[0] == 'c')
	{
		X = 2;
	}

	else if (pos[0] == 'D' || pos[0] == 'd')
	{
		X = 3;
	}

	else if (pos[0] == 'E' || pos[0] == 'e')
	{
		X = 4;
	}

	else if (pos[0] == 'F' || pos[0] == 'f')
	{
		X = 5;
	}
	else if (pos[0] == 'G' || pos[0] == 'g')
	{
		X = 6;
	}
	else if (pos[0] == 'H' || pos[0] == 'h')
	{
		X = 7;
	}
	else if (pos[0] == 'Q' || pos[0] == 'q')
	{
		exit(0);
	}
	else if (pos[0] == 'P' || pos[0] == 'p')
	{
		whiteTurn = !whiteTurn;
		return;
	}
	else
	{
		cout << "Invalid letter: " << endl;
		goto inputRestart;
	}

	cout << "Enter Number: ";
	cin >> pos[1];
	cout << endl;
	if (pos[1] == '1')
	{
		Y = 0;
	}

	else if (pos[1] == '2')
	{
		Y = 1;
	}

	else if (pos[1] == '3')
	{
		Y = 2;
	}

	else if (pos[1] == '4')
	{
		Y = 3;
	}

	else if (pos[1] == '5')
	{
		Y = 4;
	}

	else if (pos[1] == '6')
	{
		Y = 5;
	}
	else if (pos[1] == '7')
	{
		Y = 6;
	}
	else if (pos[1] == '8')
	{
		Y = 7;
	}
	else if (pos[1] == 'Q' || pos[1] == 'q')
	{
		exit(0);
	}
	else
	{
		cout << "Invalid number" << endl;
		goto inputRestart;
	}
}

int distance(int xDir, int yDir) // calculate the distance checked depending on the direction and coordinate input
{
	int boardDistanceX, boardDistanceY;
	if (xDir == -1)
		boardDistanceX = X;

	if (xDir == 1)
	{
		boardDistanceX = boardSize - X;
	}

	if (xDir == 0)
	{
		boardDistanceX = boardSize;
	}

	if (yDir == -1)
		boardDistanceY = Y;

	if (yDir == 1)
	{
		boardDistanceY = boardSize - Y;
	}

	if (yDir == 0)
	{
		boardDistanceY = boardSize;
	}


	if (boardDistanceX < boardDistanceY)
	{
		return boardDistanceX;
	}
	else
	{
		return boardDistanceY;
	}
}

void printPiece()
{
	if (invalidMove)
	{
		cout << "Invalid Move" << endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
	else
	{
		if (whiteTurn)
		{
			grid[X][Y] = W;
		}
		else
		{
			grid[X][Y] = B;
		}
		whiteTurn = !whiteTurn;
		invalidMove = true;
	}
}

void Flip(char currentplayer, int distance, int xDir, int yDir)
{
	if (!invalidMove)
	{
		for (int flipDistance = 1; flipDistance < distance; flipDistance++)
		{
			grid[flipDistance * xDir + X][flipDistance * yDir + Y] = currentplayer;
		}
	}
	else
	{
		return;
	}
}

void countPieces()
{
	int WP, BP; //		White/Black Points
	WP = 0;
	BP = 0;
	for (int r = 0; r < 8; r++) // Will check all the board and add when it finds a matching piece
	{
		for (int c = 0; c < 8; c++)
		{
			if (grid[c][r] == W)
			{
				WP += 1;
			}
			else if (grid[c][r] == B)
			{
				BP += 1;
			}
			else {
				continue;
			}
		}
	}

	if (WP > BP)
	{
		cout << "White Wins!" << endl;
	}
	else if (BP > WP)
	{
		cout << "Black Wins!" << endl;
	}
	else
	{
		cout << "It's a tie!" << endl;
	}
}

void check()
{
	char currentPlayer;
	char opponentPlayer;

	if (whiteTurn)
	{
		currentPlayer = W;
		opponentPlayer = B;
	}
	else
	{
		currentPlayer = B;
		opponentPlayer = W;
	}

	if (invalidMove)
	{
		for (int xDir = -1; xDir < 2; xDir++) // Generate directions to check 
		{
			for (int yDir = 1; -2 < yDir; yDir--)
			{
				if (xDir == 0 && yDir == 0)
				{
					continue;
				}

				int disToBoardEdge = distance(xDir, yDir);
				bool foundPiece = false;

				for (int distance = 1; distance < disToBoardEdge; distance++)
				{
					char currentPiece = grid[distance * xDir + X][distance * yDir + Y];

					if (currentPiece == opponentPlayer)
					{
						foundPiece = true;
						continue;
					}
					else if (currentPiece == S)
					{
						break;
					}
					else if (currentPiece == currentPlayer)
					{
						if (foundPiece == false)
						{
							break;
						}
						else
						{
							invalidMove = false;
							Flip(currentPlayer, distance, xDir, yDir);
						}
					}
				}
			}
		}
		if (pos[0] == 'P' || pos[0] == 'p') // Checks if there was a pass before the one just made
		{
			if (PreviousPass == true) // If there were 2 passes in a row the pieces are counted and the game ends
			{
				countPieces();
				endGame = false;
			}
			else {
				PreviousPass = true;
			}
		}
		else
		{
			PreviousPass = false;
		}
	}
}

int main()
{
	initializeGrid();
	while (endGame)
	{
		displayGame();
		enterMove();
		check();
		printPiece();
	}
	system("PAUSE");
}