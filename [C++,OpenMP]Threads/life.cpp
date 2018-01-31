#include <iostream>
#include <exception>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <omp.h>
#include <fstream>


#define size 10
#define Thread 2
#define MaxTime 200
#define ProcentageItems 50
#define DebugMode 1

char a [2][size][size];
omp_lock_t locks [2][size][size];
omp_lock_t lock;
char ArrayToPrint = 0;
double avgTime = 0.0;
int barier = 0;

void Zapisz(){
  std::ofstream myfile;
  myfile.open ("Life.csv", std::ios::app);
  myfile <<Thread <<", " <<size <<", " <<MaxTime <<", "<< avgTime <<","<< std::endl;
  myfile.close();
}

void print(int t) {
	printf("Iteracja %d\n",t);
	for (int i = 0; i < size; i++) 
	{
		for (int j = 0; j < size; j++)
		{
			if(a[ArrayToPrint][i][j] != 0)
			{
				printf("% 2d", a[ArrayToPrint][i][j]);
			}
			else
			{
				printf(" .");
			}
		}
		printf("\n");
	}
	usleep(1000000 * 1);
}

// Prepare scene with random layout
void GenerateScene() 
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			a[0][i][j] = 0;
			a[1][i][j] = 0;
			omp_init_lock(&locks[0][i][j]);
			omp_init_lock(&locks[1][i][j]);
		}
	}

	long toAdd = (size * size)/100*ProcentageItems;

	while (toAdd > 0) 
	{
		int x = rand() % size;
		int y = rand() % size;

		if (a[0][x][y] == 0) 
		{
			a[0][x][y] = (rand() % 2) + 1;
			toAdd--;
		}
	}
}

char f(char s)
{
	return (s >= 3 && s<=4) ? 1 : 0;
}

char f2(char s)
{
	return (s >= 1 && s<=4) ? 2 : 0;
}

void barrier1(int t){
	// printf("====================\n");
	// printf("S1 - Barrier wchodzę\n");
	// printf("====================\n");
	omp_set_lock(&lock);
	// printf("S1 - Lock\n");
	if(barier == 0)
	{
		barier = 1;
		omp_unset_lock(&lock);
		// printf("S1 - Unlock\n");
		
		// printf("S1 - Czekam na drugi wątek\n");
		while(barier == 1){
			printf("");
		};
	}else{
		barier = 0;
		omp_unset_lock(&lock);
		// printf("S1 - Unlock\n");
	}

	print(t);
	
	// printf("=====================\n");
	// printf("S1 - Barrier wychodzę\n");
	// printf("=====================\n");
}

void barrier2(){
	// printf("====================\n");
	// printf("S2 - Barrier wchodzę\n");
	// printf("====================\n");
	omp_set_lock(&lock);
	// printf("S2 - Lock\n");
	if(barier == 0)
	{
		// nikt jeszcze nie jest przy baierze blokujemy możliwość jej zmiany oraz czekamy na zmianę na 0
		barier = 1;
		omp_unset_lock(&lock);
		// printf("S2 - Unlock\n");

		while(barier == 1){
			 printf("");
		};
	}else{
		barier = 0;
		omp_unset_lock(&lock);
		// printf("S2 - Unlock\n");
	}
	// printf("=====================\n");
	// printf("S2 - Barrier wychodzę\n");
	// printf("=====================\n");
}
int main (int argc, char **argv)
{
  srand(time(NULL));
  omp_init_lock(&lock);
// Czy przyśpieszenie roście z liczbą wątków czy zwiększenie wielkości tablicy
// Czy umieszczenie pragmy pozwala na uzyskanie przyśpieszenia ?
	// Init array
	GenerateScene();
	std::cout<< "Simulation Started\n";
	print(0);

	omp_set_num_threads(Thread);

	for(int t = 0; t< MaxTime; t++)
	{
		ArrayToPrint = (t + 1) % 2;
		
		#pragma omp parallel sections shared(barier)
		{

			#pragma omp section
			{
				#pragma omp parallel for
				for(int x = 1;x < size; x++)
				{
					for(int y = 1; y < size; y++)
					{
						// printf("[S1]Lock [%d][%d][%d]\n",t+1%2,x,y);
						omp_set_lock(&locks[(t+1)%2][x][y]);
						
						char sum = 0;
						sum +=  a[t%2][x-1][y-1] == 1 ? 1 : 0;
						sum +=  a[t%2][x+1][y-1] == 1 ? 1 : 0;
						sum +=  a[t%2][x+1][y+1] == 1 ? 1 : 0;
						sum +=  a[t%2][x-1][y+1] == 1 ? 1 : 0;
						sum +=  a[t%2][x-1][y]   == 1 ? 1 : 0;
						sum +=  a[t%2][x+1][y]   == 1 ? 1 : 0;
						sum +=  a[t%2][x][y-1]   == 1 ? 1 : 0;
						sum +=  a[t%2][x][y+1]   == 1 ? 1 : 0;

						a[(t+1)%2][x][y] = f(sum);
						// printf("[S1]Unlock [%d][%d][%d]\n",t+1%2,x,y);
						omp_unset_lock(&locks[(t+1)%2][x][y]);
					}
				}

				barrier1(t);

				// print(t);

			} // End 1st Section

			#pragma omp section
			{
				#pragma omp parallel for
				for(int x = size - 1;x >= 1 ; x--)
				{
					for(int y = size - 1; y >= 1; y--)
					{
						// printf("[S2]Lock [%d][%d][%d]\n",t+1%2,x,y);
						omp_set_lock(&locks[(t+1)%2][x][y]);
						
						char sum = 0;
						sum +=  a[t%2][x-1][y-1] == 2 ? 1 : 0;
						sum +=  a[t%2][x+1][y-1] == 2 ? 1 : 0;
						sum +=  a[t%2][x+1][y+1] == 2 ? 1 : 0;
						sum +=  a[t%2][x-1][y+1] == 2 ? 1 : 0;
						sum +=  a[t%2][x-1][y]   == 2 ? 1 : 0;
						sum +=  a[t%2][x+1][y]   == 2 ? 1 : 0;
						sum +=  a[t%2][x][y-1]   == 2 ? 1 : 0;
						sum +=  a[t%2][x][y+1]   == 2 ? 1 : 0;

						a[(t+1)%2][x][y] = f2(sum);

						// printf("[S2]Unlock [%d][%d][%d]\n",t+1%2,x,y);
						omp_unset_lock(&locks[(t+1)%2][x][y]);
					}
				}
				
				barrier2();

			} // End 2nd section
			
		}
	}

	// std::cout<<"Threads: " <<Thread<< "\n";
	// std::cout<<"Size: " <<size<< "\n";
	// avgTime /= 100;
	// std::cout<< "Time: "<<avgTime << "\n";
	// Zapisz();
  return 0;
}