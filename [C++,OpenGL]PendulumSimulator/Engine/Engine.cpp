#include "stdafx.h"
#include "Engine.h"
#include "math.h"


int mouseX = 0;
int mouseY = 0;

bool captureMouse = true;
bool free3DMovement = false;

float mouseSensitivity = .15f;

bool keystate[255];

#define AnimationTime 17


/*
Draw,
Obj.

*/
/*
chunki do poruszania i sprawdzania kolizji
mo¿liwoœæ ustawienia iloœci ³adowanych na raz chunków.
tablica chunków

class enteti 

x,y,z;
render init update etc.
*/


/*
Play music
soundEngine->play2D("music file"); Play once
soundEngine->play2D("music file",true); repeat
*/
std::vector<double> angles;
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);

	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1280, 720);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH | GLUT_MULTISAMPLE);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glutCreateWindow("Untitled II");

	glutDisplayFunc(OnRender);
	glutReshapeFunc(OnReshape);
	glutKeyboardFunc(OnKeyPress);
	glutKeyboardUpFunc(OnKeyUp);
	glutPassiveMotionFunc(OnMouseMove);
	glutMotionFunc(OnMouseMove);

	glutTimerFunc(17, OnTimer, 0);
	

	const GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	const GLfloat light_diffuse[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	const GLfloat light_position[] = { 50.0f, 50.0f, 50.0f, 0.0f };
	const GLfloat mat_ambient[] = { 0.7f, 0.7f, 0.7f, 1.0f };
	const GLfloat mat_diffuse[] = { 0.8f, 0.8f, 0.8f, 1.0f };
	const GLfloat mat_specular[] = { 0.3f, 0.3f, 0.3f, 1.0f };
	const GLfloat mat_shininess[] = { 100.0 };

	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_ALPHA_TEST);
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_NORMALIZE);

	mouseX = glutGet(GLUT_WINDOW_WIDTH) / 2;
	mouseY = glutGet(GLUT_WINDOW_HEIGHT) / 2;
	glutWarpPointer(mouseX, mouseY);
	glutSetCursor(GLUT_CURSOR_NONE);

	CRASH = new OBJLoader("CRASH");
	soundEngine = irrklang::createIrrKlangDevice();
	gameData.Load();
	player.init();

	glutMainLoop();
	
	return 0;
}

void drawText(int x, int y, std::string st, Color color)
{
	glDisable(GL_LIGHTING);
	glMatrixMode(GL_PROJECTION);  // Tell opengl that we are doing project matrix work
	double *matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();  // Clear the matrix
	glOrtho(-128.0, 128.0, -128.0, 128.0, 0.0, 30.0);  // Setup an Ortho view
	glMatrixMode(GL_MODELVIEW);  // Tell opengl that we are doing model matrix work. (drawing)
	glLoadIdentity(); // Clear the model matrix
	glDisable(GL_BLEND);
	glPushMatrix();
	gameData.SetColor(color);
	glLoadIdentity();
	glRasterPos2i(x, y); // location to start printing text
	for (int i = 0; i < st.size(); i++)
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15, st[i]);
	glPopMatrix();
	glEnable(GL_BLEND);
	glMatrixMode(GL_PROJECTION);  // Tell opengl that we are doing project matrix work
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_LIGHTING);
}

void OnKeyPress(unsigned char key, int x, int y) {
	if (!keystate[key]) {
		keystate[key] = true;
		OnKeyDown(key, x, y);
	}
}

bool enterPressed = false;
string consoleComandString = "";

void OnKeyDown(unsigned char key, int x, int y) {
	
	if (key == 27) {
		glutLeaveMainLoop();
	}

	//reagowanie na wpisany ci¹g znaków oraz w³¹czanie wy³¹czanie konsoli.
	if(key == 13)
	{
		if (consoleComandString != "")
		{
			switch(consoleComandString[0])
			{
			case 'M':
			case 'm':
				sim.set_m(stod(consoleComandString.substr(1,consoleComandString.length())));
				break;
			case 'L':
			case 'l':
				sim.set_l(stod(consoleComandString.substr(1, consoleComandString.length())));
				break;
			case 'K':
			case 'k':
				sim.set_k(stod(consoleComandString.substr(1, consoleComandString.length())));
				break;
			case 'G':
			case 'g':
				sim.set_gravity(stod(consoleComandString.substr(1, consoleComandString.length())));
				break;
			case 'S':
			case 's':
				sim.set_stepSize(stod(consoleComandString.substr(1, consoleComandString.length())));
				break;
			case 'T':
			case 't':
				sim.set_max_time(stod(consoleComandString.substr(1, consoleComandString.length())));
				break;
			default:
				break;
			}
			consoleComandString.erase();
		}
		enterPressed = !enterPressed;
	}

	//backspace
	if(enterPressed && key == 8)
	{
		consoleComandString = consoleComandString.substr(0, consoleComandString.length() - 1);
	}

	//dodawanie znaków
	if (enterPressed && key != 13 && key != 8)
		consoleComandString += key;

	
	if (key == 'm' || key == 'M') {
		if (captureMouse) {
			captureMouse = false;
			glutSetCursor(GLUT_CURSOR_LEFT_ARROW);
		}
		else {
			captureMouse = true;
			glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);
			glutSetCursor(GLUT_CURSOR_NONE);
		}
	}
	if (key == 'l' || key == 'L') {
//		soundEngine->play2D("godlike.wav"); // ,true) ->repeat
		free3DMovement = !free3DMovement;
	}

	if (key == 'r' || key == 'R') {
	}
}

