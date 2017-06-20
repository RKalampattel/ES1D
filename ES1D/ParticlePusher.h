#pragma once

/*!
The ParticlePusher class is used to update the position and velocity of particles in 
the PIC simulation, and apply appropriate boundary conditions.
*/

#include "Field.h"
#include "Particle.h"

class ParticlePusher
{
public:
	ParticlePusher(Parameters inputs, Particle *particles, Field *fields, int t);	//!< Constructor
};