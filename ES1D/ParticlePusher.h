#pragma once

/*
The ParticlePusher class
*/

#include "Field.h"
#include "Particle.h"

class ParticlePusher
{
public:
	ParticlePusher(Parameters inputs, Particle *particles, Field *fields, int t);
};