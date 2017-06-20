#include "stdafx.h"
#include "ParticlePusher.h"

ParticlePusher::ParticlePusher(Parameters inputs, Particle *particles, Field *fields, int t)
{
	for (int i = 0; i < inputs.np; i++)
	{
		// Find electric field at particle position
		int coord = (int)floor(particles->x[i] / inputs.h);
		double d = (particles->x[i] / inputs.h) - coord;
		double E_part = fields->E[coord] * d + fields->E[coord + 1] * (1 - d);

		// Move v back by dt/2, i.e. find v(t-dt/2)
		if (t == 0)
			particles->v[i] -= 0.5*E_part*inputs.qm*inputs.dt;

		// Calculate v(t+dt/2), use this to find x(t+dt)
		particles->v[i] += E_part*inputs.qm*inputs.dt;
		particles->x[i] += particles->v[i] * inputs.dt;

		// Periodic BCs to keep the particles in the domain
		if (particles->x[i] < 0)
			particles->x[i] += inputs.L;
		if (particles->x[i] >= inputs.L)
			particles->x[i] -= inputs.L;
	}
}