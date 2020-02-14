#ifndef PARTICLEOBJECT_H
#define PARTICLEOBJECT_H

#include "GameObject.h"

class ParticleObject : public GameObject
{
private:
	Vector m_velocity;
	Vector m_acceleration;
	float m_life;

	// to set up intial value set by user
	bool hasInitialized;

public:
	ParticleObject();
	~ParticleObject();

	void SetVelocity(Vector velocity);
	Vector GetVelocity();
	void SetAcceleration(Vector acceleration);
	Vector GetAcceleration();
	void SetLife(float lifeTime);
	float GetLife();

	void SetInitializationCondition(bool initialized);
	bool GetInitializationCondition();

	void Update(double deltaTime);

};

#endif