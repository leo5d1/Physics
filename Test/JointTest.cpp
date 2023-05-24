#include "JointTest.h"
#include "../Physics/Bodies/Body.h"
#include "../Engine/World.h"
#include "../Physics/Bodies/CircleShape.h"
#include "../Physics/Joints/Joint.h"

#define SPRING_STIFFNESS	200
#define SPRING_LENGTH		1
#define BODY_DAMPING		25
#define CHAIN_SIZE			3

#define CHAIN
//#define GRID

void JointTest::Initialize()
{
	Test::Initialize();

	m_anchor = new Body(new CircleShape(20, { 1, 1, 1, 1 }), { 0, 0 }, { 0, 0 }, 0, Body::KINEMATIC);
	m_world->AddBody(m_anchor);

	Body* prevA = nullptr;
	Body* prevB = nullptr;
	Joint* joint = nullptr;

#if defined(CHAIN)
	prevA = m_anchor;

	for (int i = 0; i <= CHAIN_SIZE; i++)
	{
		auto body = new Body(new CircleShape(0.5, { 1, 1, 1, 1 }), { 0, 0 });
		body->damping = BODY_DAMPING;
		m_world->AddBody(body);

		joint = new Joint(prevA, body, SPRING_STIFFNESS, SPRING_LENGTH);
		m_world->AddJoint(joint);

		prevA = body;
	}
#elif defined(GRID)
	bool firstLoop = true;

	for (int i = 0; i <= CHAIN_SIZE; i++)
	{
		auto bodyA = new Body(new CircleShape(20, { 1, 1, 1, 1 }), { 400, 200 }, { 0, 0 }, 1, Body::DYNAMIC);
		bodyA->gravityScale = 250;
		bodyA->damping = BODY_DAMPING;
		m_world->AddBody(bodyA);

		auto bodyB = new Body(new CircleShape(20, { 1, 1, 1, 1 }), { 400, 200 }, { 0, 0 }, 1, Body::DYNAMIC);
		bodyB->gravityScale = 250;
		bodyB->damping = BODY_DAMPING;
		m_world->AddBody(bodyB);

		joint = new Joint(bodyA, bodyB, SPRING_STIFFNESS, SPRING_LENGTH);
		m_world->AddJoint(joint);

		if (firstLoop)
		{
			joint = new Joint(bodyA, m_anchor, SPRING_STIFFNESS, SPRING_LENGTH);
			m_world->AddJoint(joint);

			joint = new Joint(bodyB, m_anchor, SPRING_STIFFNESS, SPRING_LENGTH);
			m_world->AddJoint(joint);

			prevA = bodyA;
			prevB = bodyB;
			firstLoop = false;
		}
		else
		{
			joint = new Joint(bodyA, prevA, SPRING_STIFFNESS, SPRING_LENGTH);
			m_world->AddJoint(joint);

			joint = new Joint(bodyB, prevB, SPRING_STIFFNESS, SPRING_LENGTH);
			m_world->AddJoint(joint);

			joint = new Joint(bodyB, prevA, SPRING_STIFFNESS, SPRING_LENGTH);
			m_world->AddJoint(joint);

			joint = new Joint(bodyA, prevB, SPRING_STIFFNESS, SPRING_LENGTH);
			m_world->AddJoint(joint);
		}

		prevA = bodyA;
		prevB = bodyB;
	}
#endif
}

void JointTest::Update()
{
	Test::Update();
	m_anchor->position = m_graphics->ScreenToWorld(m_input->GetMousePosition());
}

void JointTest::FixedUpdate()
{
	m_world->Step(m_time->GetFixedDeltaTime());
}

void JointTest::Render()
{
	m_graphics->DrawCircle(m_input->GetMousePosition(), 10, { randomf(), randomf(), randomf(), 1 });
	m_world->Draw(m_graphics);
}
