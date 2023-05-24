#pragma once
#include "Body.h"

namespace Integrator
{
	void ExplicitEuler(Body& body, float dt)
	{
		body.position += body.velocity * dt;
		body.velocity += (body.force * body.invMass) * dt;
		body.velocity *= (1.0f / (1.0f + (dt * body.damping)));
	}

	void SemiImplicitEuler(Body& body, float dt)
	{
		body.velocity += (body.force * body.invMass) * dt;
		body.position += body.velocity * dt;
		body.velocity *= (1.0f / (1.0f + (dt * body.damping)));
	}

}