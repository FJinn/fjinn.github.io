#include "Application.h"

Application::Application()
{
	ticTacToeGame = new TicTacToe();
}

Application::~Application()
{
	delete ticTacToeGame;
}

void Application::Start()
{
	//glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	//glDisable(GL_DEPTH_TEST);
	std::cout << "Application Start!" << std::endl;

	ticTacToeGame->Start();
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

	ticTacToeGame->Update(deltaTime);
}

void Application::Draw()
{
	//std::cout << "Application Draw!" << std::endl;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	ticTacToeGame->Draw();
}