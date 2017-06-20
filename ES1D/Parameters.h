#pragma once

/*!
The Parameters class has public member variables which represent the key inputs of the 
simulation. By passing an instance of this class to other classes, these parameters 
can be easily accessed.
*/

#include <vector>
#include <cmath>

using namespace std;
const double pi = 3.14159265359;

class Parameters
{
public:
	// Member constants
	double qm;				//!< Charge to mass ratio
	double e0;				//!< Permittivity of free space 

	// Member domain parameters
	double L;				//!< Length of simulation domain
	int N;					//!< Number of grid nodes (cells - 1)
	double h;				//!< Grid spacing (cell width)

	// Member simulation time parameters
	double dt;				//!< Time step
	int tMax;				//!< Max number of iterations in main loop	

	// Member potential solver parameters
	double tol;				//!< Tolerance for solver convergence
	int itMax;				//!< Max number of iterations in solver
	double SOR;				//!< Successive over-relaxation parameter

	// Member initialisation parameters
	int np;					//!< Total number of particles

	// Other member variables
	double q;				//!< Charge per particle;
	double m;				//!< Mass per particle
	double q0;				//!< Background charge

	Parameters(double qmIn, double wp, double e0In, double LIn, int NIn, double dtIn, 
		int tMaxIn, double tolIn, int itMaxIn, double SORIn, int nCell);	//!< Constructor
};