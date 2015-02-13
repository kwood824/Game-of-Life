#include <time.h>
#include <iostream>
#include <string>
#include <cstdlib>


using namespace std;


const int ROWS = 79;
const int COLS = 22;
int WORLD[ROWS][COLS];
int copyWorld[ROWS][COLS];
int cellCount;
char DEAD = '_';
char ALIVE = '*';

//Function Declarations

void fillArray();
//Gives the player a random start by randomly assigning each spot in the array to be either dead or alive

void printArray();
//Prints out the visual display of the game world with *'s = living and _'s = dead

void changeArray();
//Function that goes through and detects the number of living cells next to each position to determine if the spot should produce a living cell or a dead one

void copyOverArray();
//Copies the living and dead values from the temporary array copyWorld to the main array WORLD that is then displayed to the player. (copyWorld is assigned the values from changeArray to prevent
//cells changed earlier up the chain from influencing cells not yet modified


int main()
{
	int QUIT = 0;
	char junk;

	fillArray();

	cout << "Welcome to the Game of Life!" << endl << "Press 0 then ENTER to create a randomized start. Press 1 to quit." << endl;
	cin >> QUIT;

	while (QUIT == 0)
	{
		printArray();

		cout << endl << "To proceed to the next step press 0 then ENTER again." << endl << "Press 1 to quit." << endl << "Press 2 to restart the Game of Life with a new batch of cells" << endl;
		cin >> QUIT;
		changeArray();
		copyOverArray();

		if (QUIT == 2)
		{
			fillArray();
			QUIT = 0;
		}

	}

	if (QUIT == 1)
	{
		cout << endl << "Thanks for playing!" << endl;
	}


	std::cin.get();
	std::cin.get(); // I added these two to make the executable pause before closing when I compile at home

	return 0;
}

void fillArray()
{
	int random = 0;
	srand(time(NULL));


	for (int i = 1; i <= ROWS - 1; i++)
	{
		for (int j = 1; j <= COLS - 1; j++)
		{
			random = rand() % 2 + 0;
			WORLD[i][j] = random;
		}
	}
}

void printArray()
{
	for (int i = 0; i <= COLS; i++)
	{
		cout << endl;
		for (int j = 0; j <= ROWS; j++)
		{
			if (WORLD[i][j] == 0)
			{
				cout << DEAD;
			}
			else
				cout << ALIVE;
		}
	}
}

void changeArray()
{
	int i, j, p, k, cx, cy;
	for (i = 0; i < ROWS; i++) 
	{
		for (j = 0; j < COLS; j++)
		{
			cellCount = 0;

			if (WORLD[i][j] == 0)//Dead cell detection
			{
				for (p = -1; p < 2; ++p)
				{
					for (k = -1; k < 2; ++k)
					{
						if (p == 0 && k == 0)
							continue;

						if ((i + p) >= ROWS)
							cx = 0;
						else if ((i + p) < 0)
							cx = ROWS - 1;
						else
							cx = i + p;

						if ((j + k) >= COLS)
							cy = 0;
						else if ((j + k) < 0)
							cy = COLS - 1;
						else
							cy = j + k;

						if (WORLD[cx][cy] == 1)
							cellCount++;
					}
				}
				if (cellCount == 3)
					copyWorld[i][j] = 1; //Becomes a cell
			}
		}
	}
	for (i = 0; i < ROWS; i++)
	{
		for (j = 0; j < COLS; j++)
		{
			cellCount = 0;

			if (WORLD[i][j] == 1)//Detects if alive
			{
				for (p = -1; p < 2; ++p)
				{
					for (k = -1; k < 2; ++k)
					{
						if (p == 0 && k == 0)
							continue;

						if ((i + p) >= ROWS)
							cx = 0;
						else if ((i + p) < 0)
							cx = ROWS - 1;
						else
							cx = i + p;

						if ((j + k) >= COLS)
							cy = 0;
						else if ((j + k) < 0)
							cy = COLS - 1;
						else
							cy = j + k;

						if (WORLD[cx][cy] == 1)
							cellCount++;
					}
				}
				if ((cellCount == 0) || (cellCount == 1))
					copyWorld[i][j] = 0; //Dies
				else if (cellCount > 3)
				{
					copyWorld[i][j] = 0; //Dies
				}
			}
		}
	}
	WORLD[ROWS][COLS] = copyWorld[ROWS][COLS];
}

void copyOverArray()
{
	for (int i = 0; i <= COLS; i++)
	{
		for (int j = 0; j <= ROWS; j++)
		{
			WORLD[i][j] = copyWorld[i][j];
		}
	}
}