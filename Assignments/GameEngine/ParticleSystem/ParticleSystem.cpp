#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(Sprite* sprite, float delayTime, bool loop, float scale)
{
	// set particle sprite
	m_sprite = sprite;

	m_emissionRate = 1.0f;

	m_particleLifeTime = 1.0f;

	m_delayTime = delayTime;
	m_loop = loop;

	m_timer = 0.0f;

	m_scale = scale;
}

ParticleSystem::~ParticleSystem()
{
	// delete pointers
	// loop through all elements in the particle list
	std::list<ParticleObject*>::iterator particleIter = m_particleList.begin();
	while (particleIter != m_particleList.end())
	{
		ParticleObject* po = *particleIter;

		delete po;
		// increase iteration
		particleIter++;
	}
	// loop through all elements in the affector list
	std::list<ParticleAffector*>::iterator affectorIter = m_particleAffectorList.begin();
	while (affectorIter != m_particleAffectorList.end())
	{
		ParticleAffector* pA = *affectorIter;

		delete pA;
		// increase iteration
		affectorIter++;
	}
	// clear list
	m_particleList.clear();
	m_particleAffectorList.clear();

	if (m_emitterShape != NULL)
	{
		delete m_emitterShape;
	}
}

ParticleObject* ParticleSystem::InitializeParticleObject()
{
	// initialize particle object
	ParticleObject* po = new ParticleObject();

	// set particle sprite
	po->SetSprite(m_sprite);
	// set particle life time 
	po->SetLife(m_particleLifeTime);

	Color white;
	white.r = 1.0f;
	white.g = 1.0f;
	white.b = 1.0f;
	white.a = 0.5f;

	// set particle color
	po->SetColor(white);
	// set scale
	po->SetScale(m_scale);
	// set rotation
	po->SetRotation(0.0f);
	// set blend mode
	po->SetBlendingMode(ADDITIVE);
	// initialize velocity
	po->SetVelocity(Vector(0.0f, 0.0f, 0.0f));
	// initialize random acceleration 
	po->SetAcceleration(Vector(0.0f, 0.0f, 0.0f));

	// cache this particle object position
	Vector poPosition = Vector(0.0f, 0.0f, 0.0f);

	// if emitter shape is null, declare one
	if (m_emitterShape == NULL)
	{
		EmitterShape* poiShape = new PointShape();
		m_emitterShape = poiShape;
	}

	// randomize a spawn position that within emitter shape boundaries
	if (m_emitterShape->GetEmitterShapeName() != POINT_SHAPE)
	{
		poPosition = m_emitterShape->GetParticleEmissionPos(&m_position);
	}
	else
	{
		poPosition = m_emitterShape->GetParticleEmissionPos(&m_position);
	}

	// intialize all particles position at particle system position
	po->SetPos(poPosition);

	return po;
}

void ParticleSystem::SetEmissionRate(float emissionRate)
{
	m_emissionRate = emissionRate;
}

float ParticleSystem::GetEmissionRate()
{
	return m_emissionRate;
}

void ParticleSystem::SetPosition(Vector position)
{
	m_position = position;
}

Vector ParticleSystem::GetPosition()
{
	return m_position;
}

void ParticleSystem::SetParticleLifeTime(float lifetime)
{
	m_particleLifeTime = lifetime;
}

float ParticleSystem::GetParticleLifeTime()
{
	return m_particleLifeTime;
}

void ParticleSystem::SetInitialScale(float scale)
{
	m_scale = scale;
}

void ParticleSystem::EmitParticles()
{
	/* initialize random seed: */
	srand(time(NULL));

	// push x number of new particle objects to the list
	for (int i = 0; i < m_emissionRate; i++)
	{
		ParticleObject* po = InitializeParticleObject();

		m_particleList.push_back(po);
	}
}

// set affector
void ParticleSystem::AddParticleAffector(ParticleAffector * pA)
{
	ParticleAffector* temp = GetAffectorFromList(pA->GetAffectorName());

	if (temp == NULL)
	{
		m_particleAffectorList.push_back(pA);
	}
}

void ParticleSystem::RemoveParticleAffector(ParticleAffector * pA)
{
	// get affector from list of affectors if there is one
	std::list<ParticleAffector*>::iterator iter = m_particleAffectorList.begin();
	while (iter != m_particleAffectorList.end())
	{
		ParticleAffector* temp = *iter;

		// if found, then erase from list
		if (temp == pA)
		{
			iter = m_particleAffectorList.erase(iter);
		}
	}
}

ParticleAffector* ParticleSystem::GetAffectorFromList(AffectorName affectorName)
{
	// get affector from list of affectors if there is one
	std::list<ParticleAffector*>::iterator iter = m_particleAffectorList.begin();
	while (iter != m_particleAffectorList.end())
	{
		ParticleAffector* pA = *iter;

		if (pA->GetAffectorName() == affectorName)
		{
			return pA;
		}

		iter++;
	}

	return NULL;
}

void ParticleSystem::SetEmitterShape(EmitterShape* emitterShape)
{
	m_emitterShape = emitterShape;
}

void ParticleSystem::StartCycle()
{
	m_startCycle = true;
}

void ParticleSystem::EndCycle()
{
	m_startCycle = false;
}

bool ParticleSystem::GetLoopBoolean()
{
	return m_loop;
}

//==============================================================================================
// Update
void ParticleSystem::Update(double deltaTime)
{
	// if not looping
	// emit particles manually based on time
	if (m_startCycle == true && m_loop == false)
	{
		m_timer = 0.0f;
		//emit once for time based emission
		m_startCycle = false;
	}

	// emit particles through looping
	if (m_timer >= m_delayTime)
	{
		EmitParticles();

		if (m_loop == true)
		{
			m_timer = 0.0f;
		}
		else if (m_loop == false)
		{
			m_timer = -1.0f;
		}
	}
	else if(m_timer >= 0.0f)
	{
		m_timer += deltaTime;
	}
/*	
	// emit particle if the list is empty
	if (m_particleList.empty())
	{
		SetEmissionRate(m_emissionRate);
	}
*/

	// loop through all elements in the list
	std::list<ParticleObject*>::iterator iter = m_particleList.begin();
	while (iter != m_particleList.end())
	{
		ParticleObject* po = *iter;

		if (po->GetLife() > 0)
		{
			// runs all particle affectors AffectParticleUpdate()
			// loop through all elements in the list
			std::list<ParticleAffector*>::iterator affectorIter = m_particleAffectorList.begin();
			while (affectorIter != m_particleAffectorList.end())
			{
				ParticleAffector* pA = *affectorIter;

				pA->AffectParticleUpdate(po, deltaTime);

				affectorIter++;
			}

			// right after first frame(first initialization for particles)
			po->SetInitializationCondition(true);
			
			// update the particles movement
			po->Update(deltaTime);

			// increase iteration
			iter++;
		}
		// remove from list if particle object life time is lesser or equal to zero
		else if (po->GetLife() <= 0)
		{
			delete po;
			iter = m_particleList.erase(iter);
		}
	}
}

void ParticleSystem::Draw()
{
	// loop through all elements in the list and draw
	std::list<ParticleObject*>::iterator iter = m_particleList.begin();
	while (iter != m_particleList.end())
	{
		ParticleObject* po = *iter;

		// draw particles
		po->Draw();

		// set box collider position
		po->SetBoxColliderSize(po->GetSprite()->GetPositionMatrix());

		// increase iteration
		iter++;
	}
}
