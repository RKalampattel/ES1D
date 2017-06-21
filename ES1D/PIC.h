#pragma once

/*!
The PIC class runs the main loop of the PIC simulation. It's member variables are the 
current iteration t, as well as the particles and fields that are updated at each time
step. In the PIC constructor, instances of ChargeProjector, FieldSolver and ParticlePusher
are created. 
*/

#include "ChargeProjector.h"
#include "FieldSolver.h"
#include "ParticlePusher.h"
#include <iostream>
#include <fstream>

class PIC
{
public:
	int t;					//!< Current iteration	
	Particle particles;		//!< Contains particle position and velocity
	Field fields;			//!< Contains charge density, potential and electric field

	PIC(Parameters inputs, double v0, double dx0);	//!< Constructor
};