void OnKeyUp(unsigned char key, int x, int y) {
	keystate[key] = false;
}

void OnMouseMove(int x, int y) {
	mouseX = x;
	mouseY = y;
}

void OnTimer(int id) {
	glutTimerFunc(17, OnTimer, 0); //rekurencyjne wywo³anie timera. bez tego zostanie wywo³any tylko raz. czasami siê przydaje taka opóŸnona funkcja.

	//KAMERA 3D
	if (captureMouse)
	{
		player.velRY = -mouseSensitivity * (glutGet(GLUT_WINDOW_WIDTH) / 2 - mouseX);
		player.velRX = mouseSensitivity * (glutGet(GLUT_WINDOW_HEIGHT) / 2 - mouseY);
		glutWarpPointer(glutGet(GLUT_WINDOW_WIDTH) / 2, glutGet(GLUT_WINDOW_HEIGHT) / 2);

		float T = acos(player.getDirY());
		float G = atan2(player.getDirZ(), player.getDirX());
		T -= player.velRX * .03f;
		G += player.velRY * .03f;
		player.setDirX(sin(T) * cos(G));
		player.setDirY(cos(T));
		player.setDirZ(sin(T) * sin(G));
	}
	//~~~~~~~~~~~~~~
	
	//Strowanie graczem//
	if (keystate['w'] || keystate['W']) {
		player.setPosX(player.getPosX() + player.getDirX()*player.GetSpeed());
			if (free3DMovement)
			player.setPosY(player.getPosY() + player.getDirY()*player.GetSpeed());
		player.setPosZ(player.getPosZ() + player.getDirZ()*player.GetSpeed());
	}
	if (keystate['s'] || keystate['S']) {
		player.setPosX(player.getPosX() - player.getDirX()*player.GetSpeed());
			if (free3DMovement)
			player.setPosY(player.getPosY() - player.getDirY()*player.GetSpeed());
		player.setPosZ(player.getPosZ() - player.getDirZ()*player.GetSpeed());
	}
	if (keystate['a'] || keystate['A']) {
		player.setPosX(player.getPosX() + -player.getDirZ() *-player.GetSpeed());
		player.setPosZ(player.getPosZ() + player.getDirX() *-player.GetSpeed());
	}
	if (keystate['d'] || keystate['D']) {
		player.setPosX(player.getPosX() + -player.getDirZ() *player.GetSpeed());
		player.setPosZ(player.getPosZ() + player.getDirX() *player.GetSpeed());
	}
}

void displayStatiscic()
{
	int x = -125;
	int y = 115;
	std::stringstream sstream;
	sstream << "masa[m]: " << sim.get_m();
	drawText(x, y, sstream.str(), White);
	sstream.str("");
	y -= 12;
	sstream << "dlugosc[l]: " << sim.get_l();
	drawText(x, y, sstream.str(), White);
	sstream.str("");
	y -= 12;
	sstream << "tlumienie[k]: " << sim.get_k();
	drawText(x, y, sstream.str(), White);
	sstream.str("");
	y -= 12;
	sstream << "grawitacja[g]: " << sim.get_gravity();
	drawText(x, y, sstream.str(), White);
	sstream.str("");
	y -= 12;
	sstream << "krok[s]: " << sim.get_stepSize();
	drawText(x, y, sstream.str(), White);
	sstream.str("");
	y -= 12;
	sstream << "czas symulacji[t]: " << sim.get_max_time();
	drawText(x, y, sstream.str(), White);
	sstream.str("");


	sstream << "frame[" << sim.get_step()<<"/"<<sim.get_SizeAngle()<<"]";
	drawText(95, 115, sstream.str(), White);
	sstream.str("");

	sstream << "Krzysztof Kolodziejczak 311A";
	drawText(75, -120, sstream.str(), White);
	sstream.str("");

	if(enterPressed)
	{
		sstream << "->" << consoleComandString;
		drawText(x,-120, sstream.str(), White);
	}
}

void OnRender() 
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(
		player.getPosX(), player.getPosY(), player.getPosZ(), // Pozycja kamery
		player.getPosX() + player.getDirX(), player.getPosY() + player.getDirY(), player.getPosZ() + player.getDirZ(), // Punkt na ktory patrzy kamera (pozycja + kierunek)
		0.0f, 1.0f, 0.0f // Wektor wyznaczajacy pion
		);

	// Narysowanie siatki stu kolorowych sfer.
	glDisable(GL_LIGHTING);

	glPushMatrix();
		glTranslatef(1.5, 2, 3);
		CRASH->render();
	glPopMatrix();

	for (int ix = -5; ix <= 5; ix += 1) {
		for (int iz = -5; iz <= 5; iz += 1) {
			glColor3f(.5f + .1f * ix, .5f - .1f * iz, 0.0f);
			glPushMatrix();
			glTranslatef(ix, 1.0f, iz);
			glutSolidSphere(.05f, 8, 8);
			glPopMatrix();
		}
	}

	sim.simulate();

	displayStatiscic();

	glEnable(GL_LIGHTING);

	glutSwapBuffers();
	glFlush();
	glutPostRedisplay();

}


void OnReshape(int width, int height) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, width, height);
	gluPerspective(50.0f, (float)width / height, .01f, 100.0f);
}
