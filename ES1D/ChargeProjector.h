#pragma once

/*!
The ChargeProjector class is used to find charge at grid nodes in the PIC simulation, 
and use this to calculate the charge density.
*/

#include "Field.h"
#include "Particle.h"

class ChargeProjector
{
public:
	ChargeProjector(Parameters inputs, Particle *particles, Field *fields);	//!< Constructor
};