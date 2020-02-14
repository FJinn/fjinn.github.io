#ifndef PARTICLEAFFECTOR_H
#define PARTICLEAFFECTOR_H

#include "vector.h"
#include "matrix.h"
#include "ParticleObject.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

enum AffectorName
{
	NONE_AFFECTOR = 0,
	GRAVITY_AFFECTOR,
	SCALE_AFFECTOR,
	ACCELERATION_AFFECTOR,
	ATTRACTOR_AFFECTOR,
	COLOR_AFFECTOR,
	COLLISION_AFFECTOR,
	ROTATOR_AFFECTOR
};

class ParticleAffector
{
protected:
	AffectorName m_affectorName;

public:
	ParticleAffector();
	~ParticleAffector();
	
	void SetAffectorName(AffectorName name);
	AffectorName GetAffectorName();

	// everything done in this file
	virtual void AffectParticleUpdate(ParticleObject* particle, double deltaTime) = 0;
};

//============================================================================
// Gravity
class GravityAffector : public ParticleAffector
{
private:
	Vector m_gravity;
public:
	GravityAffector();
	~GravityAffector();

	void SetGravity(float gravityValue);

	void AffectParticleUpdate(ParticleObject* particle, double deltaTime);
};

//============================================================================
// Scale Over Time
class ScaleAffector : public ParticleAffector
{
private:
	float m_initialScale;
	float m_endScale;

	float m_scaleVariance;

public:
	ScaleAffector();
	~ScaleAffector();

	void SetInitialScale(float initialScale);
	float GetInitialScale();
	void SetEndScale(float endScale);
	float GetEndScale();

	void AffectParticleUpdate(ParticleObject* particle, double deltaTime);
};

//============================================================================
// Acceleration Over Time
class AccelerationAffector : public ParticleAffector
{
private:
	Vector m_initialAcceleration;
	Vector m_endAcceleration;

	Vector m_accelerationVariance;

	float m_minRandomRange;
	float m_maxRandomRange;

	Vector m_resultAcceleration;

public:
	AccelerationAffector();
	~AccelerationAffector();

	void SetInitialAcceleration(Vector initialAcceleration);
	Vector GetInitialAcceleration();
	void SetEndAcceleration(Vector endAcceleration);
	Vector GetEndAcceleration();

	void SetMinRandomRange(float minValue);
	float GetMinRandomRange();
	void SetMaxRandomRange(float maxValue);
	float GetMaxRandomRange();

	void SetRandomAcceleration();

	void AffectParticleUpdate(ParticleObject* particle, double deltaTime);
};

//============================================================================
// Attractor Over Time
class AttractorAffector : public ParticleAffector
{
private:
	Vector m_attractorPosition;

	float m_speedVariance;

	Vector m_initializeAcceleration;

public:
	AttractorAffector(Vector centerPos);
	~AttractorAffector();

	void SetSpeedVariance(float speed);

	void SetAttractorPosition(Vector pos);
	Vector GetAttractorPosition();

	void AffectParticleUpdate(ParticleObject* particle, double deltaTime);
};

//============================================================================
// Color Over Time
class ColorAffector : public ParticleAffector
{
private:
	Color m_initialColor;
	Color m_endColor;

	// randomize color
	bool b_randomInitialColor;
	// bool to include channel
	bool b_randomizeR;
	bool b_randomizeG;
	bool b_randomizeB;

	Color m_colorVariance;
public:
	ColorAffector();
	~ColorAffector();

	void SetInitialColor(Color initialColor);
	Color GetInitialColor();
	void SetEndColor(Color endColor);
	Color GetEndColor();

	void RandomizeInitialColor(bool value, bool rChannel, bool gChannel, bool bChannel);

	void AffectParticleUpdate(ParticleObject* particle, double deltaTime);
};

//============================================================================
// collision 
class CollisionAffector : public ParticleAffector
{
private:
	GameObject collisionObject;
public:
	CollisionAffector(GameObject object);
	~CollisionAffector();

	void AffectParticleUpdate(ParticleObject* particle, double deltaTime);
};

//============================================================================
// Rotation 
class RotatorAffector : public ParticleAffector
{
private:
	float m_rotationAngle;

public:
	RotatorAffector();
	~RotatorAffector();

	void SetAngle(float angle);
	float GetAngle();

	void AffectParticleUpdate(ParticleObject* particle, double deltaTime);
};

#endif