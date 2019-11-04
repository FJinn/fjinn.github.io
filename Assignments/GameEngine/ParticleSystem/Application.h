#ifndef APPLICATION_H
#define APPLICATION_H

#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "Sprite.h"
#include "GameObject.h"
#include "ParticleSystem.h"

class Application
{
private:
	std::vector<GameObject> gameObject;
	std::list<ParticleSystem*> m_particleSystemList;

	Sprite* particleSprite_z;
	Sprite* particleSprite_a;
	Sprite* particleSprite_b;
	Sprite* particleSprite_o;

public:
	Application();
	virtual ~Application();

	virtual void Start();
	virtual void Update(double deltaTime);
	virtual void Draw();
};

#endif
