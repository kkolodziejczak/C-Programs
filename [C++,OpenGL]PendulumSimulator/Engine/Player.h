#pragma once
#include "stdafx.h"

class Player
{
public:
	Player() : speed(0.15f)
	{
		// Inicjalizacja kamery:
		pos.x = 0.0f;
		pos.y = 1.75f;
		pos.z = 0.0f;

		dir.x = 0.0f;
		dir.y = 0.0f;
		dir.z = -1.0f;
	};
	~Player();
	void init();
	void setPosX(const float x);
	void setPosY(const float y);
	void setPosZ(const float z);
	void setDirX(const float x);
	void setDirY(const float y);
	void setDirZ(const float z);
	void setSpeed(float speed);
	float getPosX() const;
	float getPosY() const;
	float getPosZ() const;
	float getDirX() const;
	float getDirY() const;
	float getDirZ() const;
	float GetSpeed() const;
	float velRY;
	float velRX;
private:
	vec3 pos;
	vec3 dir;
	float speed;
};