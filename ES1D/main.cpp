/*
1D Electrostatic PIC algorithm

This program solves the two stream instability problem, based on code by Brieda 
(https://www.particleincell.com/2015/two-stream-instability/), in turn based on 
Birdsall (Plasma Physics via Computer Simulation). This file is used to define 
inputs to the program. 

Rahul Kalampattel, 21/06/2017
*/

#include "stdafx.h"
#include "PIC.h"

int main()
{
	// Constants
	double qm = -1;		// Charge to mass ratio
	double wp = 1;		// Plasma frequency
	double e0 = 1;		// Permittivity of free space

	// Domain parameters
	double L = 2 * pi;	// Length of simulation domain
	int N = 64;			// Number of grid nodes (cells - 1)

	// Simulation time parameters
	double dt = 0.1;	// Time step
	int tMax = 501;		// Max number of iterations in main loop

	// Potential solver parameters
	double tol = 1e-6;	// Tolerance for solver convergence
	int itMax = 20000;	// Max number of iterations in solver
	double SOR = 1.8;	// Successive over-relaxation parameter

	// Initialisation parameters
	int nCell = 15;		// Number of particles (per species) per cell
	double v0 = 1;		// Initial velocity
	double dx0 = 1e-4;	// Perturbation factor

	// Create an instance of the Parameters class to initialise simulation
	Parameters inputs(qm, wp, e0, L, N, dt, tMax, tol, itMax, SOR, nCell);

	// Create an instance of the PIC class to run the simulation
	PIC ES1D(inputs, v0, dx0);

	system("pause");

	return 0;
}