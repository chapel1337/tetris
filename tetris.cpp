#include <iostream>
#include <string>

#ifdef __linux__
#include <unistd>
#elif _WIN32
#include <windows.h>
void sleep(int time)
{
	Sleep(time * 1000);
}
#endif

#include <vector>
#include <conio.h>
#include <random>

using std::cout; using std::cin; using std::vector; using std::string; using std::ws; using std::getline;

// written by chapel1337
// made on 11/4/2022
// WHY WON'T THESE DAMN LOOPS WORK!?!?!??!?!?!?!?!!?
// I HATE YOU MICROSOFT

// had to remove falling and just let user control the block
// did not add differing blocks because i would rather die

// i don't even care anymore if this pile of trash is broken
// i can't stand not creating something; i must make this day of importance
// i can't stop doing this

// 11/5/2022
// finished, currently very happy

vector<vector<char>> presetMap
{
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

vector<vector<char>> map{ presetMap };
vector<vector<char>> currentMap{ map };

vector<char> currentBlock{ '#', '#', '#' };
int blockY{ 1 };
vector<int> blockX{ 0, 1, 2 };

int mapY{ (int) map.size() };
int mapX{ (int) map[0].size() };

bool aDisabled{ false };
bool dDisabled{ false };
bool randomColorsEnabled{ false };

int blocksPlaced{};
int hashtagCount{};
int points{};

// ------- \\

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

int getRandom(int min, int max)
{
	// i had to copy this from learncpp.com, i will not be memorizing this prng method anytime soon
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution random{ min, max };

	return random(mt);
}

// ------- \\

void goTo(string function);

void winLoseHandler(bool outcome) // win = true, loss = false
{
	string response{};

	cout << "would you like to play again?\n\n";

	cout << "> ";
	getline(cin >> ws, response);

	if (response == "yes" || response == "y")
	{
		points = 0;
		blocksPlaced = 0;
		blockY = 1;

		map = presetMap;
		currentMap.clear();
		currentMap = map;

		for (int i{}; i < blockX.size(); ++i)
		{
			blockX[i] = i;
		}

		goTo("start");
	}
	else if (response == "no" || response == "n")
	{
		goTo("menu");
	}
	else
	{
		if (outcome)
		{
			goTo("youWin");
		}
		else
		{
			goTo("youLose");
		}
	}

}

void youWin()
{
	clear();

	setTextColor(10);
	cout << "you win!\n\n";
	resetTextColor();

	Beep(500, 200);
	Beep(500, 200);
	Beep(500, 500);
	Beep(500, 200);
	Beep(500, 200);

	winLoseHandler(true);
}

void youLose()
{
	clear();

	setTextColor(4);
	cout << "you lose!\n\n";
	resetTextColor();

	Beep(200, 700);
	Beep(200, 700);
	Beep(200, 700);
	Beep(200, 1250);

	winLoseHandler(false);
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

	if (blocksPlaced != 0)
	{
		// finally got it working!!

		for (int i{ 0 }; i < blockX.size(); ++i)
		{
			if (blockY == mapY - 1)
			{
				if (currentMap[blockY][blockX[i]] == '#')
				{
					if (blockY == 1)
					{
						youLose();
					}
					else
					{
						createNewBlock();
						goTo("start");
					}
				}
			}
			else
			{
				if (currentMap[blockY + 1][blockX[i]] == '#')
				{
					if (blockY == 1)
					{
						youLose();
					}
					else
					{
						createNewBlock();
						goTo("start");
					}
				}
			}
		}
	}

	for (int i{}; i < currentMap.size(); ++i)
	{
		for (int o{}; o < currentMap[i].size(); ++o)
		{
			// this **should** be working, but it isn't;
			// welcome to the world of programming, where NOTHING WORKS CORRECTLY! [outdated rant]

			if (currentMap[i][o] == '#')
			{
				hashtagCount++;
			}
		}

		if (hashtagCount == mapY - 1)
		{
			points++;
			hashtagCount = 0;

			map.erase(map.begin() + i);
			map.insert(map.begin(), map[0]);

			break;
		}
		else
		{
			hashtagCount = 0;
		}
	}

	if (blockY == mapY - 1)
	{
		createNewBlock();
		goTo("start");
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

	if (points >= 3)
	{
		youWin();
	}

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
			if (randomColorsEnabled)
			{
				setTextColor(getRandom(1, 10));
			}
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
	goTo("getInput");
}

void getInput()
{
	int input{ _getch() };

	switch (input)
	{
	case 'S':
	case 's':
		changeBlockPosition('s');
		break;

	case 'D':
	case 'd':
		changeBlockPosition('r');
		break;

	case 'A':
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

void toggleRandomColors()
{
	clear();

	if (randomColorsEnabled)
	{
		randomColorsEnabled = false;
		cout << "disabled text colors\n\n";
	}
	else
	{
		randomColorsEnabled = true;
		cout << "enabled text colors\n\n";
	}

	cout << "> ";

	sleep(2);
	goTo("menu");
}

void menu()
{
	clear();

	char response{};

	cout << "tetris\n\n";

	cout << "1. start\n";
	cout << "2. toggle random colors\n";
	cout << "3. quit\n\n";

	cout << "> ";
	cin >> response;

	switch (response)
	{
	case '1':
		start();
		break;

	case '2':
		toggleRandomColors();
		break;

	case '3':
		quit();
		break;

	default:
		menu();
		break;
	}
}

// ------- \\

void goTo(string function)
{
	if (function == "start")
	{
		start();
	}
	else if (function == "getInput")
	{
		getInput();
	}
	else if (function == "menu")
	{
		menu();
	}

	else if (function == "youWin")
	{
		youWin();
	}
	else if (function == "youLose")
	{
		youLose();
	}
}

int main()
{
	cout << "written by chapel1337\n";
	cout << "made on 11/4/2022\n";

	sleep(2);

	Beep(200, 325);
	menu();
}

// ------- \\