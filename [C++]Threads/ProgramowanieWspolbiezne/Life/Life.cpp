// Life.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <vector>
#include <windows.h>
#include <thread>
#include <mutex>

#define Size 20
int toAdd = Size*Size/16;
int table[Size][Size];
int table2[Size][Size];
int table3[Size][Size];
std::mutex MutezTable[Size][Size];
std::mutex barrier;
struct point {
	int x;
	int y;
};

void GenerateScene() {
	for (int i = 0; i < Size; i++)
		for (int j = 0; j < Size; j++)
			table[i][j] = 0;

	while (toAdd > 0) {
		int x = rand() % Size;
		int y = rand() % Size;

		if (table[x][y] != 1 || table[x][y] != 2 || table[x][y] != 3 || table[x][y] != 4) {
			table[x][y] = rand()%4+1;
			toAdd--;
		}
	}
}

void print() {
	for (int i = 0; i < Size; i++) {
		for (int j = 0; j < Size; j++)
			if(table[i][j]!=0)
				printf("% 2d", table[i][j]);
			else
				printf("  ");

	printf("\n");
	}
}
int isAlive(int x, int y)
{
	int toReturn = 0;
	try
	{
		if(x >=0 && x<Size && y >=0 && y <Size)
		{
			MutezTable[x][y].lock();
			if (table[x][y] != 0)
				toReturn = 1;
			MutezTable[x][y].unlock();
		}
	}catch(int a)
	{
		;
	}
	return toReturn;
}
int getNeib(int x, int y) {
	int nerb = 0;
		nerb += isAlive(x-1,y-1);
		nerb += isAlive(x+1,y-1);
		nerb += isAlive(x+1,y+1);
		nerb += isAlive(x-1,y+1);
		nerb += isAlive(x-1,y);
		nerb += isAlive(x+1,y);
		nerb += isAlive(x,y-1);
		nerb += isAlive(x,y+1);

	return nerb;
}

void run(int type)
{
	switch(type)
	{
		case 0:
				for (int i = 0; i < Size; i++)
				{
					for (int j = 0; j < Size; j++)
					{
						// == 0 i ma 3 kolegów rodzi siê do ¿ycia
						if (table[i][j] == 0 && getNeib(i, j) == 3)
						{
							MutezTable[i][j].lock();
							table[i][j] = type+1;
							MutezTable[i][j].unlock();
						}
						// == 1 i ma 2 lub 3 to nic a inaczej to ginie
						if (table[i][j] == type+1 && (getNeib(i, j) == 2 || getNeib(i, j) == 3))
						{
							//posiada 2/3 sasiadów dalej ¿yje
							MutezTable[i][j].lock();
							table[i][j] = type+1;
							MutezTable[i][j].unlock();
						}
						else
						{
							if (table[i][j] == type + 1)
							{
								//posiada 0/1 lub wiecej jak 3 s¹diadów umiera
								MutezTable[i][j].lock();
								table[i][j] = 0;
								MutezTable[i][j].unlock();
							}
						}
					}
				}
			break;
		case 1:
				for (int i = Size-1; i >= 0 ; i--)
				{
					for (int j = Size-1; j >= 0; j--)
					{
						// == 0 i ma 3 kolegów rodzi siê do ¿ycia
						if (table[i][j] == 0 && getNeib(i, j) == 3)
						{
							MutezTable[i][j].lock();
							table[i][j] = type+1;
							MutezTable[i][j].unlock();
						}

						// == 1 i ma 2 lub 3 to nic a inaczej to ginie
						if (table[i][j] == type + 1 && (getNeib(i, j) == 2 || getNeib(i, j) == 3))
						{
							//posiada 2/3 sasiadów dalej ¿yje
							MutezTable[i][j].lock();
							table[i][j] = type+1;
							MutezTable[i][j].unlock();
						}
						else
						{
							if (table[i][j] == type + 1)
							{
								//posiada 0/1 lub wiecej jak 3 s¹diadów umiera
								MutezTable[i][j].lock();
								table[i][j] = 0;
								MutezTable[i][j].unlock();
							}
						}
					}
				}
			break;
		case 2:
				for (int i = 0; i < Size; i++)
				{
					for (int j = Size-1; j >= 0; j--)
					{
						// == 0 i ma 3 kolegów rodzi siê do ¿ycia
						if (table[i][j] == 0 && getNeib(i, j) == 3)
						{
							MutezTable[i][j].lock();
							table[i][j] = type+1;
							MutezTable[i][j].unlock();
						}

						// == 1 i ma 2 lub 3 to nic a inaczej to ginie
						if (table[i][j] == type + 1 && (getNeib(i, j) == 2 || getNeib(i, j) == 3))
						{
							//posiada 2/3 sasiadów dalej ¿yje
							MutezTable[i][j].lock();
							table[i][j] = type + 1;
							MutezTable[i][j].unlock();
						}
						else
						{
							if (table[i][j] == type + 1)
							{
								//posiada 0/1 lub wiecej jak 3 s¹diadów umiera
								MutezTable[i][j].lock();
								table[i][j] = 0;
								MutezTable[i][j].unlock();
							}
						}
					}
				}
			break;
		case 3:
				for (int i = Size-1; i >= 0; i--)
				{
					for (int j = Size-1; j >= 0; j--)
					{
						// == 0 i ma 3 kolegów rodzi siê do ¿ycia
						if (table[i][j] == 0 && getNeib(i, j) == 3)
						{
							MutezTable[i][j].lock();
							table[i][j] = type+1;
							MutezTable[i][j].unlock();
						}

						// == 1 i ma 2 lub 3 to nic a inaczej to ginie
						if (table[i][j] == type + 1 && (getNeib(i, j) == 2 || getNeib(i, j) == 3))
						{
							//posiada 2/3 sasiadów dalej ¿yje
							MutezTable[i][j].lock();
							table[i][j] = type+1;
							MutezTable[i][j].unlock();
						}
						else
						{
							if (table[i][j] == type + 1)
							{
								//posiada 0/1 lub wiecej jak 3 s¹diadów umiera
								MutezTable[i][j].lock();
								table[i][j] = 0;
								MutezTable[i][j].unlock();
							}
						}
					}
				}
			break;
		default:break;
	}
}


int main()
{
	srand(time(NULL));
	GenerateScene();
	print();
	//pokój 104 wi2.
	getchar();
	getchar();
	while(true)
	{
		system("cls");
		print();
		std::thread t1(run, 0);
		std::thread t2(run, 1);
		std::thread t3(run, 2);
		std::thread t4(run, 3);

		t1.join();
		t2.join();
		t3.join();
		t4.join();
		Sleep(250);
	}

	getchar();
	getchar();
    return 0;
}
