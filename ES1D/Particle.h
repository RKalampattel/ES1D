#pragma once

/*
The Particle class
*/

#include "Parameters.h"

class Particle
{
public:
	vector<double> x;
	vector<double> v;

	Particle() {};
	Particle(Parameters inputs, double v0, double dx0);
};