// magicSquare.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

#define RowToSkip 0
#define Size 5


struct Point
{
	int x;
	int y;
	int value;
};

int f(int n, int x, int y)
{
	return (x + y * 2 + 1) % n;
}

//std::vector<std::vector<int>> table;
int table[Size][Size];
std::mutex MutexTable[Size][Size];
std::vector<Point> ElementsToHide;
int count = 0;
Point LastPoint;
int Suma = 0;
bool rows;
bool cols;
bool diaR;
bool diaL;

int SumValue;
void diagL()
{
	Point a;
	SumValue = 0;
	std::vector<Point> place;
	for (int i = Size - 1; i > 0; i--)
	{
		MutexTable[i][i].lock();
		if (table[i][i] == -1)
		{
			a.x = i;
			a.y = i;
			place.push_back(a);
		}
		else
		{
			SumValue += table[i][i];
		}
		MutexTable[i][i].unlock();
	}
	if (place.size() > 1 || place.size() == 0)
	{
		diaL = false;
		return;
	}

	MutexTable[place.front().x][place.front().y].lock();
	table[place.front().x][place.front().y] = Suma - SumValue;
	diaL = true;
	MutexTable[place.front().x][place.front().y].unlock();

}
void diagR()
{
	Point a;
	SumValue = 0;
	std::vector<Point> place;
	for (int i = 0; i < Size; i++)
	{
		MutexTable[i][i].lock();
		if (table[i][i] == -1)
		{
			a.x = i;
			a.y = i;
			place.push_back(a);
		}
		else
		{
			SumValue += table[i][i];
		}
		MutexTable[i][i].unlock();
	}
	if (place.size() > 1 || place.size() == 0)
	{
		diaR = false;
	}
	else
	{
		MutexTable[place.front().x][place.front().y].lock();
		table[place.front().x][place.front().y] = Suma - SumValue;
		diaR = true;
		MutexTable[place.front().x][place.front().y].unlock();
	}
}
void col()
{
	bool ToReturn = false;
	std::vector<Point> place;
	for (int j = 0; j<Size; j++)
	{
		Point a;
		SumValue = 0;
		place.clear();
		for (int i = 0; i < Size; i++)
		{
			MutexTable[i][j].lock();
			if (table[i][j] == -1)
			{
				a.x = i;
				a.y = j;
				place.push_back(a);
			}
			else
			{
				SumValue += table[i][j];
			}
			MutexTable[i][j].unlock();
		}

		if (place.size() == 1)
		{
			MutexTable[place.front().x][place.front().y].lock();
			table[place.front().x][place.front().y] = Suma - SumValue;
			ToReturn = true;
			MutexTable[place.front().x][place.front().y].unlock();
		}
	}
	cols = ToReturn;
}
void row()
{
	bool ToReturn = false;
	std::vector<Point> place;
	for (int j = 0; j<Size; j++)
	{
		Point a;
		SumValue = 0;
		place.clear();
		for (int i = 0; i < Size; i++)
		{
			MutexTable[j][i].lock();
			if (table[j][i] == -1)
			{
				a.x = j;
				a.y = i;
				place.push_back(a);
			}
			else
			{
				SumValue += table[j][i];
			}
			MutexTable[j][i].unlock();
		}

		if (place.size() == 1)
		{
			MutexTable[place.front().x][place.front().y].lock();
			table[place.front().x][place.front().y] = Suma - SumValue;
			ToReturn = true;
			MutexTable[place.front().x][place.front().y].unlock();
		}
	}
	rows = ToReturn;
};

void printTable()
{

	auto a = table[0][0];

	table[0][0] = a;
	//	printf("\n");
	std::cout << std::endl;
	for (int i = 0; i < Size; i++)
	{
		for (int j = 0; j < Size; j++)
			printf("% 4d", table[i][j]);
		//			std::cout << table[i][j];
		std::cout << std::endl;
		//		printf("\n");
	}
}
void ChoseElementToHide();
void HideElements();
void Hide(Point PointToHide);
void recoverTable();

bool isSolution()
{
	for (int i = 0; i < Size; i++)
		for (int j = 0; j < Size; j++)
			if (table[i][j] == -1)
				return false;
	return true;
};

int solve()
{
	int Tries = 5;

	while (Tries >0)
	{
		do
		{
			rows = false;
			cols = false;
			diaR = false;
			diaL = false;
			if (isSolution())
			{
				printf("~~~~~~~~~~~~~~~~~~~~\n");
				ChoseElementToHide();
				recoverTable();
				HideElements();
				printTable();
			}

			//watek na funkcje.
			std::thread rowThread(row);
			std::thread colThread(col);
			std::thread diaRThread(diagR);
			std::thread diaLThread(diagL);

			rowThread.join();
			colThread.join();
			diaRThread.join();
			diaLThread.join();

			printTable();
		} while ((rows == true || cols == true || diaR == true || diaL == true) || isSolution());
		Tries--;
		recoverTable();
		if (!ElementsToHide.empty())
			ElementsToHide.pop_back();
	}

	int depth = ElementsToHide.size();

	return depth;
}



void ChoseElementToHide()
{
	Point pointToHide;
	int sum = 0;
	do
	{
		sum = 0;
		do {
			pointToHide.x = rand() % Size;
		} while (pointToHide.x == RowToSkip);
		pointToHide.y = rand() % Size;

		for (auto p : ElementsToHide)
		{
			if (pointToHide.x == p.x && pointToHide.y == p.y)
				sum++;
		}
	} while (sum > 0);
	pointToHide.value = table[pointToHide.x][pointToHide.y];
	ElementsToHide.push_back(pointToHide);
}
void HideElements()
{
	for (auto e : ElementsToHide)
	{
		Hide(e);
	}
}
void Hide(Point PointToHide)
{
	table[PointToHide.x][PointToHide.y] = -1;
}
void recoverTable()
{
	for (auto e : ElementsToHide)
	{
		table[e.x][e.y] = e.value;
	}
}

int main()
{
	srand(time(NULL));

	int i, j, n = Size;

	for (i = 0; i < n; i++)
	{
		std::vector<int> a;
		for (j = 0; j < n; j++)
		{
			printf("% 4d", f(n, n - j - 1, i)*n + f(n, j, i) + 1);
			table[i][j] = f(n, n - j - 1, i)*n + f(n, j, i) + 1;
			//			a.push_back(f(n, n - j - 1, i)*n + f(n, j, i) + 1);
		}
		//		table.push_back(a);
		putchar('\n');
	}

	for (int i = 0; i < Size; i++)
		Suma += table[RowToSkip][i];

	printf("\nSuma = %d\n", Suma);


	printf("\n\n\n\nMaksymalna glebokosc przeszukiwan wynosi %d dla tablic %dx%d.\n", solve(), Size, Size);
	printTable();
	printf("\nSuma = %d\n", Suma);
	getchar();
	getchar();
	return 0;
}

