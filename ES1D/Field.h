#pragma once

/*!
The Field class has three member variables representing the charge density, potential
and electric field. The second constructor is used to initialise these values, while
the two other member functions are used to clear the rho and phi vectors. 
*/

#include "Parameters.h"

class Field
{
public:
	vector<double> rho;	//!< Charge density vector
	vector<double> phi;	//!< Potential vector
	vector<double> E;	//!< Electric field vector

	Field() {};					//!< Default constructor
	Field(Parameters inputs);	//!< Second constructor
	void clearRho();			//!< Clear the rho vector
	void clearPhi();			//!< Clear the phi vector
};