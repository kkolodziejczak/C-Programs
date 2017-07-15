#pragma once
class PendulumSimulator
{
private:
	double m;		// masa
	double l;		// d³ugoœæ
	double k;		// wspó³rzynnik t³umienia
	double gravity; // przyœpieszenie ziemskie
	double stepSize;// krok
	int step;		// iteracja
	double maxTime;
	std::vector<double> angles;
	void calculateRK4();
public:
	double get_step() const;
	double get_SizeAngle() const;
	PendulumSimulator();
	~PendulumSimulator();
	void recalculate();
	void simulate();
	double get_m() const;
	void set_m(double m);
	double get_l() const;
	void set_l(double l);
	double get_k() const;
	void set_k(double k);
	double get_gravity() const;
	void set_gravity(double gravity);
	double get_stepSize() const;
	void set_stepSize(double step);
	double get_max_time() const;
	void set_max_time(double max_time);
};

