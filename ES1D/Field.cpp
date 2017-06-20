#include "stdafx.h"
#include "Field.h"

Field::Field(Parameters inputs)
{
	for (int i = 0; i < inputs.N; i++)
	{
		rho.push_back(0);
		phi.push_back(0);
		E.push_back(0);
	}
}

void Field::clearRho()
{
	for (int i = 0; i < rho.size(); i++)
		rho[i] = 0;
}

void Field::clearPhi()
{
	for (int i = 0; i < phi.size(); i++)
		phi[i] = 0;
}