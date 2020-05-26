#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "ParticleObject.h"
#include "ParticleAffector.h"
#include "EmitterShape.h"
#include <list>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

class ParticleSystem
{
private:
	Sprite* m_sprite;
	std::list<ParticleObject*> m_particleList;
	float m_emissionRate;
	//int m_emissionCount;
	Vector m_position;
	std::list<ParticleAffector*> m_particleAffectorList;
	float m_particleLifeTime;

	float m_scale;

	// emitter shape
	EmitterShape* m_emitterShape;

	// delay 
	float m_delayTime;
	// loop
	bool m_loop;
	// timer
	float m_timer;
	// start a new cycle
	bool m_startCycle;

public:
	ParticleSystem(Sprite* sprite, float delayTime, bool loop, float scale);
	~ParticleSystem();

	// initialize particle object
	ParticleObject* InitializeParticleObject();

	void SetEmissionRate(float emissionRate);
	float GetEmissionRate();
	void SetPosition(Vector position);
	Vector GetPosition();
	void SetParticleLifeTime(float lifetime);
	float GetParticleLifeTime();

	// set particle initial scale
	void SetInitialScale(float scale);

	// re-initialize / push particles in the list
	void EmitParticles();

	// Set particle has which affector
	void AddParticleAffector(ParticleAffector* pA);
	// remove affector from list
	void RemoveParticleAffector(ParticleAffector* pA);
	// Get related affector
	ParticleAffector* GetAffectorFromList(AffectorName affectorName);
	// initialize emitter shape
	void SetEmitterShape(EmitterShape* emitterShape);

	// start cycle
	void StartCycle();
	void EndCycle();
	// get loop to avoid turning cycle bool = true
	bool GetLoopBoolean();

	void Update(double deltaTime);
	void Draw();
};

#endif