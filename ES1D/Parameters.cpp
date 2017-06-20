#include "stdafx.h"
#include "Parameters.h"

Parameters::Parameters(double qmIn, double wp, double e0In, double LIn, int NIn, double dtIn, int tMaxIn, double tolIn, int itMaxIn, double SORIn, int nCell)
{
	// Set member constants
	qm = qmIn;
	e0 = e0In;

	// Set member domain parameters
	L = LIn;
	N = NIn;
	h = L / (N - 1);

	// Set member simulation time parameters
	dt = dtIn;
	tMax = tMaxIn;

	// Set member potential solver parameters
	tol = tolIn;
	itMax = itMaxIn;
	SOR = SORIn;

	// Calculate member initialisation parameters
	np = 2*(N - 1)*nCell;

	// Calculate other member variables
	q = wp*wp*(1 / qm)*e0*L / (0.5*np);
	m = q / qm;
	q0 = -q;
}