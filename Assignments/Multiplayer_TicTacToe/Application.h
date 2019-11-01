#ifndef APPLICATION_H
#define APPLICATION_H

#include <GLFW/glfw3.h>
#include <iostream>
#include "TicTacToe.h"

class Application
{
private:
	TicTacToe* ticTacToeGame;

public:
	Application();
	virtual ~Application();

	virtual void Start();
	virtual void Update(double deltaTime);
	virtual void Draw();
};

#endif
