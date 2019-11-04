#include "Application.h"

Application::Application()
{
	Color white;
	white.r = 1.0f;
	white.g = 1.0f;
	white.b = 1.0f;
	white.a = 1.0f;

	//mySprite.push_back(Sprite("../Media/tree.bmp") );
	particleSprite_z = new Sprite("../Media/spark.bmp");
	particleSprite_a = new Sprite("../Media/particleO.bmp");
	particleSprite_b = new Sprite("../Media/particleB.bmp");
	particleSprite_o = new Sprite("../Media/particleA.bmp");
/*
	GameObject tree = GameObject(particleSprite, Vector(320.0f, 240.0f, 0.0f), 0.0f, 1.0f, white, NONE);
	GameObject treeCollision = GameObject(particleSprite, Vector(520.0f, 340.0f, 0.0f), 0.0f, 0.5f, white, NONE);
	gameObject.push_back(tree);
	gameObject.push_back(tree);

	gameObject.push_back(treeCollision);
	gameObject.push_back(treeCollision);

	gameObject[1].SetBlendingMode(ALPHA_BLEND);
	gameObject[1].SetRotation(45.0f);

	gameObject[2].SetPos(Vector(120.0f, 400.0f, 0.0f));
	gameObject[3].SetPos(Vector(520.0f, 400.0f, 0.0f));
*/

	// ================================================================
	float oneCycleTime;

	// particle system initialization
	ParticleSystem* backgroundPS;
	// delay and loop
	backgroundPS = new ParticleSystem(particleSprite_z, 0.4f, true, 0.1f);
	backgroundPS->SetPosition(Vector(320.0f, 240.0f, 0.0f));
	backgroundPS->SetParticleLifeTime(1.2f);

	ParticleSystem* firstPS;
	// delay and loop
	firstPS = new ParticleSystem(particleSprite_a, 0.0f, false, 0.3f);
	firstPS->SetPosition(Vector(320.0f, 240.0f, 0.0f));
	firstPS->SetParticleLifeTime(2.0f);

	ParticleSystem* secondPS;
	// delay and loop
	secondPS = new ParticleSystem(particleSprite_b, 1.0f, false, 0.5f);
	secondPS->SetPosition(Vector(320.0f, 240.0f, 0.0f));
	secondPS->SetParticleLifeTime(2.0f);

	// ================================================================
	// affector initialization
	GravityAffector* gA = new GravityAffector();

	ScaleAffector* sA = new ScaleAffector();
	sA->SetInitialScale(0.1f);
	sA->SetEndScale(0.5f);

	AccelerationAffector* aA = new AccelerationAffector();
	aA->SetInitialAcceleration(Vector(.0f, 0.0f, 0.0f));
	aA->SetEndAcceleration(Vector(0.0f, 0.0f, 0.0f));
	aA->SetMinRandomRange(-200.0f);
	aA->SetMaxRandomRange(200.0f);

	// background
	AttractorAffector* attractAffector_z = new AttractorAffector(Vector(320.0f, 240.0f, 0.0f));
	// slower spped
	attractAffector_z->SetSpeedVariance(0.3f);
	// first particle system
	AttractorAffector* attractAffector_a = new AttractorAffector(Vector(320.0f, 240.0f, 0.0f));

	RotatorAffector* rotatorAffector_z = new RotatorAffector();
	RotatorAffector* rotatorAffector_b = new RotatorAffector();

	Color objectOColor;
	objectOColor.r = 1.0f;
	objectOColor.g = 0.1f;
	objectOColor.b = 0.0f;
	objectOColor.a = 1.0f;

	GameObject object = GameObject(particleSprite_o, Vector(320.0f, 240.0f, 0.0f), 0.0f, 1.0f, objectOColor, ADDITIVE);
	object.Draw();
	object.SetBoxColliderSize(object.GetSprite()->GetPositionMatrix());
	gameObject.push_back(object);

	CollisionAffector* cA = new CollisionAffector(object);

	Color z_c1;
	z_c1.r = 0.8f;
	z_c1.g = 0.8f;
	z_c1.b = 0.0f;
	z_c1.a = 0.6f;

	Color z_c2;
	z_c2.r = 0.4f;
	z_c2.g = 0.4f;
	z_c2.b = 0.0f;
	z_c2.a = 0.5f;

	Color a_c1;
	a_c1.r = 0.8f;
	a_c1.g = 0.15f;
	a_c1.b = 0.0f;
	a_c1.a = 0.5f;

	Color a_c2;
	a_c2.r = 1.0f;
	a_c2.g = 0.9f;
	a_c2.b = 0.0f;
	a_c2.a = 0.8f;

	Color b_c1;
	b_c1.r = 0.15f;
	b_c1.g = 0.0f;
	b_c1.b = 1.0f;
	b_c1.a = 0.5f;

	Color b_c2;
	b_c2.r = 1.0f;
	b_c2.g = 0.0f;
	b_c2.b = 0.5f;
	b_c2.a = 0.5f;

	// background
	ColorAffector* colorAffector_z = new ColorAffector();
	colorAffector_z->SetInitialColor(z_c1);
	colorAffector_z->SetEndColor(z_c2);
	colorAffector_z->RandomizeInitialColor(true, true, true, true);
	// first particle system
	ColorAffector* colorAffector_a = new ColorAffector();
	colorAffector_a->SetInitialColor(a_c1);
	colorAffector_a->SetEndColor(a_c2);
	colorAffector_a->RandomizeInitialColor(true, true, false, true);
	// second particle system
	ColorAffector* colorAffector_b = new ColorAffector();
	colorAffector_b->SetInitialColor(b_c1);
	colorAffector_b->SetEndColor(b_c2);
	colorAffector_b->RandomizeInitialColor(true, true, true, true);


	// ================================================================
	// emitter shape initialization
	Vector psPos = backgroundPS->GetPosition();
	EmitterShape* poiShape = new PointShape();
	EmitterShape* recShape = new RectangleShape(600);
	EmitterShape* cirShape = new CircleShape(200);

	// ================================================================
	backgroundPS->SetEmitterShape(recShape);
	firstPS->SetEmitterShape(cirShape);
	secondPS->SetEmitterShape(poiShape);

	// ================================================================

	// change color from white to black
	backgroundPS->AddParticleAffector(colorAffector_z);
	// attract to mid point
	backgroundPS->AddParticleAffector(attractAffector_z);
	// random rotation
	backgroundPS->AddParticleAffector(rotatorAffector_z);
	// color
	firstPS->AddParticleAffector(colorAffector_a);
	// attract particle to a point
	firstPS->AddParticleAffector(attractAffector_a);
	// collide with point
	firstPS->AddParticleAffector(cA);
	// color
	secondPS->AddParticleAffector(colorAffector_b);
	// rotator
	secondPS->AddParticleAffector(rotatorAffector_b);
	// random acceleration
	secondPS->AddParticleAffector(aA);
	// gravity 
	secondPS->AddParticleAffector(gA);
	// scale
	secondPS->AddParticleAffector(sA);

	backgroundPS->SetEmissionRate(200);
	firstPS->SetEmissionRate(200);
	secondPS->SetEmissionRate(200);

	m_particleSystemList.push_back(backgroundPS);
	m_particleSystemList.push_back(firstPS);
	m_particleSystemList.push_back(secondPS);

	// emit particle at first
	backgroundPS->EmitParticles();
	//firstPS->EmitParticles();
}

