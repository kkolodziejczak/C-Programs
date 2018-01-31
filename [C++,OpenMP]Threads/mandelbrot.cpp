#include <iostream>
#include <sstream>
#include <fstream>
#include <thread>
#include <cmath>
#include <omp.h>

// I/O
// prywatyzacja
// czasy
// schedule
// pokolorować

struct colors{
   unsigned char r, g, b;
};

#define Size 2400

const int iXmax = Size;
const int iYmax = Size;
/* world ( double) coordinate = parameter plane*/
const double CxMin=-2.5;
const double CxMax=1.5;
const double CyMin=-2.0;
const double CyMax=2.0;
/* color component ( R or G or B) is coded from 0 to 255 */
/* it is 24 bit color RGB file */
const int MaxColorComponentValue=255;
const int IterationMax=200;
/* bail-out value , radius of circle ;  */
const double EscapeRadius=2;
static unsigned char color[3];
static char Picture[Size][Size][3];


struct colors kolory[10];
struct colors tlo[4];

std::ofstream outputFile("new1.ppm");
void CalculateFractal(int ThreadCount);

int main() {

    kolory[0].r = 255;
    kolory[0].g = 0;
    kolory[0].b = 0;
    kolory[1].r = 0;
    kolory[1].g = 255;
    kolory[1].b = 0;
    kolory[2].r = 0;
    kolory[2].g = 0;
    kolory[2].b = 255;
    kolory[3].r = 125;
    kolory[3].g = 125;
    kolory[3].b = 0;
    kolory[4].r = 125;
    kolory[4].g = 125;
    kolory[4].b = 255;

    tlo[0].r = 102;
    tlo[0].g = 102;
    tlo[0].b = 102;

    tlo[1].r = 25;
    tlo[1].g = 25;
    tlo[1].b = 25;

    tlo[2].r = 51;
    tlo[2].g = 51;
    tlo[2].b = 51;

    tlo[3].r = 76;
    tlo[3].g = 76;
    tlo[3].b = 76;

	std::string comment = "# ";

	if (!outputFile.is_open()){
		std::cout<< "Can't write to file"<<std::endl;
	}
	//"P6\n %s\n %d\n %d\n %d\n"
	outputFile <<"P6\n " << comment <<"\n " << iXmax <<"\n "<< iYmax <<"\n "<< MaxColorComponentValue<<"\n";

//	CalculateFractal(0,200,200,0,0,0);
    CalculateFractal(5);

	//Zapis dannych do pliku.
	for(int i=0;i<iXmax;i++){
		for(int j =0;j<iYmax;j++){
			 outputFile << Picture[i][j][0] <<Picture[i][j][1] <<Picture[i][j][2];
		}
    }
    
    outputFile.close();
	std::cout<< "program wykonal sie poprawnie" <<std::endl;
	return 0;
}

void CalculateFractal(int ThreadCount){
    int iY;
	double Cx,Cy;
	double PixelWidth=(CxMax-CxMin)/iXmax;
	double PixelHeight=(CyMax-CyMin)/iYmax;
	double Zx, Zy;
	double Zx2, Zy2;
	double ER2=EscapeRadius*EscapeRadius;
    
    double time = 0.0;
    time = omp_get_wtime();
    
    omp_set_num_threads(ThreadCount);
    #pragma omp parallel for schedule(static, Size/16) private(iY, Cy, Cx, Zx, Zy, Zx2, Zy2)
    for(iY=0;iY<iYmax;iY++)
    {
        Cy=CyMin + iY*PixelHeight;
        if (fabs(Cy)< PixelHeight/2) Cy=0.0; /* Main antenna */
        for(int iX=0;iX<iXmax;iX++)
        {
            Cx=CxMin + iX*PixelWidth;
            /* initial value of orbit = critical point Z= 0 */
            Zx=0.0;
            Zy=0.0;
            Zx2=Zx*Zx;
            Zy2=Zy*Zy;
            /* */
            int Iteration;
            for (Iteration=0;Iteration<IterationMax && ((Zx2+Zy2)<ER2);Iteration++)
            {
                Zy=2*Zx*Zy + Cy;
                Zx=Zx2-Zy2 +Cx;
                Zx2=Zx*Zx;
                Zy2=Zy*Zy;
            };
            /* compute  pixel color (24 bit = 3 bytes) */
            if (Iteration==IterationMax)
            { /*  interior of Mandelbrot set = black */
                color[0]=kolory[omp_get_thread_num()].r;
                color[1]=kolory[omp_get_thread_num()].g;
                color[2]=kolory[omp_get_thread_num()].b;
            }
            else
            { /* exterior of Mandelbrot set = white */
                color[0]= tlo[omp_get_thread_num()].r; /* Red*/
                color[1]= tlo[omp_get_thread_num()].g; /* Green */
                color[2]= tlo[omp_get_thread_num()].b;/* Blue */
            };
            /*write color to the file*/
            // std::cout << iY << " " << iX << " \n";
            Picture[iY][iX][0]= color[0];
            Picture[iY][iX][1]= color[1];
            Picture[iY][iX][2]= color[2];
        }
    }

    std::cout<< "Czas:" << omp_get_wtime() - time << "\n";
    
}
