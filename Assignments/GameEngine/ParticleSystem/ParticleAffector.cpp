#include "ParticleAffector.h"

ParticleAffector::ParticleAffector()
{
	
}

ParticleAffector::~ParticleAffector()
{
}

void ParticleAffector::SetAffectorName(AffectorName name)
{
	m_affectorName = name;
}

AffectorName ParticleAffector::GetAffectorName()
{
	return m_affectorName;
}

void ParticleAffector::AffectParticleUpdate(ParticleObject * particle, double deltaTime)
{
}

//============================================================================
// Gravity
GravityAffector::GravityAffector() : ParticleAffector()
{
	m_gravity = Vector(0.0f, -9.81f, 0.0f);
	
	SetAffectorName(GRAVITY_AFFECTOR);
}

GravityAffector::~GravityAffector()
{
}

void GravityAffector::SetGravity(float gravityValue)
{
	m_gravity = Vector(0.0f, gravityValue, 0.0f);
}

void GravityAffector::AffectParticleUpdate(ParticleObject * particle, double deltaTime)
{
	Vector temp = particle->GetAcceleration();
	temp += m_gravity;
	particle->SetAcceleration(temp);
}

//============================================================================
// Scale Over Time
ScaleAffector::ScaleAffector() : ParticleAffector()
{
	m_initialScale = 1.0f;
	
	m_endScale = 1.0f;

	m_scaleVariance = 0.0f;

	SetAffectorName(SCALE_AFFECTOR);
}

ScaleAffector::~ScaleAffector()
{
}

void ScaleAffector::SetInitialScale(float initialScale)
{
	m_initialScale = initialScale;
}

float ScaleAffector::GetInitialScale()
{
	return m_initialScale;
}

void ScaleAffector::SetEndScale(float endScale)
{
	m_endScale = endScale;
}

float ScaleAffector::GetEndScale()
{
	return m_endScale;
}

void ScaleAffector::AffectParticleUpdate(ParticleObject * particle, double deltaTime)
{
	if (particle->GetInitializationCondition() == false)
	{
		// calculate variance value once
		m_scaleVariance = (m_endScale - m_initialScale) / particle->GetLife();
	}

	// update particles scale over time
	float temp = particle->GetScale() + m_scaleVariance * deltaTime;
	particle->SetScale(temp);
}

//============================================================================
// Acceleration Over Time
AccelerationAffector::AccelerationAffector()
{
	m_initialAcceleration = Vector(1.0f, 1.0f, 0.0f);

	m_endAcceleration = Vector(1.0f, 1.0f, 0.0f);

	SetAffectorName(ACCELERATION_AFFECTOR);
}

AccelerationAffector::~AccelerationAffector()
{
}

void AccelerationAffector::SetInitialAcceleration(Vector initialAcceleration)
{
	m_initialAcceleration = initialAcceleration;

}

Vector AccelerationAffector::GetInitialAcceleration()
{
	return m_initialAcceleration;
}

void AccelerationAffector::SetEndAcceleration(Vector endAcceleration)
{
	m_endAcceleration = endAcceleration;
}

Vector AccelerationAffector::GetEndAcceleration()
{
	return m_endAcceleration;
}

void AccelerationAffector::SetMinRandomRange(float minValue)
{
	m_minRandomRange = minValue;
}

float AccelerationAffector::GetMinRandomRange()
{
	return m_minRandomRange;
}

void AccelerationAffector::SetMaxRandomRange(float maxValue)
{
	m_maxRandomRange = maxValue;
}

float AccelerationAffector::GetMaxRandomRange()
{
	return m_maxRandomRange;
}

void AccelerationAffector::SetRandomAcceleration()
{
	float newAffectValueX = rand() % ((int)m_maxRandomRange - (int)m_minRandomRange + 1) + (int)m_minRandomRange;
	float newAffectValueY = rand() % ((int)m_maxRandomRange - (int)m_minRandomRange + 1) + (int)m_minRandomRange;

	m_resultAcceleration = Vector(newAffectValueX, newAffectValueY, 0.0f);
}

void AccelerationAffector::AffectParticleUpdate(ParticleObject * particle, double deltaTime)
{
	if (particle->GetInitializationCondition() == false)
	{
		// calculate variance value once
		m_accelerationVariance = (m_endAcceleration - m_initialAcceleration) / particle->GetLife();
	}

	if (particle->GetAcceleration().mVal[0] == 0.0f && particle->GetAcceleration().mVal[1] == 0.0f)
	{
		SetRandomAcceleration();
		particle->SetAcceleration(m_resultAcceleration);
	}

	if (m_initialAcceleration.mVal[0] != m_endAcceleration.mVal[0]
		&& m_initialAcceleration.mVal[1] != m_endAcceleration.mVal[1])
	{
		// update particles acceleration over time based on acceleration affector
		Vector tempAcceleration = particle->GetAcceleration() + m_accelerationVariance;
		particle->SetAcceleration(tempAcceleration);
	}
	else
	{
		//SetRandomAffectValue();
	}

}

//============================================================================
// Attractor Over Time
AttractorAffector::AttractorAffector(Vector centerPos)
{
	m_attractorPosition = centerPos;

	// default speed = 1.0
	m_speedVariance = 1.0f;

	SetAffectorName(ATTRACTOR_AFFECTOR);
}

