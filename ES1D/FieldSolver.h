#pragma once

/*!
The FieldSolver class is used to solve the Poisson equation and find the potential and 
electric field at each time step. The Gauss-Seidel method with successive over-relaxation
is used.
*/

#include "Field.h"

class FieldSolver
{
public:
	FieldSolver(Parameters inputs, Field *fields);	//!< Constructor
};