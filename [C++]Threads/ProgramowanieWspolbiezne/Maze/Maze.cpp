
#include "stdafx.h"
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>
using namespace std;

#define Maze_X 13
#define Maze_Y 10

class Point {
public:
	int x;
	int y;
	Point(int x, int y) :x(x), y(y) { ; };
	Point(Point &source)
	{
		x = source.x;
		y = source.y;
	}
	bool isEqual(Point point)
	{
		if (x == point.x && y == point.y)
			return true;
		return false;
	}
};

void CalculateFractal() {
	std::cout<<"Gello\n";
}

void RandomDirections();
void GenerateMaze();

int maze[10][13] = {
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1 },
	{ 1,0,1,0,1,0,1,0,0,0,0,0,1 },
	{ 1,0,1,0,0,0,1,0,1,1,1,0,1 },
	{ 1,0,0,0,1,1,1,0,0,0,0,0,1 },
	{ 1,0,1,0,0,0,0,0,1,1,1,0,1 },
	{ 1,0,1,0,1,1,1,0,1,0,0,0,1 },
	{ 1,0,1,0,1,0,0,0,1,1,1,0,1 },
	{ 1,0,1,0,1,1,1,0,1,0,1,0,1 },
	{ 1,0,0,0,0,0,0,0,0,0,1,0,1 },
	{ 1,1,1,1,1,1,1,1,1,1,1,1,1 } };

mutex mazeMutex[Maze_Y][Maze_X];
void printMaze();
vector<Point> getPossibleWays(Point point);
void solver(Point StartPoint, Point EndPoint);

bool Found = false;
int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

	Point StartPoint(1, 1);
	Point EndPoint(11, 8);

	printMaze();
	for (int i = 0; i < Maze_Y; i++)
	{
		for (int j = 0; j < Maze_X; j++)
		{
			if (maze[i][j] == 1)
			{
				mazeMutex[i][j].lock();
			}
		}
	}
	//zablokowanie startu.
	mazeMutex[StartPoint.y][StartPoint.x].lock();
	thread firstThread(solver, StartPoint, EndPoint);
	//czekanie na zakoñczenie w¹tku.
	firstThread.join();
	printMaze();
	if (Found)
		cout << "Znaleziono rozwiazanie." << endl;
	else
		cout << "Nie znaleziono rozwiazania." << endl;

	getchar();
	getchar();
	return 0;
}


void solver(Point StartPoint, Point EndPoint)
{
	Point PointToCheck(StartPoint);
	std::vector<thread> childThread;
	std::vector<Point> possibleWays;

	if (PointToCheck.isEqual(EndPoint))
	{
		Found = true;
		maze[PointToCheck.y][PointToCheck.x] = 6;
		return;
	}

	do
	{
		possibleWays = getPossibleWays(PointToCheck);

		if (possibleWays.size()>1)
			for (auto way = 0; way < possibleWays.size() - 1; way++)
				childThread.push_back(thread(solver, possibleWays[way], EndPoint));

		if (!possibleWays.empty())
			PointToCheck = possibleWays.back();

		if (PointToCheck.isEqual(EndPoint))
		{
			Found = true;
			maze[PointToCheck.y][PointToCheck.x] = 6;
		}

	} while (possibleWays.size() > 0 && !Found);

	//oczekiwanie na zakoñczenie siê wszystkich w¹tków
	for (int i = 0; i < childThread.size(); i++)
		childThread[i].join();
}

void printMaze()
{
	for (int y = 0; y<10; y++)
	{
		for (int x = 0; x<13; x++)
		{
			if (maze[y][x] != 0 && maze[y][x] != 1)
				std::cout<<maze[y][x];
			else
			{
				if (maze[y][x] == 0)
					std::cout << " ";
				else
					std::cout << "#";
			}
		}
		std::cout << "\n";
	} 
}
vector<Point> getPossibleWays(Point point)
{
	vector<Point> possible;
	int x = point.x;
	int y = point.y;

	if (x + 1 < Maze_X && maze[y][x + 1] == false)
		if (mazeMutex[y][x + 1].try_lock())
			possible.push_back(Point(x + 1, y));
	if (x - 1 >= 0 && maze[y][x - 1] == false)
		if (mazeMutex[y][x - 1].try_lock())
			possible.push_back(Point(x - 1, y));
	if (y + 1 < Maze_Y && maze[y + 1][x] == false)
		if (mazeMutex[y + 1][x].try_lock())
			possible.push_back(Point(x, y + 1));
	if (y - 1 >= 0 && maze[y - 1][x] == false)
		if (mazeMutex[y - 1][x].try_lock())
			possible.push_back(Point(x, y - 1));

	return possible;
}



