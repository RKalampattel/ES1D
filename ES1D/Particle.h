#pragma once

/*!
The Particle class has two member variables representing position and velocity of the
particle set. The second constructor is used to initialise these values.
*/

#include "Parameters.h"

class Particle
{
public:
	vector<double> x;	//!< Position vector
	vector<double> v;	//!< Velocity vector

	Particle() {};										//!< Default constructor
	Particle(Parameters inputs, double v0, double dx0);	//!< Second constructor
};