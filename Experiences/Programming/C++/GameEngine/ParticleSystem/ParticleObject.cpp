#include "ParticleObject.h"

ParticleObject::ParticleObject() : GameObject()
{
	m_velocity = Vector(0.0f, 0.0f, 0.0f);
	m_acceleration = Vector(0.0f, 0.0f, 0.0f);
	m_life = 1.0f;

	hasInitialized = false;
}

ParticleObject::~ParticleObject()
{
}

void ParticleObject::SetVelocity(Vector velocity)
{
	m_velocity = velocity;
}

Vector ParticleObject::GetVelocity()
{
	return m_velocity;
}

void ParticleObject::SetAcceleration(Vector acceleration)
{
	m_acceleration = acceleration;
}

Vector ParticleObject::GetAcceleration()
{
	return m_acceleration;
}

void ParticleObject::SetLife(float lifeTime)
{
	m_life = lifeTime;
}

float ParticleObject::GetLife()
{
	return m_life;
}

void ParticleObject::SetInitializationCondition(bool initialized)
{
	hasInitialized = initialized;
}

bool ParticleObject::GetInitializationCondition()
{
	return hasInitialized;
}

void ParticleObject::Update(double deltaTime)
{
	// reduce life
	m_life -= deltaTime;

	// a = v / t
	// v = p / t
	//=> v = a * t
	// p = v * t

	Vector currentPosition = GetPos();
	m_velocity += m_acceleration * deltaTime;
	Vector newPosition = currentPosition + m_velocity * deltaTime;

	SetPos(newPosition);
}
