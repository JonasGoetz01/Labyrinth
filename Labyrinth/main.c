#include <stdio.h>
#include <time.h>

#define LAB_Y 9
#define LAB_X 27
#define START_POS_X 16
#define START_POS_Y	3

struct Pos
{
	int X;
	int Y;
	int Steps;
};

char lab[LAB_Y][LAB_X] ={{ '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#', },
     { '#',' ',' ',' ',' ',' ',' ','M',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ','#', },
	 { '#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ','#', },
	 { '#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ','#',' ',' ',' ','G',' ',' ','#', },
	 { '#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#','#','#',' ',' ',' ',' ',' ',' ','#', },
	 { '#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#', },
	 { '#',' ',' ','#','#','#','#','#','#','#','#','#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#', },
	 { '#',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','M',' ',' ','#', },
	 { '#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#','#', } };
char brainMap[LAB_Y][LAB_X];
char brain[LAB_Y][LAB_X];
char generalDir;
struct Pos Player;

char startDirection()				//stellt fest, in welchem Quadranten sich der Spieler befindet und in welcher Bewegungsrichtung die Wand am schnellsten erreicht werden kann
{
	if (Player.X >= LAB_X/2 && Player.Y >= LAB_Y/2)			//quadrant unten rechts
	{
		if(LAB_X - Player.X < LAB_Y - Player.Y)
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
	}else if (Player.X < LAB_X / 2 && Player.Y >= LAB_Y / 2)		//Quadrant unten links
	{
		if (Player.X < LAB_Y - Player.Y)
		{
			return 'l';
		}
		else {
			return 'd';
		}
	}else if (Player.X < LAB_X / 2 && Player.Y < LAB_Y / 2)		//Quadrant oben links
	{
		if (Player.X < Player.Y)
		{
			return 'l';
		}
		else {
			return 'u';
		}
	}
}

void waitFor(unsigned int secs) {
	unsigned int retTime = time(0) + secs;  
	while (time(0) < retTime);      
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
		brainMap[LAB_Y-1][x] = '#';
	}
	
	for (y = 0; y < LAB_Y; y++)
	{
		brainMap[y][0] = '#';
		brainMap[y][LAB_X-1] = '#';
	}
}

void nextPath() 
{
	for (int i = 0; i < LAB_Y; i++) {
		for (int j = 0; j< LAB_X; j++)
		{
			if (brainMap[i][j] == '.') brainMap[i][j] = ',';
		}
	}
}

void showFrame()
{
	system("cls");
	printf("\n\nLab-View: \n\n");
	for (int i = 0; i < LAB_Y; i++)
	{
		for (int j = 0; j < LAB_X; j++)
		{
			printf("%c", lab[i][j]);
		}
		printf("\n");
	}
	printf("\n\nBrain-Map-View: \n\n");
	for (int i = 0; i < LAB_Y; i++)
	{
		for (int j = 0; j < LAB_X; j++)
		{
			printf("%c", brainMap[i][j]);
		}
		printf("\n");
	}
	printf("\n\n\nSteps: %d \nGeneral Dir: %c \nPlayerX: %d \nPlayerY: %d", Player.Steps, generalDir, Player.X, Player.Y);
	waitFor(1);
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
		exit(0);
	}

	if (Player.Steps % 1 == 0) { showFrame(); }
}

int getPlayerX()
{
	return Player.X;
}

int getPlayerY()
{
	return Player.Y;
}

void setPlayerX(int x)
{
	Player.X = x;
}

void setPlayerY(int y)
{
	Player.Y = y;
}

char getElement(int y, int x)
{
	return (brainMap[y][x]);
}

int checkMoveWall(int y, int x)				//checks, if desired position to move to is a wall
{
	if (lab[y][x] == ' ' || lab[y][x] == ',' || lab[y][x] == '.' || lab[y][x] == 'G')
		return 1;
	brainMap[y][x] = '#';
	return 0;
}

