#include "stdafx.h"
#include "Parameters.h"

Parameters::Parameters(double qmIn, double wp, double e0In, double LIn, int NIn, double dtIn, int tMaxIn, double tolIn, int itMaxIn, double SORIn, int nCell)
{
	// Member constants
	qm = qmIn;
	e0 = e0In;

	// Member domain parameters
	L = LIn;
	N = NIn;
	h = L / (N - 1);

	// Member simulation time parameters
	dt = dtIn;
	tMax = tMaxIn;

	// Member potential solver parameters
	tol = tolIn;
	itMax = itMaxIn;
	SOR = SORIn;

	// Member initialisation parameters
	np = 2*(N - 1)*nCell;

	// Other member variables
	q = wp*wp*(1 / qm)*e0*L / (0.5*np);
	m = q / qm;
	q0 = -q;
}