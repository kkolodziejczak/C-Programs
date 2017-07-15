#pragma once
#include "Player.h"
#include "Data.h"
#include "OBJLoader.h"
#include "PendulumSimulator.h"
#include <irrKlang.h>

#pragma comment(lib, "irrKlang.lib")

void OnRender();
void OnReshape(int, int);
void OnKeyPress(unsigned char, int, int);
void OnKeyDown(unsigned char, int, int);
void OnKeyUp(unsigned char, int, int);
void OnMouseMove(int, int);
void OnTimer(int);

Player player;

Data gameData;

irrklang::ISoundEngine* soundEngine;

OBJLoader *CRASH;

PendulumSimulator sim;