AttractorAffector::~AttractorAffector()
{
}

void AttractorAffector::SetSpeedVariance(float speed)
{
	m_speedVariance = speed;
}

void AttractorAffector::SetAttractorPosition(Vector pos)
{
	m_attractorPosition = pos;
}

Vector AttractorAffector::GetAttractorPosition()
{
	return m_attractorPosition;
}

void AttractorAffector::AffectParticleUpdate(ParticleObject * particle, double deltaTime)
{
	if (particle->GetInitializationCondition() == false)
	{
		Vector resultValue;

		resultValue = m_attractorPosition - particle->GetPos();

		resultValue *= m_speedVariance;

		particle->SetAcceleration(resultValue);
	}
}

//============================================================================
// Color Over Time
ColorAffector::ColorAffector()
{
	Color white;
	white.r = 1.0f;
	white.g = 1.0f;
	white.b = 1.0f;
	white.a = 0.5f;

	Color zero;
	zero.r = 0.0f;
	zero.g = 0.0f;
	zero.b = 0.0f;
	zero.a = 0.0f;

	m_initialColor = white;

	m_endColor = white;

	m_colorVariance = zero;

	// randomize color bool
	b_randomInitialColor = false;
	b_randomizeR = false;
	b_randomizeG = false;
	b_randomizeB = false;

	SetAffectorName(COLOR_AFFECTOR);
}

ColorAffector::~ColorAffector()
{
}

void ColorAffector::SetInitialColor(Color initialColor)
{
	m_initialColor = initialColor;
}

Color ColorAffector::GetInitialColor()
{
	return m_initialColor;
}

void ColorAffector::SetEndColor(Color endColor)
{
	m_endColor = endColor;
}

Color ColorAffector::GetEndColor()
{
	return m_endColor;
}

void ColorAffector::RandomizeInitialColor(bool value, bool rChannel, bool gChannel, bool bChannel)
{
	b_randomInitialColor = value;

	b_randomizeR = rChannel;
	b_randomizeG = gChannel;
	b_randomizeB = bChannel;
}

void ColorAffector::AffectParticleUpdate(ParticleObject * particle, double deltaTime)
{
	if (particle->GetInitializationCondition() == false)
	{
		Color initialColor = m_initialColor;
		// for background color only now
		if (b_randomInitialColor == true)
		{
			float newR = rand() % 10 + 1;
			float newG = rand() % 10 + 1;
			float newB = rand() % 10 + 1;

			newR *= 0.1f;
			newG *= 0.1f;
			newB *= 0.1f;

			if (b_randomizeR == true)
			{
				initialColor.r = newR;
			}
			if (b_randomizeG == true)
			{
				initialColor.g = newG;
			}
			if (b_randomizeB == true)
			{
				initialColor.b = newB;
			}
		}

		particle->SetColor(initialColor);

		// calculate variance value once
		if (m_endColor.r != m_initialColor.r)
		{
			m_colorVariance.r = (m_endColor.r - m_initialColor.r) / particle->GetLife();
		}
		if (m_endColor.g != m_initialColor.g)
		{
			m_colorVariance.g = (m_endColor.g - m_initialColor.g) / particle->GetLife();
		}
		if (m_endColor.b != m_initialColor.b)
		{
			m_colorVariance.b = (m_endColor.b - m_initialColor.b) / particle->GetLife();
		}
		if (m_endColor.a != m_initialColor.a)
		{
			m_colorVariance.a = (m_endColor.a = m_initialColor.a) / particle->GetLife();
		}
	}

	// update particles scale over time
	Color temp;

	temp.r = particle->GetColor().r + m_colorVariance.r *deltaTime;
	temp.g = particle->GetColor().g + m_colorVariance.g *deltaTime;
	temp.b = particle->GetColor().b + m_colorVariance.b *deltaTime;
	temp.a = particle->GetColor().a + m_colorVariance.a *deltaTime;

	particle->SetColor(temp);
}


//============================================================================
// collision 
CollisionAffector::CollisionAffector(GameObject object)
{
	m_affectorName = COLLISION_AFFECTOR;

	collisionObject = object;
}

CollisionAffector::~CollisionAffector()
{
}

void CollisionAffector::AffectParticleUpdate(ParticleObject * particle, double deltaTime)
{
	if (particle->GetBoxCollider().IsCollided(collisionObject.GetBoxCollider()))
	{
		particle->SetLife(0.0f);
	}
}

//============================================================================
// Rotation 
RotatorAffector::RotatorAffector()
{
	m_rotationAngle = 0.0f;

	m_affectorName = ROTATOR_AFFECTOR;
}

RotatorAffector::~RotatorAffector()
{
}

void RotatorAffector::SetAngle(float angle)
{
	m_rotationAngle = angle;
}

float RotatorAffector::GetAngle()
{
	return 	m_rotationAngle;
}

void RotatorAffector::AffectParticleUpdate(ParticleObject * particle, double deltaTime)
{
	if (particle->GetInitializationCondition() == false)
	{
		// random rotation
		m_rotationAngle = rand() % 360;

		particle->SetRotation(m_rotationAngle);
	}
}
