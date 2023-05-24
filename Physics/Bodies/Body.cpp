#include "Body.h"
#include "../../Engine/Integrator.h"
#include "../../Engine/World.h"
#include "Shape.h"
#include "CircleShape.h"


void Body::ApplyForce(const glm::vec2& force)
{
	this->force += force;
}

void Body::Step(float dt)
{
	if (type != DYNAMIC)
	{
		return;
	}
	// Gravity
	Body::ApplyForce(World::gravity * gravityScale * mass);
	Integrator::ExplicitEuler(*this, dt);
	ClearForce();
}

void Body::Draw(Graphics* graphics)
{
	shape->Draw(graphics, position);
}

bool Body::Intersects(Body* body)
{
	glm::vec2 direction = this->position - body->position;
	float distance = glm::length(direction);
	float radius = ((CircleShape*)shape)->radius + ((CircleShape*)body->shape)->radius;

	return distance <= radius;
}
