#pragma once

/*
The PIC class 
*/

#include "ChargeProjector.h"
#include "FieldSolver.h"
#include "ParticlePusher.h"
#include <iostream>

class PIC
{
public:
	int t;					// Current iteration	
	Particle particles;		// Contains particle position and velocity
	Field fields;			// Contains charge density, potential and electric field

	PIC(Parameters inputs, double v0, double dx0);
};