Application::~Application()
{
	// temporary delete all sprites
	//for (int i = 0; i < gameObject.size(); i++)
	//{
	//	delete gameObject[0].GetSprite();
	//}

	std::list<ParticleSystem*>::iterator psIter = m_particleSystemList.begin();
	for (psIter; psIter != m_particleSystemList.end(); psIter++)
	{
		ParticleSystem* currentPS = *psIter;

		delete currentPS;
	}

	delete particleSprite_z;
	delete particleSprite_a;
	delete particleSprite_b;
	delete particleSprite_o;
}

void Application::Start()
{
	//glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	//glDisable(GL_DEPTH_TEST);
	std::cout << "Application Start!" << std::endl;
}

void Application::Update(double deltaTime)
{
	/*
	//std::cout << "Application Update!" << std::endl;
	for (int i = 0; i < gameObject.size(); i++)
	{
		gameObject[i].Update(deltaTime);
	}
	*/

	// cache time passed to control particle emission
	static float timePassed = 0.0f;
	timePassed += deltaTime;

	// one cycle time
	// cannot smaller than m_delayTime
	static float cycleTime = 3.0f;

	std::list<ParticleSystem*>::iterator psIter = m_particleSystemList.begin();
	for (psIter; psIter != m_particleSystemList.end(); psIter++)
	{
		ParticleSystem* currentPS = *psIter;

		// manually emit particle based on time
		if (timePassed >= cycleTime)
		{
			// if not looping (don't use cycle if it is looping)
			if (currentPS->GetLoopBoolean() == false)
			{
				currentPS->StartCycle();
			}
		}

		currentPS->Update(deltaTime);
	}

	if (timePassed >= cycleTime)
	{
		timePassed = 0.0f;
	}

	static float m_rotation = 0.0f;
	m_rotation ++;
	gameObject[0].SetRotation(m_rotation);
}

