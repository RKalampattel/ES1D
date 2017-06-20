#include "stdafx.h"
#include "Particle.h"

Particle::Particle(Parameters inputs, double v0, double dx0)
{
	for (int i = 0; i < inputs.np; i++)
	{
		double x0 = (0.5 + i)*inputs.L / inputs.np;
		double theta = 2 * pi*x0 / inputs.L;
		double dx = dx0*cos(theta);
		double x1 = x0 + dx;
		double x2 = x0 - dx;

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