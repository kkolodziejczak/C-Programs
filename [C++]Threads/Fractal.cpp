#include <iostream>
#include <sstream>
#include <fstream>
#include <thread>
#include <cmath>

const int iXmax = 800;
const int iYmax = 800;
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
static char Picture[800][800][3];

std::ofstream outputFile("new1.ppm");
void CalculateFractal(int startX, int startY,int endX, int endY, char R,char G, char B);

int main() {

	std::string comment = "# ";

	if (!outputFile.is_open()){
		std::cout<< "Can't write to file"<<std::endl;
	}
	//"P6\n %s\n %d\n %d\n %d\n"
	outputFile <<"P6\n " << comment <<"\n " << iXmax <<"\n "<< iYmax <<"\n "<< MaxColorComponentValue<<"\n";

//	CalculateFractal(0,200,200,0,0,0);
	std::thread t1(CalculateFractal,0,  0,  400,400,0,  123,126);
	std::thread t2(CalculateFractal,400,0,  800,400,0,  0,  255);
	std::thread t3(CalculateFractal,0,400,  400,800,0,  255,0);
	std::thread t4(CalculateFractal,400,400,800,800,255,0,  0);

	t1.join();
	t2.join();
	t3.join();
	t4.join();

	//Zapis dannych do pliku.
	for(int i=0;i<iXmax;i++){
		for(int j =0;iYmax;j++){
			 outputFile << Picture[i][j][0] <<Picture[i][j][1] <<Picture[i][j][2];
		}
	}
	std::cout<< "program wykonal sie poprawnie" <<std::endl;
	return 0;
}

void CalculateFractal(int startX, int startY,int endX, int endY, char R,char G, char B){
	int iX,iY;
	double Cx,Cy;
	double PixelWidth=(CxMax-CxMin)/iXmax;
	double PixelHeight=(CyMax-CyMin)/iYmax;
	double Zx, Zy;
	double Zx2, Zy2;
	int Iteration;
	double ER2=EscapeRadius*EscapeRadius;

    for(iY=startY;iY<endY;iY++)
            {
                 Cy=CyMin + iY*PixelHeight;
                 if (fabs(Cy)< PixelHeight/2) Cy=0.0; /* Main antenna */
                 for(iX=startX;iX<endX;iX++)
                 {
                            Cx=CxMin + iX*PixelWidth;
                            /* initial value of orbit = critical point Z= 0 */
                            Zx=0.0;
                            Zy=0.0;
                            Zx2=Zx*Zx;
                            Zy2=Zy*Zy;
                            /* */
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
                               color[0]=R;
                               color[1]=G;
                               color[2]=B;
                            }
                         else
                            { /* exterior of Mandelbrot set = white */
                                 color[0]=255; /* Red*/
                                 color[1]=255;  /* Green */
                                 color[2]=255;/* Blue */
                            };
                            /*write color to the file*/
                            Picture[iY][iX][0]= color[0];
                            Picture[iY][iX][1]= color[1];
                            Picture[iY][iX][2]= color[2];
                    }
            }
}
