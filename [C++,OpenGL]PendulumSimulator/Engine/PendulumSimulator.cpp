#include "stdafx.h"
#include "PendulumSimulator.h"


PendulumSimulator::PendulumSimulator()
{
	m = 10;			// masa
	l = 3;			// d³ugoœæ
	k = 1;			// wspó³rzynnik t³umienia
	gravity = 10;	// przyœpieszenie ziemskie
	stepSize = 0.01;	// krok
	step = 0;
	maxTime = 100;
	recalculate();
}

PendulumSimulator::~PendulumSimulator()
{
}

void PendulumSimulator::recalculate()
{
	calculateRK4();
}

void PendulumSimulator::simulate()
{
	if(step <= angles.size())
	{
		double x1 = l*sin(angles[step]);
		double y1 = l*cos(angles[step]);
		glPushMatrix();
		glTranslatef(x1, 2.0f, y1);
		glColor3f(0.0f,1.0f, 0.0f);
		glutSolidSphere(.1f*m, 16, 16);
		glPopMatrix();
	
		glLineWidth(1.5);
		glColor3f(1.0, 1.0, 1.0);
		glBegin(GL_LINES);
		glVertex3f(0.0, 2.0, 0.0);
		glVertex3f(x1, 2, y1);
		glEnd();
		step++;
		if (step == angles.size())
			step = 0;
	}
}

void PendulumSimulator::calculateRK4()
{
	angles.clear();

	std::vector<double> fi0;
	fi0.push_back(90 * PI / 180);
	std::vector<double> fi1;
	fi1.push_back(0.0);
	std::vector<double> fi2;
	fi2.push_back(-sin(fi0[0]) * gravity / l - fi1[0] * k / m);
	std::vector<double> times;
	times.push_back(0.0);

	int i = 0;
	double newY1;
	double newY0;
	double poch2tmp;
	double poch1tmp;
	for (double time = times[0] + stepSize; time <= maxTime; time += stepSize, i += 1)
	{
		// K1
		double K1y1 = fi2.back() * stepSize;
		double K1y0 = fi1.back() * stepSize;
		// zmienne tymczasowe
		newY1 = fi1.back() + K1y1 * 0.5; // a tutaj dla y' + 1/2 * K1
		newY0 = fi0.back() + K1y0 * 0.5; // a tutaj dla y + 1/2 * K1
		poch2tmp = -sin(newY0)*gravity / l - newY1*k / m;
		poch1tmp = newY1;
		//K2
		double K2y1 = poch2tmp*stepSize;
		double K2y0 = poch1tmp*stepSize;
		// zmienne tymczasowe
		newY1 = fi1.back() + K2y1 * 0.5; // a tutaj dla y' + 1/2 * K2
		newY0 = fi0.back() + K2y0 * 0.5; // a tutaj dla y + 1/2 * K2
		poch2tmp = -sin(newY0)*gravity / l - newY1*k / m;
		poch1tmp = newY1;
		// K3
		double K3y1 = poch2tmp*stepSize;
		double K3y0 = poch1tmp*stepSize;
		// zmienne tymczasowe
		newY1 = fi1.back() + K3y1; // a tutaj dla y' +  K3
		newY0 = fi0.back() + K3y0; // a tutaj dla y + K3
		poch2tmp = -sin(newY0)*gravity / l - newY1*k / m;
		poch1tmp = newY1;
		// K4
		double K4y1 = poch2tmp*stepSize;
		double K4y0 = poch1tmp*stepSize;
		// Wynik
		fi0.push_back(fi0.back() + (K1y0 + 2 * (K2y0 + K3y0) + K4y0) / 6);
		fi1.push_back(fi1.back() + (K1y1 + 2 * (K2y1 + K3y1) + K4y1) / 6);
		fi2.push_back(-sin(fi0.back()) *gravity / l - fi1.back()*k / m);
	}
	step = 0;
	angles = fi0;
}

double PendulumSimulator::get_step() const
{
	return step;
}

double PendulumSimulator::get_SizeAngle() const
{
	return angles.size();
}

double PendulumSimulator::get_m() const
{
	return m;
}

void PendulumSimulator::set_m(double m)
{
	this->m = m;
	recalculate();
}

double PendulumSimulator::get_l() const
{
	return l;
}

void PendulumSimulator::set_l(double l)
{
	this->l = l;
	recalculate();
}

double PendulumSimulator::get_k() const
{
	return k;
}

void PendulumSimulator::set_k(double k)
{
	this->k = k;
	recalculate();
}

double PendulumSimulator::get_gravity() const
{
	return gravity;
}

void PendulumSimulator::set_gravity(double gravity)
{
	this->gravity = gravity;
	recalculate();
}

double PendulumSimulator::get_stepSize() const
{
	return this->stepSize;
}

void PendulumSimulator::set_stepSize(double step)
{
	this->stepSize = step;
	recalculate();
}

double PendulumSimulator::get_max_time() const
{
	return maxTime;
}

void PendulumSimulator::set_max_time(double max_time)
{
	maxTime = max_time;
}
