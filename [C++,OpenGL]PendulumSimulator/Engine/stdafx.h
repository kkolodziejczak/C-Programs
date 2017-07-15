// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#define PI 3.14159265

struct vec3
{
	float x, y, z;
};

#include "targetver.h"

#include <math.h>
#include <stdio.h>
#include <fstream>
#include <istream>
#include <sstream>
#include <string>
#include <cstdlib>

#include <vector>

#include "GL/freeglut.h"


#pragma region Zmienne globalne

extern float T;

extern int mouseX;
extern int mouseY;

extern bool captureMouse;
extern bool free3DMovement;

extern float mouseSensitivity;

extern bool keystate[255];

#pragma endregion