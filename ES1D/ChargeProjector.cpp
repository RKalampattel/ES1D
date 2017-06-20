#include "stdafx.h"
#include "ChargeProjector.h"

ChargeProjector::ChargeProjector(Parameters inputs, Particle *particles, Field *fields)
{
	fields->clearRho();

	for (int i = 0; i < inputs.np; i++)
	{
		int coord = (int)floor(particles->x[i] / inputs.h);
		double d = (particles->x[i] / inputs.h) - coord;
		fields->rho[coord] += inputs.q*d;
		fields->rho[coord + 1] += inputs.q*(1 - d);
	}

	for (int i = 0; i < inputs.N - 1; i++)
		fields->rho[i] += inputs.q0*((double)inputs.np / (inputs.N - 1));

	fields->rho[inputs.N - 1] += fields->rho[0];
	fields->rho[0] = fields->rho[inputs.N - 1];

	for (int i = 0; i < inputs.N; i++)
	{
		fields->rho[i] /= inputs.h;
		if (abs(fields->rho[i])<1e-10)
			fields->rho[i] = 0;
	}
}