#include "stdafx.h"
#include "ChargeProjector.h"

ChargeProjector::ChargeProjector(Parameters inputs, Particle *particles, Field *fields)
{
	// Clear the charge density vector
	fields->clearRho();

	for (int i = 0; i < inputs.np; i++)
	{
		// Coordinate of grid node to the left of particle
		int coord = (int)floor(particles->x[i] / inputs.h);
		// Distance from particle to grid node as a percentage of grid spacing
		double d = (particles->x[i] / inputs.h) - coord;
		fields->rho[coord] += inputs.q*d;
		fields->rho[coord + 1] += inputs.q*(1 - d);
	}

	// Add background charge
	for (int i = 0; i < inputs.N - 1; i++)
		fields->rho[i] += inputs.q0*((double)inputs.np / (inputs.N - 1));

	// Periodic BCs at the end points
	fields->rho[inputs.N - 1] += fields->rho[0];
	fields->rho[0] = fields->rho[inputs.N - 1];

	// Calculate the charge density
	for (int i = 0; i < inputs.N; i++)
	{
		fields->rho[i] /= inputs.h;
		// Remove some noise
		if (abs(fields->rho[i])<1e-10)
			fields->rho[i] = 0;
	}
}