#include <iostream>
#include <cstdlib>
#include <vector>
#include <omp.h>
#include <time.h>
#include <fstream>

/// Matrix size
#define M_X 3
#define M_Y 3

void wyswietl(std::vector<std::vector<auto> > &matrix)
{
  
  for(auto r : matrix)
  {
    for(auto c: r)
    {
      std::cout<<c << "\t";
    }
    std::cout<< std::endl;
  }
}

void wypelnijLosowo(std::vector<std::vector<float> > &matrix, long x, long y)
{
  for(int i = 0; i < x; i++)
  {
    for(int j = 0; j < y; j++)
    {
      matrix[i][j] = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    }
  }
}

void Zapisz(int tCount, long mSize, long it, double time, const char * fileName)
{
  if(fileName == NULL)
    return;
  std::ofstream myfile;
  myfile.open (fileName, std::ios::app);
  myfile <<tCount <<", " <<mSize <<", " <<it <<", "<< time <<","<< std::endl;
  myfile.close();
}

int main(int argc, char **argv)
{
  if (argc == 1 || argc > 5)
  {
    std::cout<< "Program need at least 3 arguments to run. \n1st argument is number of Threads that will be created. \n2nd size of Matrix that will be created. \n3rd number or iterations to test";
    return 0;
  }

  srand(time(NULL));

  int threadCount = atoi(argv[1]);
  long MatrixSize = atoi(argv[2]);
  long Iterations = atoi(argv[3]);
  char* fName = argv[4];
  double StartingTime = 0.0;

  /// Create arrays
  std::vector<std::vector<float> > Matrix_A(MatrixSize,std::vector<float>(MatrixSize));
  std::vector<std::vector<float> > Matrix_B(MatrixSize,std::vector<float>(MatrixSize));
  std::vector<std::vector<float> > Matrix_OUT(MatrixSize,std::vector<float>(MatrixSize));

  wypelnijLosowo(Matrix_A,MatrixSize,MatrixSize);
  wypelnijLosowo(Matrix_B,MatrixSize,MatrixSize);

  // wyswietl(Matrix_A);
  // std::cout<< std::endl;
  // wyswietl(Matrix_B);

  /// Set max number of threads
  omp_set_num_threads(threadCount);

  // Total Time duration
  double Dur;

  // Iterate and get avg score that way
  for(int it =0; it < Iterations; it++)
  {
    float suma = 0;
    #pragma omp parallel
    {
      StartingTime = omp_get_wtime();
      #pragma omp for
      for(int i = 0; i < MatrixSize; i++)//wierszA
      {
        for(int j = 0; j < MatrixSize; j++)//kolumnaB
        {
          for(int k = 0; k < MatrixSize; k++)//mnożwenie wierszA * kolumnaB 
          {
            Matrix_OUT[j][i] += Matrix_A[j][k] * Matrix_B[k][i];
          }
        }
      }
    }
    // Add duration time to total number
    Dur += (omp_get_wtime() - StartingTime);
  }

  /// Czytanie wierszami jest szybsze niż czytanie kolumnami
  std::cout << "Threads: " << threadCount <<" Matrix: " << MatrixSize << "x"<< MatrixSize << " It: " << Iterations << "\n"
  << "AVG: " << Dur/Iterations << " sec\n";

  Zapisz(threadCount, MatrixSize, Iterations, Dur/Iterations, fName);

  return 0;
}