void findMonster()				//dis not working
{
	for (int y = 0; y < LAB_Y; y++) {
		for (int x = 0; x < LAB_X; x++) {
			if (brainMap[y][x] == '$') {
				if (y - 2 >= 0) {
					if (brainMap[y - 2][x] == '$') {
						brainMap[y - 1][x] = "M";
						return;
					}
				}
				if (y - 1 >= 0 && x + 1 <= LAB_X) {
					if (brainMap[y - 1][x + 1] == '$') {
						if (brainMap[y - 1][x] == '.' || brainMap[y - 1][x] == ',' || brainMap[y - 1][x] == '#')
						{
							brainMap[y][x + 1] = 'M';
							return;
						}
						else if (brainMap[y][x + 1] == '.' || brainMap[y][x + 1] == ',' || brainMap[y][x + 1] == '#')
						{
							brainMap[y - 1][x] = 'M';
							return;
						}
					}
				}
				if (x + 2 <= LAB_X) {
					if (brainMap[y][x + 2] == '$') {
						brainMap[y][x + 1] = 'M';
						return;
					}
				}
				if (y + 1 <= LAB_Y && x + 1 <= LAB_X) {
					if (brainMap[y + 1][x + 1] == '$') {
						if (brainMap[y + 1][x] == '.' || brainMap[y + 1][x] == ',' || brainMap[y + 1][x] == '#')
						{
							brainMap[y][x + 1] = 'M';
							return;
						}
						else if (brainMap[y][x + 1] == '.' || brainMap[y][x + 1] == ',' || brainMap[y][x + 1] == '#')
						{
							brainMap[y + 1][x] = 'M';
							return;
						}
					}
				}
				if (y + 2 <= LAB_Y) {
					if (brainMap[y + 2][x] == '$') {
						brainMap[y + 1][x] = 'M';
						return;
					}
				}
				if (y + 1 <= LAB_Y && x - 1 >= 0) {
					if (brainMap[y + 1][x - 1] == '$') {
						if (brainMap[y + 1][x] == '.' || brainMap[y + 1][x] == ',' || brainMap[y + 1][x] == '#') {
							brainMap[y][x - 1] = 'M';
							return;
						}
					}
					else if (brainMap[y][x - 1] == '.' || brainMap[y][x - 1] == ',' || brainMap[y][x - 1] == '#') {
						brainMap[y + 1][x] = 'M';
						return;
					}
				}
				if (x - 2 >= 0) {
					if (brainMap[y][x - 2] == '$') {
						brainMap[y][x - 1] = 'M';
						return;
					}
				}
				if (y - 1 >= 0 && x - 1 >= 0) {
					if (brainMap[y - 1][x - 1] == '$') {
						if (brainMap[y][x - 1] == '.' || brainMap[y][x - 1] == ',' || brainMap[y][x - 1] == '#')
						{
							brainMap[y - 1][x] = 'M';
							return;
						}
						else if (brainMap[y - 1][x] == '.' || brainMap[y - 1][x] == ',' || brainMap[y - 1][x] == '#')
						{
							brainMap[y][x - 1] = 'M';
							return;
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
	if (checkMoveWall(Player.Y + yOffset(dir), Player.X + xOffset(dir)) && checkMoveMonster(Player.Y + yOffset(dir), Player.X + xOffset(dir)) && brainMap[Player.Y + yOffset(dir)][Player.X + xOffset(dir)] != ',' )
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
		if(desiredMove(dir))
			{}
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
	return sqrt(pow(Player.X - x, 2) + pow(Player.Y - y), 2);
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
	char dir = alternateDirRight(generalDir);
	int startPosX = Player.X;
	int startPosY = Player.Y;
	int startSteps = Player.Steps;
	while(startPosX != Player.X || startPosY != Player.Y || Player.Steps == startSteps)			//checks if actual position is same as starting position or if zero steps were made
	{
		if (desiredMove(alternateDirLeft(dir))) 
		{
			dir = alternateDirLeft(dir);
		}
		else if(desiredMove(dir))
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
	char dir = alternateDirRight(bestDir());
	int startPosX = Player.X;
	int startPosY = Player.Y;
	int startSteps = Player.Steps;
	while(startPosX != Player.X || startPosY != Player.Y || Player.Steps == startSteps)			//checks if actual position is same as starting position or if zero steps were made
	{
		if (desiredMoveWall(alternateDirLeft(dir))) 
		{
			dir = alternateDirLeft(dir);
		}
		else if(desiredMoveWall(dir))
		{
		}
		else
		{
		dir = alternateDirRight(dir);
		}
	}
	nextPath();
}

void avoidWall(int y, int x, char dir)
{
	dir = alternateDirRight(dir);
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
		else if(desiredMove(dir))
		{
		}
		else
		{
		dir = alternateDirRight(dir);
		}
	} while (prevDis < distance(y, x));
	/*do
	{
		prevDis = distance(y, x);
		if (desiredMove(alternateDirLeft(dir))) 
		{
			dir = alternateDirLeft(dir);
		}
		else if(desiredMove(dir))
		{
		}
		else
		{
		dir = alternateDirRight(dir);
		}
	} while (prevDis > distance(y, x));*/
}

void moveTo(int y, int x)
{
	char dir;
	int b = 1, c = 1;
	if (y < Player.Y) { dir = 'u'; }
	else if (y > Player.Y) { dir = 'd'; }
	else { b = 0; }
	
	while (Player.Y != y && b)
	{
		if (!desiredMove(dir))
			break;
	}
	if (x < Player.X) { dir = 'l'; }
	else if (x > Player.X) { dir = 'r'; }
	else { b = 0; }
	while (Player.X != x && b)
	{
		if (!desiredMove(dir))
			break;
	}
	while(Player.X != x || Player.Y != y)
	{
		avoidWall(y, x, dir);
		while (Player.Y != y && b)
		{
			if (!desiredMove(dir))
			break;
		}
		if (x < Player.X) { dir = 'l'; }
		else if (x > Player.X) { dir = 'r'; }
		else { b = 0; }
		while (Player.X != x && b)
		{
			if (!desiredMove(dir))
				break;
		}
	}

	nextPath();

}

void moveToNextFree()
{
	struct Pos free;
	free = brainRadar();
	moveTo(free.Y, free.X);
}

void main()
{
	struct Pos test;
	makeMap(lab);
	startGame();
	showFrame();
	moveToWall();
	moveAlongWall();
	while(1)
	{
		moveToNextFree();
		moveAlongPath();
	}
	
	showFrame();
	
}