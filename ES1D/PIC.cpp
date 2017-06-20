#include "stdafx.h"
#include "PIC.h"

PIC::PIC(Parameters inputs, double v0, double dx0)
{
	t = 0;	// Initial time
	Particle particles(inputs, v0, dx0);
	Field fields(inputs);

	cout << "Beginning simulation..." << endl;

	// Main loop
	while (t < inputs.tMax)
	{
		// Find charge at grid nodes, and use this to calculate charge density
		ChargeProjector projector(inputs, &particles, &fields);

		// Solve the Poisson equation to find the potential and electric field
		FieldSolver solver(inputs, &fields);

		// Move the particles and apply boundary conditions
		ParticlePusher pusher(inputs, &particles, &fields, t);

		// Calculate kinetic and potential energies
		if (t % 5 == 0)
		{
			double EK = 0, EP = 0;
			for (int i = 0; i < inputs.np; i++)
				EK += 0.5*inputs.m*particles.v[i] * particles.v[i];
			for (int i = 0; i < inputs.N; i++)
				EP += 0.5*fields.rho[i] * fields.phi[i];

			cout << "Time step: " << t << endl;
			cout << "EK: " << EK << endl;
			cout << "EP: " << EP << endl;
		}

		t += 1;	// Update time
	}
	cout << "Simulation complete!" << endl;
}