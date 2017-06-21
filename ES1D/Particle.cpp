#include "stdafx.h"
#include "Particle.h"

Particle::Particle(Parameters inputs, double v0, double dx0)
{
	for (int i = 0; i < 0.5*inputs.np; i++)
	{
		// Seed particles uniformly in domain
		double x0 = (0.5 + i)*inputs.L / (0.5*inputs.np);
		double theta = 2 * pi*x0 / inputs.L;

		// Offset from initial location
		double dx = dx0*cos(theta);
		double x1 = x0 + dx;
		double x2 = x0 - dx;

		// Check if particles are still in the simulation domain, load x and v vectors
		if (x1 < 0) 
			x1 += inputs.L;
		if (x1 >= inputs.L)
			x1 -= inputs.L;
		x.push_back(x1);
		v.push_back(v0);

		if (x2 < 0) 
			x2 += inputs.L;
		if (x2 >= inputs.L)
			x2 -= inputs.L;
		x.push_back(x2);
		v.push_back(-v0);
	}
}