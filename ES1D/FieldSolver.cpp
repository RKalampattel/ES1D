#include "stdafx.h"
#include "FieldSolver.h"

FieldSolver::FieldSolver(Parameters inputs, Field *fields)
{
	fields->clearPhi();

	for (int j = 1; j <= inputs.itMax; j++)
	{
		for (int i = 0; i < inputs.N - 1; i++)
		{
			if (i == 0)
				fields->phi[i] = inputs.SOR*0.5*(fields->phi[inputs.N - 2] + fields->phi[i + 1] + (fields->rho[i] / inputs.e0)*inputs.h*inputs.h) + (1 - inputs.SOR)*fields->phi[i];
			else if (i == inputs.N - 2)
				fields->phi[i] = inputs.SOR*0.5*(fields->phi[i - 1] + fields->phi[0] + (fields->rho[i] / inputs.e0)*inputs.h*inputs.h) + (1 - inputs.SOR)*fields->phi[i];
			else
				fields->phi[i] = inputs.SOR*0.5*(fields->phi[i - 1] + fields->phi[i + 1] + (fields->rho[i] / inputs.e0)*inputs.h*inputs.h) + (1 - inputs.SOR)*fields->phi[i];
		}

		if (j % 25 == 0)
		{
			double resSum = 0, residual = 0;
			for (int i = 1; i < inputs.N - 1; i++)
			{
				if (i == inputs.N - 2)
					residual = (fields->rho[i] / inputs.e0) + (fields->phi[i - 1] - 2 * fields->phi[i] + fields->phi[0]) / (inputs.h*inputs.h);
				else
					residual = (fields->rho[i] / inputs.e0) + (fields->phi[i - 1] - 2 * fields->phi[i] + fields->phi[i + 1]) / (inputs.h*inputs.h);
				resSum += residual*residual;
			}
			if (sqrt(resSum / inputs.N) < inputs.tol)
				break;
		}
	}
	fields->phi[inputs.N - 1] = fields->phi[0];

	for (int i = 0; i < inputs.N; i++)
	{
		if (i == 0)
			fields->E[i] = (fields->phi[inputs.N - 2] - fields->phi[i + 1]) / (2 * inputs.h);
		else if (i == inputs.N - 1)
			fields->E[i] = (fields->phi[i - 1] - fields->phi[1]) / (2 * inputs.h);
		else
			fields->E[i] = (fields->phi[i - 1] - fields->phi[i + 1]) / (2 * inputs.h);
	}
}