void Application::Draw()
{
	Color white;
	white.r = 1.0f;
	white.g = 1.0f;
	white.b = 1.0f;
	white.a = 0.5f;

	//std::cout << "Application Draw!" << std::endl;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*
	static float rotationIncrement = 0.0f;
	rotationIncrement = 0.1f;

	static float scaleIncrement = 0.0f;
	if(scaleIncrement<4.0f)
		scaleIncrement += 0.01f;

	static int collideObject1 = 2;
	static int collideObject2 = 3;

	for (int i = 0; i < gameObject.size(); i++)
	{
		if ( i < 2)
		{
			static float tempX = gameObject[i].GetPos().mVal[0];
			static float tempY = gameObject[i].GetPos().mVal[1];

			float r = gameObject[i].GetRotation() + rotationIncrement;

			gameObject[i].SetRotation(r);
			gameObject[i].SetScale(scaleIncrement);
			
		}

		//==========================================================================================
		// Collision
		// change sprite color if collide
		if (gameObject[collideObject1].GetBoxCollider().IsCollided(gameObject[collideObject2].GetBoxCollider()))
		{
			Color red;
			red.r = 1.0f;
			red.g = 0.0f;
			red.b = 0.0f;
			red.a = 1.0f;

			gameObject[collideObject1].SetColor(red);
			gameObject[collideObject2].SetColor(red);
		}
		else
		{
			gameObject[collideObject1].SetColor(white);
			gameObject[collideObject2].SetColor(white);
		}

		// keep the colliding object moving by switching collideObject 1 and 2
		if (gameObject[collideObject2].GetPos().mVal[0] <= 120.0f)
		{
			int temp = collideObject2;
			collideObject2 = collideObject1;
			collideObject1 = temp;
		}
		// move collide object 1 & 2
		Vector newPos = gameObject[collideObject1].GetPos() + Vector(0.5f, 0.0f, 0.0f);
		gameObject[collideObject1].SetPos(newPos);
		Vector newPos2 = gameObject[collideObject2].GetPos() - Vector(0.5f, 0.0f, 0.0f);
		gameObject[collideObject2].SetPos(newPos2);

		//==========================================================================================
		gameObject[i].Draw();

		gameObject[i].SetBoxColliderSize(gameObject[i].GetSprite()->GetPositionMatrix());

		gameObject[i].DrawBoxCollider();
	}
*/
	gameObject[0].Draw();
	std::list<ParticleSystem*>::iterator psIter = m_particleSystemList.begin();
	for (psIter; psIter != m_particleSystemList.end(); psIter++)
	{
		ParticleSystem* currentPS = *psIter;

		currentPS->Draw();
	}
}