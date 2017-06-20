#pragma once

/*
The Field class
*/

#include "Parameters.h"

class Field
{
public:
	vector<double> rho;	// Charge density
	vector<double> phi;	// Potential
	vector<double> E;	// Electric field

	Field() {};
	Field(Parameters inputs);
	void clearRho();
	void clearPhi();
};