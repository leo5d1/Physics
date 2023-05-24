#include "ParticleTest.h"
#include "../Physics/Bodies/Body.h"

void ParticleTest::Initialize()
{
	Test::Initialize();

}

void ParticleTest::Update()
{
	Test::Update();

	if (m_input->GetMouseButton(0))
	{
		glm::vec2 velocity = randomUnitCircle() * randomf(100, 200);

		auto body = new Body(new CircleShape(randomf(5, 20), { randomf(255), randomf(255), randomf(255), randomf(255) }), m_input->GetMousePosition(), velocity);

		m_world->AddBody(body);
	}
}

void ParticleTest::FixedUpdate()
{
	m_world->Step(m_time->GetFixedDeltaTime());
}

void ParticleTest::Render()
{
	m_world->Draw(m_graphics);
	m_graphics->DrawCircle(m_input->GetMousePosition(), 30, { randomf(), randomf(), randomf(), 1 });
}
