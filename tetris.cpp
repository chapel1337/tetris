#include <iostream>
#include <string>
#include <windows.h>
#include <vector>
#include <conio.h>

using std::cout; using std::cin; using std::vector; using std::string; using std::ws; using std::getline;

// written by chapel1337
// made on 11/4/2022
// WHY WON'T THESE DAMN LOOPS WORK!?!?!??!?!?!?!?!!?
// I HATE YOU MICROSOFT

// had to remove falling and just let user control the block
// did not add differing blocks because i would rather die

// i don't even care anymore if this pile of trash is broken

vector<vector<char>> map{ 
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', }, 
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', }, 
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
	{ ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', },
};
vector<vector<char>> currentMap{ map };

vector<char> block1{ '#', '#', '#' };

vector<char> currentBlock{ block1 };

int blockY{ 1 };
vector<int> blockX{ 0, 1, 2 };

int mapY{ (int) map.size() };
int mapX{ (int) map[0].size() };

bool aDisabled{ false };
bool dDisabled{ false };

int blocksPlaced{};
int hashtagCount{};
int points{};

// ------- \\

void sleep(int time)
{
	Sleep(time * 1000);
}

void clear()
{
	#ifdef __linux__
	system("clear");

	#elif _WIN32
		system("cls");
	#endif
}

void setTextColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void resetTextColor()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

// ------- \\

void getInput();
void start();

void youWin()
{
	clear();

	cout << "you win!\n";

	exit(1);
}

void youLose()
{
	clear();

	cout << "you lose!\n";

	exit(1);
}

// ------- \\

void displayStatistics()
{
	cout << "x: ";
	for (int i{ 0 }; i < blockX.size(); ++i)
	{
		cout << blockX[i] << ", ";
	}
	cout << '\n';

	cout << "y: " << blockY << '\n';
	cout << "map y: " << mapY << '\n';
	cout << "map x: " << mapX << "\n\n";
	cout << "blocks placed: " << blocksPlaced << "\n\n";
	cout << "hashtag count: " << hashtagCount << '\n';
	cout << "points: " << points << "\n\n";
}

void createNewBlock()
{
	for (int i{ 0 }; i < blockX.size(); ++i)
	{
		map[blockY][blockX[i]] = currentBlock[i];
	}
	currentBlock = block1;

	blocksPlaced++;

	blockY = 1;
	for (int i{ 0 }; i < blockX.size(); ++i)
	{
		blockX[i] = i;
	}

	// it sure would be great if this didn't freeze everything when playing; thanks microsoft!
	// Beep(200, 325);
}

void setBlockPosition()
{
	currentMap.clear();
	currentMap = map;

	if (points >= 3)
	{
		youWin();
	}

	if (blocksPlaced != 0)
	{
		for (int i{ 0 }; i < blockX.size(); ++i)
		{
			if (currentMap[blockY + 1][i] == '#')
			{
				if (blockY == 1)
				{
					youLose();
				}
				else
				{
					createNewBlock();
					start();
				}
			}
		}
	}

	for (int i{}; i < currentMap.size(); ++i)
	{
		for (int o{}; o < currentMap[i].size(); ++o)
		{
			// this **should** be working, but it isn't;
			// welcome to the world of programming, where NOTHING WORKS CORRECTLY!
			if (hashtagCount == mapY)
			{
				points++;
				break;
			}

			if (currentMap[i][o] == '#')
			{
				hashtagCount++;
			}
		}
	}

	hashtagCount = 0;

	if (blockY == mapY - 1)
	{
		createNewBlock();
		start();
	}

	if (blockX[0] == 0)
	{
		aDisabled = true;
	}
	else
	{
		aDisabled = false;
	}

	if (blockX[blockX.size() - 1] == mapX - 1)
	{
		dDisabled = true;
	}
	else
	{
		dDisabled = false;
	}

	for (int i{0}; i < blockX.size(); ++i)
	{
		currentMap[blockY][blockX[i]] = currentBlock[i]; // spook
	}
}

void refresh()
{
	clear();
	setBlockPosition();
	displayStatistics();

	cout << '|';
	for (int i{}; i < mapX + 1; ++i)
	{
		cout << '-';
	}
	cout << "|\n";

	for (int i{ 0 }; i < currentMap.size(); ++i)
	{
		cout << "| ";

		for (int o{}; o < currentMap[i].size(); ++o)
		{
			cout << currentMap[i][o];
		} 

		cout << "|\n";
	}

	cout << '|';
	for (int i{}; i < mapX + 1; ++i)
	{
		cout << '-';
	}
	cout << "|\n";
}

// ------- \\

void changeBlockPosition(char direction)
{
	if (direction == 'r' && !dDisabled)
	{
		for (int i{ 0 }; i < blockX.size(); ++i)
		{
			blockX[i]++;
		}
	}
	else if (direction == 'l' && !aDisabled)
	{
		for (int i{ 0 }; i < blockX.size(); ++i)
		{
			blockX[i]--;
		}
	}
	else if (direction == 's')
	{
		blockY++;
	}

	refresh();
	getInput();
}

void getInput()
{
	int input{ _getch() };

	switch (input)
	{
	case 's':
		changeBlockPosition('s');
		break;

	case 'd':
		changeBlockPosition('r');
		break;

	case 'a':
		changeBlockPosition('l');
		break;

	default:
		getInput();
		break;
	}

	refresh();
}

// ------- \\

void quit()
{
	clear();

	for (int i{ 3 }; i > 0; --i)
	{
		cout << "okay, exiting in " << i;

		sleep(1);
		clear();
	}

	Beep(200, 325);
	exit(1);
}

void start()
{
	refresh();
	getInput();
}

void menu()
{
	clear();

	char response{};

	cout << "tetris\n\n";

	cout << "1. start\n";
	cout << "2. quit\n\n";

	cout << "> ";
	cin >> response;

	switch (response)
	{
	case '1':
		start();
		break;

	case '2':
		quit();
		break;

	default:
		menu();
		break;
	}
}

// ------- \\

int main()
{
	cout << "written by chapel1337\n";
	cout << "made on 11/4/2022\n";

	sleep(2);

	Beep(200, 325);
	menu();
}

// ------- \\
