#include <stdio.h>
#include <time.h>
#include <math.h>
#include <Windows.h>
#include <errno.h> 
#include <conio.h>

#define LAB_Y 30 //50 //9
#define LAB_X 35 //60 //27
#define START_POS_X 1
#define START_POS_Y	1
#define FRAMES 1
#define STARTFRAME 0
#define MILLIS 0

struct Pos
{
	int X;
	int Y;
	int Steps;
};

struct Node
{
	char parent;
	int visited;
	int distance;
};

char lab[LAB_Y][LAB_X] = {
{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'},
{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','M',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
{'#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#',' ','#'},
{'#',' ','#',' ',' ',' ',' ',' ','#',' ','#',' ',' ',' ',' ',' ','#',' ','#',' ',' ',' ',' ',' ','#',' ','#',' ',' ',' ',' ',' ','#',' ','#'},
{'#',' ','#',' ','#','#','#',' ','#',' ','#',' ','#','#','#',' ','#',' ','#',' ','#','#','#',' ','#',' ','#',' ','#','#','#',' ','#',' ','#'},
{'#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#'},
{'#',' ','#',' ','#',' ',' ',' ','#',' ','#',' ','#',' ',' ',' ','#',' ','#',' ','#',' ',' ',' ','#',' ','#',' ','#',' ',' ',' ','#',' ','#'},
{'#',' ','#',' ','#','#','#','#','#',' ','#',' ','#','#','#','#','#',' ','#',' ','#','#','#','#','#',' ','#',' ','#','#','#','#','#',' ','#'},
{'#',' ','#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','#'},
{'#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#',' ','#'},
{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
{'#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#',' ','#'},
{'#',' ','#',' ',' ',' ',' ',' ','#',' ','#',' ',' ',' ',' ',' ','#',' ','#',' ',' ',' ',' ',' ','#',' ','#',' ',' ',' ',' ',' ','#',' ','#'},
{'#',' ','#',' ','#','#','#',' ','#',' ','#',' ','#','#','#',' ','#',' ','#',' ','#','#','#',' ','#',' ','#',' ','#','#','#',' ','#',' ','#'},
{'#',' ','#',' ','#','M','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#','G','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#'},
{'#',' ','#',' ','#',' ',' ',' ','#',' ','#',' ','#',' ',' ',' ','#',' ','#',' ','#',' ',' ',' ','#',' ','#',' ','#',' ',' ',' ','#',' ','#'},
{'#',' ','#',' ','#','#','#','#','#',' ','#',' ','#','#','#','#','#',' ','#',' ','#','#','#','#','#',' ','#',' ','#','#','#','#','#',' ','#'},
{'#',' ','#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','#'},
{'#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#',' ','#'},
{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
{'#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#',' ','#'},
{'#',' ','#',' ',' ',' ',' ',' ','#',' ','#',' ',' ',' ',' ',' ','#',' ','#',' ',' ',' ',' ',' ','#',' ','#',' ',' ',' ',' ',' ','#',' ','#'},
{'#',' ','#',' ','#','#','#',' ','#',' ','#',' ','#','#','#',' ','#',' ','#',' ','#','#','#',' ','#',' ','#',' ','#','#','#',' ','#',' ','#'},
{'#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#',' ','#','M','#',' ','#',' ','#'},
{'#',' ','#',' ','#',' ',' ',' ','#',' ','#',' ','#',' ',' ',' ','#',' ','#',' ','#',' ',' ',' ','#',' ','#',' ','#',' ',' ',' ','#',' ','#'},
{'#',' ','#',' ','#','#','#','#','#',' ','#',' ','#','#','#','#','#',' ','#',' ','#','#','#','#','#',' ','#',' ','#','#','#','#','#',' ','#'},
{'#',' ','#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ','#'},
{'#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#',' ','#','#','#','#','#','#','#',' ','#'},
{'#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#'},
{'#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#'}
};

char end[25][43] = {
{ ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\n' },
{ ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\n' },
{ ' ',' ',' ',' ',' ',' ',' ',' ','G','G','G','G','G','G','G','G','G','G','G','G','G',' ',' ',' ',' ',' ',' ',' ',' ','G','G','G','G','G','G','G','G','G','G','G','G','G','\n' },
{ ' ',' ',' ',' ',' ','G','G','G',':',':',':',':',':',':',':',':',':',':',':',':','G',' ',' ',' ',' ',' ','G','G','G',':',':',':',':',':',':',':',':',':',':',':',':','G','\n' },
{ ' ',' ',' ','G','G',':',':',':',':',':',':',':',':',':',':',':',':',':',':',':','G',' ',' ',' ','G','G',':',':',':',':',':',':',':',':',':',':',':',':',':',':',':','G','\n' },
{ ' ',' ','G',':',':',':',':',':','G','G','G','G','G','G','G','G',':',':',':',':','G',' ',' ','G',':',':',':',':',':','G','G','G','G','G','G','G','G',':',':',':',':','G','\n' },
{ ' ','G',':',':',':',':',':','G',' ',' ',' ',' ',' ',' ',' ','G','G','G','G','G','G',' ','G',':',':',':',':',':','G',' ',' ',' ',' ',' ',' ',' ','G','G','G','G','G','G','\n' },
{ 'G',':',':',':',':',':','G',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','G',':',':',':',':',':','G',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\n' },
{ 'G',':',':',':',':',':','G',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','G',':',':',':',':',':','G',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\n' },
{ 'G',':',':',':',':',':','G',' ',' ',' ',' ','G','G','G','G','G','G','G','G','G','G','G',':',':',':',':',':','G',' ',' ',' ',' ','G','G','G','G','G','G','G','G','G','G','\n' },
{ 'G',':',':',':',':',':','G',' ',' ',' ',' ','G',':',':',':',':',':',':',':',':','G','G',':',':',':',':',':','G',' ',' ',' ',' ','G',':',':',':',':',':',':',':',':','G','\n' },
{ 'G',':',':',':',':',':','G',' ',' ',' ',' ','G','G','G','G','G',':',':',':',':','G','G',':',':',':',':',':','G',' ',' ',' ',' ','G','G','G','G','G',':',':',':',':','G','\n' },
{ 'G',':',':',':',':',':','G',' ',' ',' ',' ',' ',' ',' ',' ','G',':',':',':',':','G','G',':',':',':',':',':','G',' ',' ',' ',' ',' ',' ',' ',' ','G',':',':',':',':','G','\n' },
{ ' ','G',':',':',':',':',':','G',' ',' ',' ',' ',' ',' ',' ','G',':',':',':',':','G',' ','G',':',':',':',':',':','G',' ',' ',' ',' ',' ',' ',' ','G',':',':',':',':','G','\n' },
{ ' ',' ','G',':',':',':',':',':','G','G','G','G','G','G','G','G',':',':',':',':','G',' ',' ','G',':',':',':',':',':','G','G','G','G','G','G','G','G',':',':',':',':','G','\n' },
{ ' ',' ',' ','G','G',':',':',':',':',':',':',':',':',':',':',':',':',':',':',':','G',' ',' ',' ','G','G',':',':',':',':',':',':',':',':',':',':',':',':',':',':',':','G','\n' },
{ ' ',' ',' ',' ',' ','G','G','G',':',':',':',':',':',':','G','G','G',':',':',':','G',' ',' ',' ',' ',' ','G','G','G',':',':',':',':',':',':','G','G','G',':',':',':','G','\n' },
{ ' ',' ',' ',' ',' ',' ',' ',' ','G','G','G','G','G','G',' ',' ',' ','G','G','G','G',' ',' ',' ',' ',' ',' ',' ',' ','G','G','G','G','G','G',' ',' ',' ','G','G','G','G','\n' },
{ ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\n' },
{ ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\n' },
{ ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\n' },
{ ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\n' },
{ ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\n' },
{ ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\n' },
{ ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\n' },
};

char brainMap[LAB_Y][LAB_X];
char brain[LAB_Y][LAB_X];
char generalDir;
char directions[4] = { 'u','l','d','r'};
struct Pos Player;
struct Node map[LAB_Y][LAB_X];

char startDirection()				//stellt fest, in welchem Quadranten sich der Spieler befindet und in welcher Bewegungsrichtung die Wand am schnellsten erreicht werden kann
{
	if (Player.X >= LAB_X / 2 && Player.Y >= LAB_Y / 2)			//quadrant unten rechts
	{
		if (LAB_X - Player.X < LAB_Y - Player.Y)
		{
			return 'r';
		}
		else {
			return 'd';
		}
	}
	else if (Player.X >= LAB_X / 2 && Player.Y < LAB_Y / 2)		//quadrant oben rechts
	{
		if (LAB_X - Player.X < Player.Y)
		{
			return 'r';
		}
		else {
			return 'u';
		}
	}
	else if (Player.X < LAB_X / 2 && Player.Y >= LAB_Y / 2)		//Quadrant unten links
	{
		if (Player.X < LAB_Y - Player.Y)
		{
			return 'l';
		}
		else {
			return 'd';
		}
	}
	else if (Player.X < LAB_X / 2 && Player.Y < LAB_Y / 2)		//Quadrant oben links
	{
		if (Player.X < Player.Y)
		{
			return 'l';
		}
		else {
			return 'u';
		}
	}
	return 0;
}

char findDirection() {
	char dir;
	for(int i = 0; i < 4; i++)
	{
		dir = directions[i];
		if (brainMap[Player.Y + yOffset(dir)][Player.X + xOffset(dir)] == '#' || brainMap[Player.Y + yOffset(dir)][Player.X + xOffset(dir)] == '$')
		return dir;
	}
	return 'u';
}

char findDirectionPath() {
	
	char dir;
	for(int i = 0; i < 4; i++)
	{
		dir = directions[i];
		if (brainMap[Player.Y + yOffset(dir)][Player.X + xOffset(dir)] == '#' || brainMap[Player.Y + yOffset(dir)][Player.X + xOffset(dir)] == ',' || brainMap[Player.Y + yOffset(dir)][Player.X + xOffset(dir)] == '$')
		return dir;
	}
	return 'u';
	/*dir = 'd';
	if (brainMap[Player.Y + yOffset(dir)][Player.X + xOffset(dir)] == '#' || brainMap[Player.Y + yOffset(dir)][Player.X + xOffset(dir)] == ',' || brainMap[Player.Y + yOffset(dir)][Player.X + xOffset(dir)] == '$')
		return dir;
	dir = 'u';
	if (brainMap[Player.Y + yOffset(dir)][Player.X + xOffset(dir)] == '#' || brainMap[Player.Y + yOffset(dir)][Player.X + xOffset(dir)] == ',' || brainMap[Player.Y + yOffset(dir)][Player.X + xOffset(dir)] == '$')
		return dir;
	dir = 'l';
	if (brainMap[Player.Y + yOffset(dir)][Player.X + xOffset(dir)] == '#' || brainMap[Player.Y + yOffset(dir)][Player.X + xOffset(dir)] == ',' || brainMap[Player.Y + yOffset(dir)][Player.X + xOffset(dir)] == '$')
		return dir;
	dir = 'r';
	if (brainMap[Player.Y + yOffset(dir)][Player.X + xOffset(dir)] == '#' || brainMap[Player.Y + yOffset(dir)][Player.X + xOffset(dir)] == ',' || brainMap[Player.Y + yOffset(dir)][Player.X + xOffset(dir)] == '$')
		return dir;
	return 'u';*/	
}

void waitFor(long msec) {
	Sleep(50);
	//unsigned int retTime = time(0) + secs;
	//while (time(0) < retTime);
}

void makeMap()
{
	int x = 0, y = 0;

	for (int i = 0; i < LAB_Y; i++)
	{
		for (int j = 0; j < LAB_X; j++)
		{
			brainMap[i][j] = ' ';
		}
		printf("\n");
	}

	for (x = 0; x < LAB_X; x++)
	{
		brainMap[0][x] = '#';
		brainMap[LAB_Y - 1][x] = '#';
	}

	for (y = 0; y < LAB_Y; y++)
	{
		brainMap[y][0] = '#';
		brainMap[y][LAB_X - 1] = '#';
	}
}

void nextPath()
{
	for (int i = 0; i < LAB_Y; i++) {
		for (int j = 0; j < LAB_X; j++)
		{
			if (brainMap[i][j] == '.') brainMap[i][j] = ',';
		}
	}
}

void showFrame()
{
	system("cls");
	/*printf("\n\nLab-View: \n\n");
	for (int i = 0; i < LAB_Y; i++)
	{
		for (int j = 0; j < LAB_X; j++)
		{
			printf("%c", lab[i][j]);
		}
		printf("\n");
	}*/
	printf("\n\nBrain-Map-View: \n\n");
	for (int i = 0; i < LAB_Y; i++)
	{
		for (int j = 0; j < LAB_X; j++)
		{
			if(brainMap[i][j] == 'X'){
			printf("\033[35m\033[1m%c\033[0m\033[0m\033[40m", brainMap[i][j]);
			}
			else if(brainMap[i][j] == 'f'){
			printf("\033[0;32m\033[1m%c\033[0m", brainMap[i][j]);
			}
			else if(brainMap[i][j] == 'G'){
			printf("\033[0;33m\033[1m%c\033[0m", brainMap[i][j]);
			}
			else if(brainMap[i][j] == '#'){
			printf("\033[46m\033[30m%c\033[0m", brainMap[i][j]);
			}
			else if (brainMap[i][j] == 'M') {
				printf("\033[41m%c\033[40m", brainMap[i][j]);
			}
			else if(brainMap[i][j] == ' ')
				if (lab[i][j] == '#' || lab[i][j] == 'M') {
					printf("%c", lab[i][j]);
				}else if (lab[i][j] == 'G') {
					printf("\033[0;33m\033[1m%c\033[0m", lab[i][j]);
				}
				else {
					printf("%c", brainMap[i][j]);
				}
			else {
				printf("%c", brainMap[i][j]);
			}
		}
		printf("\n");
	}
	printf("\n\n\nSteps: %d \nGeneral Dir: %c \nPlayerX: %d \nPlayerY: %d", Player.Steps, generalDir, Player.X, Player.Y);
	waitFor(MILLIS);
}

void move(char command)
{
	brainMap[Player.Y][Player.X] = '.';
	lab[Player.Y][Player.X] = ' ';
	if (command == 'r')
	{
		Player.X++;
	}
	else if (command == 'l')
	{
		Player.X--;
	}
	else if (command == 'u')
	{
		Player.Y--;
	}
	else if (command == 'd')
	{
		Player.Y++;
	}
	brainMap[Player.Y][Player.X] = 'X';
	Player.Steps++;
	if (lab[Player.Y][Player.X] != 'G')
	{
		lab[Player.Y][Player.X] = 'X';
	}
	else
	{
		showFrame();
		char g = 'g';
		printf("\n\n\n\n\n\n\n\n\n\n");
		for (int i = 0; i < 25; i++) {
			for (int j = 0; j < 43; j++) {
				printf("%c", end[i][j]);
			}
		}
		exit(0);
	}
	if (Player.Steps % FRAMES == 0 && Player.Steps > STARTFRAME)
		showFrame();
	//showFrame();
}

int checkMoveWall(int y, int x)				//checks, if desired position to move to is a wall
{
	if (lab[y][x] == ' ' || lab[y][x] == ',' || lab[y][x] == '.' || lab[y][x] == 'G')
		return 1;
	brainMap[y][x] = '#';
	return 0;
}

void placeMonsterWall(int y, int x)
{
	brainMap[y + 1][x] = '#';
	brainMap[y][x + 1] = '#';
	brainMap[y - 1][x] = '#';
	brainMap[y][x - 1] = '#';
}

void findMonster()				//dis not working
{
	for (int y = 0; y < LAB_Y; y++) {
		for (int x = 0; x < LAB_X; x++) {
			if (brainMap[y][x] == '$') {
				if (y - 2 >= 0) {
					if (brainMap[y - 2][x] == '$') {
						if (brainMap[y - 1][x] == ' ') {
							brainMap[y - 1][x] = 'M';
							placeMonsterWall(y - 1, x);
							return;
						}
					}
				}
				if (y - 1 >= 0 && x + 1 <= LAB_X) {
					if (brainMap[y - 1][x + 1] == '$') {
						if (brainMap[y - 1][x] == '.' || brainMap[y - 1][x] == ',' || brainMap[y - 1][x] == '#')
						{
							if (brainMap[y][x + 1] == ' ') {
								brainMap[y][x + 1] = 'M';
								placeMonsterWall(y, x + 1);
								return;
							}
						}
						else if (brainMap[y][x + 1] == '.' || brainMap[y][x + 1] == ',' || brainMap[y][x + 1] == '#')
						{
							if (brainMap[y - 1][x] == ' ') {
								brainMap[y - 1][x] = 'M';
								placeMonsterWall(y - 1, x);
								return;
							}
						}
					}
				}
				if (x + 2 <= LAB_X) {
					if (brainMap[y][x + 2] == '$') {
						if (brainMap[y][x + 1] == ' ') {
							brainMap[y][x + 1] = 'M';
							placeMonsterWall(y, x + 1);
							return;
						}
					}
				}
				if (y + 1 <= LAB_Y && x + 1 <= LAB_X) {
					if (brainMap[y + 1][x + 1] == '$') {
						if (brainMap[y + 1][x] == '.' || brainMap[y + 1][x] == ',' || brainMap[y + 1][x] == '#')
						{
							if (brainMap[y][x + 1] == ' ') {
								brainMap[y][x + 1] = 'M';
								placeMonsterWall(y, x + 1);
								return;
							}
						}
						else if (brainMap[y][x + 1] == '.' || brainMap[y][x + 1] == ',' || brainMap[y][x + 1] == '#')
						{
							if (brainMap[y + 1][x] == ' ') {
								brainMap[y + 1][x] = 'M';
								placeMonsterWall(y + 1, x);
								return;
							}
						}
					}
				}
				if (y + 2 <= LAB_Y) {
					if (brainMap[y + 2][x] == '$') {
						if (brainMap[y + 1][x] == ' ') {
							brainMap[y + 1][x] = 'M';
							placeMonsterWall(y + 1, x);
							return;
						}
					}
				}
				if (y + 1 <= LAB_Y && x - 1 >= 0) {
					if (brainMap[y + 1][x - 1] == '$') {
						if (brainMap[y + 1][x] == '.' || brainMap[y + 1][x] == ',' || brainMap[y + 1][x] == '#') {
							if (brainMap[y][x - 1] == ' ') {
								brainMap[y][x - 1] = 'M';
								placeMonsterWall(y, x - 1);
								return;
							}
						}
					}
					else if (brainMap[y][x - 1] == '.' || brainMap[y][x - 1] == ',' || brainMap[y][x - 1] == '#') {
						if (brainMap[y + 1][x] == ' ') {
							brainMap[y + 1][x] = 'M';
							placeMonsterWall(y + 1, x);
							return;
						}
					}
				}
				if (x - 2 >= 0) {
					if (brainMap[y][x - 2] == '$') {
						if (brainMap[y][x - 1] == ' ') {
							brainMap[y][x - 1] = 'M';
							placeMonsterWall(y, x - 1);
							return;
						}
					}
				}
				if (y - 1 >= 0 && x - 1 >= 0) {
					if (brainMap[y - 1][x - 1] == '$') {
						if (brainMap[y][x - 1] == '.' || brainMap[y][x - 1] == ',' || brainMap[y][x - 1] == '#')
						{
							if (brainMap[y - 1][x] == ' ') {
								brainMap[y - 1][x] = 'M';
								placeMonsterWall(y - 1, x);
								return;
							}
						}
						else if (brainMap[y - 1][x] == '.' || brainMap[y - 1][x] == ',' || brainMap[y - 1][x] == '#')
						{
							if (brainMap[y][x - 1] == ' ') {
								brainMap[y][x - 1] = 'M';
								placeMonsterWall(y, x - 1);
								return;
							}
						}
					}
				}
				else {
					//Kein Monster eindeutig bestimmbar
				}
			}
		}
	}
}

int checkMoveMonster(int y, int x)			//checks, if desired position to move to is occupied by a monster
{
	if (lab[y + 1][x] != 'M' && lab[y - 1][x] != 'M' && lab[y][x + 1] != 'M' && lab[y][x - 1] != 'M')
		return 1;
	if (brainMap[y][x] != '#')
		brainMap[y][x] = '$';
	findMonster();
	return 0;
}

void startGame()		//resets player steps to 0, puts player in his starting position
{
	Player.Steps = 0;
	Player.X = START_POS_X;
	Player.Y = START_POS_Y;
	brainMap[Player.Y][Player.X] = 'X';
	lab[Player.Y][Player.X] = 'X';
}

int xOffset(char dir)
{
	switch (dir) {
	case 'u': return 0;
		break;
	case 'd': return 0;
		break;
	case 'r': return 1;
		break;
	case 'l': return -1;
		break;
	}
}

int yOffset(char dir)
{
	switch (dir) {
	case 'u': return -1;
		break;
	case 'd': return 1;
		break;
	case 'r': return 0;
		break;
	case 'l': return 0;
		break;
	}
}

int desiredMove(char dir)
{
	if (checkMoveWall(Player.Y + yOffset(dir), Player.X + xOffset(dir)) && checkMoveMonster(Player.Y + yOffset(dir), Player.X + xOffset(dir)))
	{
		move(dir);
		return 1;
	}
	return 0;
}

int desiredMoveWall(char dir)
{
	if (checkMoveWall(Player.Y + yOffset(dir), Player.X + xOffset(dir)) && checkMoveMonster(Player.Y + yOffset(dir), Player.X + xOffset(dir)) && brainMap[Player.Y + yOffset(dir)][Player.X + xOffset(dir)] != ',')
	{
		move(dir);
		return 1;
	}
	return 0;
}

char alternateDirRight(char c)
{
	switch (c) {
	case 'u':
		return 'r';
		break;
	case 'r':
		return 'd';
		break;
	case 'd':
		return 'l';
		break;
	case 'l':
		return 'u';
		break;
	}
}

char alternateDirLeft(char c)
{
	switch (c) {
	case 'u':
		return 'l';
		break;
	case 'r':
		return 'u';
		break;
	case 'd':
		return 'r';
		break;
	case 'l':
		return 'd';
		break;
	}
}

char oppositeDir(char c)
{
	return alternateDirLeft(alternateDirLeft(c));
}

char bestDir()
{
	if (brain[Player.Y + 1][Player.X] != ' ')
		return 'd';
	if (brain[Player.Y - 1][Player.X] != ' ')
		return 'u';
	if (brain[Player.Y][Player.X + 1] != ' ')
		return 'r';
	if (brain[Player.Y][Player.X - 1] != ' ')
		return 'l';
}

void moveToWall()			//Player is supposed to move to the outer wall closest to him     
{
	char dir = startDirection();
	while (Player.X != 1 && Player.X != LAB_X - 2 && Player.Y != 1 && Player.Y != LAB_Y - 2)
	{
		/*if (checkMoveWall(Player.Y + yOffset(dir), Player.X + xOffset(dir)) && checkMoveMonster(Player.Y + yOffset(dir), Player.X + xOffset(dir)))
		{
			move(dir);
		}*/
		if (desiredMove(dir))
		{
		}
		else
		{
			dir = alternateDirRight(dir);
		}
		generalDir = dir;
	}
}

int clamp(int var, int min, int max) {
	if (var <= min) {
		return min;
	}
	if (var >= max) {
		return max;
	}
	return var;
}

float distance(int y, int x)
{
	return sqrt(pow(Player.X - x, 2) + pow(Player.Y - y, 2));
}

struct Pos brainRadar()			//Finds the next empty Place in Brainmap
{
	struct Pos closest;
	int radius = 1;
	int i, j, y, x;
	while (radius < 100)
	{
		for (i = -radius; i <= radius; i++)
		{
			for (j = -radius; j <= radius; j++)
			{
				y = Player.Y + j;
				x = Player.X + i;

				y = clamp(y, 0, LAB_Y - 1);
				x = clamp(x, 0, LAB_X - 1);

				if (brainMap[y][x] == ' ')
				{
					closest.X = x;
					closest.Y = y;
					brainMap[y][x] = 'f';
					return closest;
				}
			}
		}
		radius++;
	}
}

void moveAlongWall()			//player is supposed to move along the wall/dots next to him
{
	char dir = findDirection();
	int startPosX = Player.X;
	int startPosY = Player.Y;
	int startSteps = Player.Steps;
	while (startPosX != Player.X || startPosY != Player.Y || Player.Steps == startSteps)			//checks if actual position is same as starting position or if zero steps were made
	{
		if (desiredMove(alternateDirLeft(dir)))
		{
			dir = alternateDirLeft(dir);
		}
		else if (desiredMove(dir))
		{
		}
		else
		{
			dir = alternateDirRight(dir);
		}
	}
	nextPath();
}

void moveAlongPath()
{
	char dir = findDirectionPath();
	int startPosX = Player.X;
	int startPosY = Player.Y;
	int startSteps = Player.Steps;
	int computing = 0;
	while ((startPosX != Player.X || startPosY != Player.Y || Player.Steps == startSteps) && computing < 10)			//checks if actual position is same as starting position or if zero steps were made
	{
		if (desiredMoveWall(alternateDirLeft(dir)))
		{
			dir = alternateDirLeft(dir);
			computing = 0;
		}
		else if (desiredMoveWall(dir))
		{
			computing = 0;
		}
		else
		{
			dir = alternateDirRight(dir);
		}
		computing++;
		
	}
	nextPath();
}

void avoidWall(int y, int x, char dir)
{
	//dir = alternateDirRight(dir);
	dir = findDirection();
	int startPosX = Player.X;
	int startPosY = Player.Y;
	int startSteps = Player.Steps;
	float prevDis;
	do
	{
		prevDis = distance(y, x);
		if (desiredMove(alternateDirLeft(dir)))
		{
			dir = alternateDirLeft(dir);
		}
		else if (desiredMove(dir))
		{
		}
		else
		{
			dir = alternateDirRight(dir);
		}
	} while (prevDis < distance(y, x));
	dir = findDirection();
	do
	{
		prevDis = distance(y, x);
		if (desiredMove(alternateDirLeft(dir)))
		{
			dir = alternateDirLeft(dir);
		}
		else if (desiredMove(dir))
		{
		}
		else
		{
			dir = alternateDirRight(dir);
		}
	} while (prevDis > distance(y, x));
}

void moveTo(int y, int x)
{

	char dir;
	int b = 1, c = 1;

	if (y < Player.Y) { dir = 'u'; }
	else if (y > Player.Y) { dir = 'd'; }
	//else { b = 0; }
	while (Player.Y != y)
	{
		if (!desiredMove(dir))
			break;
	}
	if (x < Player.X) { dir = 'l'; }
	else if (x > Player.X) { dir = 'r'; }
	//else { b = 0; }
	while (Player.X != x)
	{
		if (!desiredMove(dir))
			break;
	}
	while (Player.X != x || Player.Y != y)
	{
		avoidWall(y, x, dir);
		if (y < Player.Y) { dir = 'u'; }
		else if (y > Player.Y) { dir = 'd'; }
		//else { b = 0; }
		while (Player.Y != y)
		{
			if (!desiredMove(dir))
				break;
		}
		if (x < Player.X) { dir = 'l'; }
		else if (x > Player.X) { dir = 'r'; }
		//else { b = 0; }
		while (Player.X != x)
		{
			if (!desiredMove(dir))
				break;
		}
	}

	nextPath();
}

void clearNode()
{
	for (int i = 0; i <= LAB_Y - 1; i++)
	{
		for (int j = 0; j <= LAB_X - 1; j++)
		{
			map[i][j].visited = 0;
			map[i][j].distance = -1;
			map[i][j].parent = 'N';
		}
	}
}

struct Pos aStar(int mode)
{
	clearNode();
	int dis = 0;
	char dir;
	struct Pos a;
	map[Player.Y][Player.X].distance = 0;
	map[Player.Y][Player.X].visited = 1;


	while (dis < 5000)
	{
		for (int i = 1; i <= LAB_Y - 2; i++)
		{
			for (int j = 1; j <= LAB_X - 2; j++)
			{
				if (map[i][j].distance == dis)
				{
					
					for(int k = 0; k < 4; k++)
					{
						dir = directions[k];
						if (brainMap[i + yOffset(dir)][j + xOffset(dir)] != '#' && brainMap[i + yOffset(dir)][j + xOffset(dir)] != '$' && map[i + yOffset(dir)][j + xOffset(dir)].visited != 1)
						{
							map[i + yOffset(dir)][j + xOffset(dir)].visited = 1;
							map[i + yOffset(dir)][j + xOffset(dir)].distance = (dis + 1);
							map[i + yOffset(dir)][j + xOffset(dir)].parent = dir;
							if (mode && brainMap[i + yOffset(dir)][j + xOffset(dir)] == ' ') {
								a.X = j + xOffset(dir);
								a.Y = i + yOffset(dir);
								return a;
							}
						}
					}
				}
			}
		}
		dis++;
	}
}

int moveTo2(int y, int x)
{
	int x2 = x, y2 = y, pos = 0;
	char route[5000];
	aStar(0);

	if(map[y][x].parent == 'N')
	{
		brainMap[y][x] = '#';
		return 1;
	}

	while (x2 != Player.X || y2 != Player.Y)
	{
		route[pos] = map[y2][x2].parent;
		y2 = y2 + yOffset(oppositeDir(route[pos]));
		x2 = x2 + xOffset(oppositeDir(route[pos]));
		pos++;
	}
	pos--;
	for (int i = pos; i >= 0; i--)
	{
		if (desiredMove(route[i]))
		{
		}
		else
		{
			generalDir = route[i];
			moveAlongWall();
			moveTo2(y, x);
			return 0;
		}
	}
	nextPath();
	return 0;


}

int moveToNextFree()
{
	struct Pos free;
	free = aStar(1);
	int x2 = free.X, y2 = free.Y, pos = 0;
	char route[5000];
	brainMap[free.Y][free.X] = 'f';

	if(map[free.Y][free.X].parent == 'N')
	{
		brainMap[free.Y][free.X] = '#';
		return 1;
	}

	while (x2 != Player.X || y2 != Player.Y)
	{
		route[pos] = map[y2][x2].parent;
		y2 = y2 + yOffset(oppositeDir(route[pos]));
		x2 = x2 + xOffset(oppositeDir(route[pos]));
		pos++;
	}
	pos--;
	for (int i = pos; i >= 0; i--)
	{
		if (desiredMove(route[i]))
		{
		}
		else
		{
			generalDir = route[i];
			moveAlongWall();
			moveToNextFree();
			return 0;
		}
	}
	nextPath();
	return 0;
}

void main()
{
	struct Pos test;
	int a;
	makeMap(lab);
	startGame();
	showFrame();
	while (desiredMove('u'))
	{}
	moveAlongWall();
	while (1)
	{
		if (moveToNextFree())
			continue;
		moveAlongPath();
	}
}