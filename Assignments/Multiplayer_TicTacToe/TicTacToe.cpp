#include "TicTacToe.h"

TicTacToe::TicTacToe()
{
	Color white;
	white.r = 1.0f;
	white.g = 1.0f;
	white.b = 1.0f;
	white.a = 1.0f;

	logoSprite = new Sprite("../Media/TicTacToeLogo.bmp", 720, 320);
	boardSprite = new Sprite("../Media/TicTacToeBoard.bmp", 600, 596);
	firstPlayerSprite = new Sprite("../Media/Cross.bmp", 180, 180);
	secondPlayerSprite = new Sprite("../Media/Circle.bmp", 180, 180);
	firstPlayerWinSprite = new Sprite("../Media/CrossWin.bmp", 180, 180);
	secondPlayerWinSprite = new Sprite("../Media/CircleWin.bmp", 180, 180);
	emptySprite = new Sprite("../Media/Empty.bmp", 180, 180);
	restartSprite = new Sprite("../Media/Restart.bmp", 360, 180);
	undoSprite = new Sprite("../Media/Undo.bmp", 360, 180);
	yourTurnSprite = new Sprite("../Media/YourTurn.bmp", 540, 90);
	othersTurnSprite = new Sprite("../Media/OthersTurn.bmp", 540, 90);
	waitingSprite = new Sprite("../Media/Waiting.bmp", 540, 90);
	youWinSprite = new Sprite("../Media/Win.bmp", 540, 90);
	youLoseSprite = new Sprite("../Media/Lose.bmp", 540, 90);
	tieSprite = new Sprite("../Media/Tie.bmp", 540, 90);

	// top = x, 314
	// mid = 400, 200
	// bot = x, 84
	// left = 285, y
	// right = 515, y

	// draw board first, so circle/cross will be drawn above board
	GameObject gameBoard = GameObject(boardSprite, Vector(400.0f, 200.0f, 0.0f), 0.0f, 0.6f, white, NONE);
	gameObject.push_back(gameBoard);

	//===========================================================================================================
	// start with 1 from top left then mid left 4 and bot right 9
	GameObject topLeftBoard = GameObject(emptySprite, Vector(285.0f, 314.0f, 0.0f), 0.0f, 0.5f, white, NONE);
	gameObject.push_back(topLeftBoard);

	GameObject topMidBoard = GameObject(emptySprite, Vector(400.0f, 314.0f, 0.0f), 0.0f, 0.5f, white, NONE);
	gameObject.push_back(topMidBoard);

	GameObject topRightBoard = GameObject(emptySprite, Vector(515.0f, 314.0f, 0.0f), 0.0f, 0.5f, white, NONE);
	gameObject.push_back(topRightBoard);

	GameObject midLeftBoard = GameObject(emptySprite, Vector(285.0f, 200.0f, 0.0f), 0.0f, 0.5f, white, NONE);
	gameObject.push_back(midLeftBoard);

	GameObject midMidBoard = GameObject(emptySprite, Vector(400.0f, 200.0f, 0.0f), 0.0f, 0.5f, white, NONE);
	gameObject.push_back(midMidBoard);

	GameObject midRightBoard = GameObject(emptySprite, Vector(515.0f, 200.0f, 0.0f), 0.0f, 0.5f, white, NONE);
	gameObject.push_back(midRightBoard);

	GameObject botLeftBoard = GameObject(emptySprite, Vector(285.0f, 84.0f, 0.0f), 0.0f, 0.5f, white, NONE);
	gameObject.push_back(botLeftBoard);

	GameObject botMidBoard = GameObject(emptySprite, Vector(400.0f, 84.0f, 0.0f), 0.0f, 0.5f, white, NONE);
	gameObject.push_back(botMidBoard);

	GameObject botRightBoard = GameObject(emptySprite, Vector(515.0f, 84.0f, 0.0f), 0.0f, 0.5f, white, NONE);
	gameObject.push_back(botRightBoard);


	//===========================================================================================================

	GameObject gameLogo = GameObject(logoSprite, Vector(400.0f, 520.0f, 0.0f), 0.0f, 0.4f, white, NONE);
	gameObject.push_back(gameLogo);

	GameObject restartButton = GameObject(restartSprite, Vector(690.0f, 310.0f, 0.0f), 0.0f, 0.5f, white, NONE);
	gameObject.push_back(restartButton);

	GameObject undoButton = GameObject(undoSprite, Vector(107.0f, 310.0f, 0.0f), 0.0f, 0.5f, white, NONE);
	gameObject.push_back(undoButton);

	GameObject situationSign = GameObject(waitingSprite, Vector(400.0f, 420.0f, 0.0f), 0.0f, 0.5f, white, NONE);
	gameObject.push_back(situationSign);

	//===========================================================================================================
	// initialize slotPlaced = 0 by clear board
	ClearBoard();
	
	previousSlotPlaced[0] = 0;
	previousSlotPlaced[1] = 0;
}

TicTacToe::~TicTacToe()
{
	delete logoSprite;
	delete boardSprite;
	delete firstPlayerSprite;
	delete secondPlayerSprite;
	delete firstPlayerWinSprite;
	delete secondPlayerWinSprite;
	delete emptySprite;
	delete restartSprite;
	delete undoSprite;
	delete yourTurnSprite;
	delete othersTurnSprite;
	delete waitingSprite;
	delete youWinSprite;
	delete youLoseSprite;
	delete tieSprite;
}

void TicTacToe::ClearBoard()
{
	for (int i=0; i<9; ++i)
	{
		slotPlaced[i] = 0;
		previousSlotPlaced[0] = 0;
		previousSlotPlaced[1] = 0;
		// board slots start with 1
		gameObject[i + 1].SetSprite(emptySprite);
	}

}

void TicTacToe::CheckRestartGame()
{
	double xPos, yPos;
	xPos = MyPhoton::getInstance().GetMousePosition().mVal[0];
	yPos = MyPhoton::getInstance().GetMousePosition().mVal[1];

	// check mouse position to identify which action
	static int action = -1;

	action = IdentifyAction(xPos, yPos);

	// if it is occupied, return/quit this function
	if (action != 0)
	{
		//MyPhoton::getInstance().SetExecuteAction(false);
		return;
	}


	if (MyPhoton::getInstance().CheckRestartExecution())
	{
		MyPhoton::getInstance().SetRestartExecuteAction(false);

		MyPhoton::getInstance().SetExecuteAction(true);

		// else update own data 
		UpdateGame(action, false);

		// if everything is fine, send data
		// then send data based on action
		MyPhoton::getInstance().SetDataAndSend(action);

	}
	action = -1;
}

void TicTacToe::CheckInputAndSend()
{
	double xPos, yPos;
	xPos = MyPhoton::getInstance().GetMousePosition().mVal[0];
	yPos = MyPhoton::getInstance().GetMousePosition().mVal[1];

	// check mouse position to identify which action
	int action = IdentifyAction(xPos, yPos);

	// if it is occupied, return/quit this function
	if (action == -1)
	{
		//MyPhoton::getInstance().SetExecuteAction(false);
		return;
	}

	// else update own data 
	UpdateGame(action, false);

	// if everything is fine, send data
	// then send data based on action
	if (action != -1)
	{
		MyPhoton::getInstance().SetDataAndSend(action);

		if (action != 0 && action != 10)
		{
			// change sign
			gameObject[13].SetSprite(othersTurnSprite);

			// check end condition
			CheckEndCondition();
		}
	}
}

void TicTacToe::UpdateGame(int &action, bool isReceivedData)
{
	// place at slot
	if (action >= 1 && action <= 9)
	{
		slotPlaced[action - 1] = true;
		if (!isReceivedData)
		{
			if (MyPhoton::getInstance().GetFirstPlayerCheck())
			{
				gameObject[action].SetSprite(firstPlayerSprite);
			}
			else
			{
				gameObject[action].SetSprite(secondPlayerSprite);
			}

			// own input
			previousSlotPlaced[0] = action;
		}
		else
		{
			if (MyPhoton::getInstance().GetFirstPlayerCheck())
			{
				gameObject[action].SetSprite(secondPlayerSprite);
			}
			else
			{
				gameObject[action].SetSprite(firstPlayerSprite);
			}

			// other input
			previousSlotPlaced[1] = action;
		}
	}
	else if(action == 0) // restart by clearing board
	{
		ClearBoard();

		if (MyPhoton::getInstance().GetFirstPlayerCheck())
		{
			MyPhoton::getInstance().SetFirstPlayer(false);
			MyPhoton::getInstance().SetFirstTurn(false);
			MyPhoton::getInstance().SetCurrentState(OTHERS_TURN);
		}
		else
		{
			MyPhoton::getInstance().SetFirstPlayer(true);
			MyPhoton::getInstance().SetFirstTurn(true);
			MyPhoton::getInstance().SetCurrentState(YOUR_TURN);
		}
	}
	else if (action == 10) // undo
	{
		if (MyPhoton::getInstance().GetCurrentState() != END)
		{
			if (previousSlotPlaced[0] != 0 && previousSlotPlaced[1] != 0)
			{
				gameObject[previousSlotPlaced[0]].SetSprite(emptySprite);
				gameObject[previousSlotPlaced[1]].SetSprite(emptySprite);

				slotPlaced[previousSlotPlaced[0]-1] = false;
				slotPlaced[previousSlotPlaced[1]-1] = false;

				previousSlotPlaced[0] = 0;
				previousSlotPlaced[1] = 0;
			}
			else
			{
				MyPhoton::getInstance().SetExecuteAction(false);
				action = -1;
			}
		}
	}
}

int TicTacToe::IdentifyAction(double xPos, double yPos)
{
	// top = x, 314
	// mid = 400, 200
	// bot = x, 84
	// left = 285, y
	// right = 515, y
	// with 0.5 scale

	int action = 0;

	// start with top
	if (yPos >= 236 && yPos <= 336 && xPos >= 234 && xPos <= 334) // left
	{
		action = 1;
	}
	else if(yPos >= 236 && yPos <= 336 && xPos >= 350 && xPos <= 450) //mid
	{
		action = 2;
	}
	else if (yPos >= 236 && yPos <= 336 && xPos >= 465 && xPos <= 565) // right
	{
		action = 3;
	}// mid
	else if (yPos >= 350 && yPos <= 450 && xPos >= 234 && xPos <= 334) // left
	{
		action = 4;
	}
	else if (yPos >= 350 && yPos <= 450 && xPos >= 350 && xPos <= 450) //mid
	{
		action = 5;
	}
	else if (yPos >= 350 && yPos <= 450 && xPos >= 465 && xPos <= 565) // right
	{
		action = 6;
	}// bot
	else if (yPos >= 465 && yPos <= 565 && xPos >= 234 && xPos <= 334) // left
	{
		action = 7;
	}
	else if (yPos >= 465 && yPos <= 565 && xPos >= 350 && xPos <= 450) //mid
	{
		action = 8;
	}
	else if (yPos >= 465 && yPos <= 565 && xPos >= 465 && xPos <= 565) // right
	{
		action = 9;
	}
	else if (yPos >= 244 && yPos <= 334 && xPos >= 600 && xPos <= 780) // restart
	{
		action = 0;
	}
	else if (yPos >= 244 && yPos <= 334 && xPos >= 15 && xPos <= 195) // undo
	{
		action = 10;
	}
	else // nothing done 
	{
		action = -1;
	}

	// check if the action is valid (e.g. slot is not occupied)
	if (action >= 1 && action <= 9 && slotPlaced[action - 1] == true)
	{
		return -1;
	}

	return action;
}

void TicTacToe::UpdateSign()
{
	if (MyPhoton::getInstance().GetCurrentState() == YOUR_TURN)
	{
		gameObject[13].SetSprite(yourTurnSprite);
	}
	else if(MyPhoton::getInstance().GetCurrentState() == OTHERS_TURN)
	{
		gameObject[13].SetSprite(othersTurnSprite);
	}
	else if (MyPhoton::getInstance().GetCurrentState() == END)
	{
		if (gameObject[13].GetSprite() != tieSprite)
		{
			if (youWin)
			{
				gameObject[13].SetSprite(youWinSprite);
			}
			else
			{
				gameObject[13].SetSprite(youLoseSprite);
			}
		}
	}
}

void TicTacToe::CheckEndCondition()
{
	// check in send and receive
	// topRow, midRow, botRow, leftCol, midCol, rightCol, leftDiagonal, rightDiagonal

	if (gameObject[1].GetSprite() == gameObject[2].GetSprite() && gameObject[1].GetSprite() == gameObject[3].GetSprite() && gameObject[1].GetSprite() != emptySprite) // top row
	{
		if (gameObject[1].GetSprite() == firstPlayerSprite && MyPhoton::getInstance().GetFirstPlayerCheck())
		{
			youWin = true;

			gameObject[1].SetSprite(firstPlayerWinSprite);
			gameObject[2].SetSprite(firstPlayerWinSprite);
			gameObject[3].SetSprite(firstPlayerWinSprite);
		}
		else if (gameObject[1].GetSprite() == secondPlayerSprite && !MyPhoton::getInstance().GetFirstPlayerCheck())
		{
			youWin = true;

			gameObject[1].SetSprite(secondPlayerWinSprite);
			gameObject[2].SetSprite(secondPlayerWinSprite);
			gameObject[3].SetSprite(secondPlayerWinSprite);
		}
		else
		{
			youWin = false;
		}

		MyPhoton::getInstance().SetCurrentState(END);
	}
	else if (gameObject[4].GetSprite() == gameObject[5].GetSprite() && gameObject[4].GetSprite() == gameObject[6].GetSprite() && gameObject[4].GetSprite() != emptySprite) // mid row
	{
		if (gameObject[4].GetSprite() == firstPlayerSprite && MyPhoton::getInstance().GetFirstPlayerCheck())
		{
			youWin = true;

			gameObject[4].SetSprite(firstPlayerWinSprite);
			gameObject[5].SetSprite(firstPlayerWinSprite);
			gameObject[6].SetSprite(firstPlayerWinSprite);
		}
		else if (gameObject[4].GetSprite() == secondPlayerSprite && !MyPhoton::getInstance().GetFirstPlayerCheck())
		{
			youWin = true;

			gameObject[4].SetSprite(secondPlayerWinSprite);
			gameObject[5].SetSprite(secondPlayerWinSprite);
			gameObject[6].SetSprite(secondPlayerWinSprite);
		}
		else
		{
			youWin = false;
		}

		MyPhoton::getInstance().SetCurrentState(END);
	}
	else if (gameObject[7].GetSprite() == gameObject[8].GetSprite() && gameObject[7].GetSprite() == gameObject[9].GetSprite() && gameObject[7].GetSprite() != emptySprite) // bot row
	{
		if (gameObject[7].GetSprite() == firstPlayerSprite && MyPhoton::getInstance().GetFirstPlayerCheck())
		{
			youWin = true;

			gameObject[7].SetSprite(firstPlayerWinSprite);
			gameObject[8].SetSprite(firstPlayerWinSprite);
			gameObject[9].SetSprite(firstPlayerWinSprite);
		}
		else if (gameObject[7].GetSprite() == secondPlayerSprite && !MyPhoton::getInstance().GetFirstPlayerCheck())
		{
			youWin = true;

			gameObject[7].SetSprite(secondPlayerWinSprite);
			gameObject[8].SetSprite(secondPlayerWinSprite);
			gameObject[9].SetSprite(secondPlayerWinSprite);
		}
		else
		{
			youWin = false;
		}

		MyPhoton::getInstance().SetCurrentState(END);
	}
	else if (gameObject[1].GetSprite() == gameObject[4].GetSprite() && gameObject[1].GetSprite() == gameObject[7].GetSprite() && gameObject[1].GetSprite() != emptySprite) // left col
	{
		if (gameObject[1].GetSprite() == firstPlayerSprite && MyPhoton::getInstance().GetFirstPlayerCheck())
		{
			youWin = true;

			gameObject[1].SetSprite(firstPlayerWinSprite);
			gameObject[4].SetSprite(firstPlayerWinSprite);
			gameObject[7].SetSprite(firstPlayerWinSprite);
		}
		else if (gameObject[1].GetSprite() == secondPlayerSprite && !MyPhoton::getInstance().GetFirstPlayerCheck())
		{
			youWin = true;

			gameObject[1].SetSprite(secondPlayerWinSprite);
			gameObject[4].SetSprite(secondPlayerWinSprite);
			gameObject[7].SetSprite(secondPlayerWinSprite);
		}
		else
		{
			youWin = false;
		}

		MyPhoton::getInstance().SetCurrentState(END);
	}
	else if (gameObject[2].GetSprite() == gameObject[5].GetSprite() && gameObject[2].GetSprite() == gameObject[8].GetSprite() && gameObject[2].GetSprite() != emptySprite) // mid col
	{
		if (gameObject[2].GetSprite() == firstPlayerSprite && MyPhoton::getInstance().GetFirstPlayerCheck())
		{
			youWin = true;

			gameObject[2].SetSprite(firstPlayerWinSprite);
			gameObject[5].SetSprite(firstPlayerWinSprite);
			gameObject[8].SetSprite(firstPlayerWinSprite);
		}
		else if (gameObject[2].GetSprite() == secondPlayerSprite && !MyPhoton::getInstance().GetFirstPlayerCheck())
		{
			youWin = true;

			gameObject[8].SetSprite(secondPlayerWinSprite);
			gameObject[5].SetSprite(secondPlayerWinSprite);
			gameObject[2].SetSprite(secondPlayerWinSprite);
		}
		else
		{
			youWin = false;
		}

		MyPhoton::getInstance().SetCurrentState(END);
	}
	else if (gameObject[3].GetSprite() == gameObject[6].GetSprite() && gameObject[3].GetSprite() == gameObject[9].GetSprite() && gameObject[3].GetSprite() != emptySprite) // right col
	{
		if (gameObject[3].GetSprite() == firstPlayerSprite && MyPhoton::getInstance().GetFirstPlayerCheck())
		{
			youWin = true;

			gameObject[3].SetSprite(firstPlayerWinSprite);
			gameObject[6].SetSprite(firstPlayerWinSprite);
			gameObject[9].SetSprite(firstPlayerWinSprite);
		}
		else if (gameObject[3].GetSprite() == secondPlayerSprite && !MyPhoton::getInstance().GetFirstPlayerCheck())
		{
			youWin = true;

			gameObject[3].SetSprite(secondPlayerWinSprite);
			gameObject[6].SetSprite(secondPlayerWinSprite);
			gameObject[9].SetSprite(secondPlayerWinSprite);
		}
		else
		{
			youWin = false;
		}

		MyPhoton::getInstance().SetCurrentState(END);
	}
	else if (gameObject[1].GetSprite() == gameObject[5].GetSprite() && gameObject[1].GetSprite() == gameObject[9].GetSprite() && gameObject[1].GetSprite() != emptySprite) // left diagonal
	{
		if (gameObject[1].GetSprite() == firstPlayerSprite && MyPhoton::getInstance().GetFirstPlayerCheck())
		{
			youWin = true;

			gameObject[1].SetSprite(firstPlayerWinSprite);
			gameObject[5].SetSprite(firstPlayerWinSprite);
			gameObject[9].SetSprite(firstPlayerWinSprite);
		}
		else if (gameObject[1].GetSprite() == secondPlayerSprite && !MyPhoton::getInstance().GetFirstPlayerCheck())
		{
			youWin = true;

			gameObject[1].SetSprite(secondPlayerWinSprite);
			gameObject[5].SetSprite(secondPlayerWinSprite);
			gameObject[9].SetSprite(secondPlayerWinSprite);
		}
		else
		{
			youWin = false;
		}

		MyPhoton::getInstance().SetCurrentState(END);
	}
	else if (gameObject[3].GetSprite() == gameObject[5].GetSprite() && gameObject[3].GetSprite() == gameObject[7].GetSprite() && gameObject[3].GetSprite() != emptySprite) // right diagonal
	{
		if (gameObject[3].GetSprite() == firstPlayerSprite && MyPhoton::getInstance().GetFirstPlayerCheck())
		{
			youWin = true;

			gameObject[3].SetSprite(firstPlayerWinSprite);
			gameObject[5].SetSprite(firstPlayerWinSprite);
			gameObject[7].SetSprite(firstPlayerWinSprite);
		}
		else if (gameObject[3].GetSprite() == secondPlayerSprite && !MyPhoton::getInstance().GetFirstPlayerCheck())
		{
			youWin = true;

			gameObject[3].SetSprite(secondPlayerWinSprite);
			gameObject[5].SetSprite(secondPlayerWinSprite);
			gameObject[7].SetSprite(secondPlayerWinSprite);
		}
		else
		{
			youWin = false;
		}

		MyPhoton::getInstance().SetCurrentState(END);
	}
	else
	{
		for (int i=0; i<9; ++i)
		{
			if (slotPlaced[i] == false)
			{
				break;
			}
			else
			{
				if (i == 8)
				{
					gameObject[13].SetSprite(tieSprite);

					MyPhoton::getInstance().SetCurrentState(END);
				}
			}
		}

		youWin = false;
	}
}

void TicTacToe::UpdateWithReceivedData()
{
	if (MyPhoton::getInstance().CheckReceivedData())
	{
		int action = MyPhoton::getInstance().UnpackReceivedData();

		// update
		UpdateGame(action, true);

		// turn off received data
		MyPhoton::getInstance().DoneUpdateReceivedData();

		if (action != 0 && action != 10)
		{
			// change sign
			gameObject[13].SetSprite(yourTurnSprite);

			// check end condition
			CheckEndCondition();
		}
	}
	else if (MyPhoton::getInstance().CheckWhoseTurn())
	{
		MyPhoton::getInstance().SetCheckWhoseTurn(false);

		int num = MyPhoton::getInstance().GetReceivedTurnNum();

		if (MyPhoton::getInstance().GetTurnNum() > num)
		{
			std::cout << "Your random number : " << num << std::endl;
			std::cout << "Other's random number : " << MyPhoton::getInstance().GetTurnNum() << std::endl;
			std::cout << "Your number is smaller! You are the Second Player!" << std::endl;
			MyPhoton::getInstance().SetFirstPlayer(false);
			MyPhoton::getInstance().InitializeFirstMove(0);
			MyPhoton::getInstance().SetCurrentState(OTHERS_TURN);
			
		}
		else if(MyPhoton::getInstance().GetTurnNum() < num)
		{
			std::cout << "Your random number : " << num << std::endl;
			std::cout << "Other's random number : " << MyPhoton::getInstance().GetTurnNum() << std::endl;
			std::cout << "Your number is bigger! You are the First Player!" << std::endl;
			MyPhoton::getInstance().SetFirstPlayer(true);
			MyPhoton::getInstance().InitializeFirstMove(1);

			MyPhoton::getInstance().SetCurrentState(YOUR_TURN);
		}
		else if (MyPhoton::getInstance().GetTurnNum() == num)
		{
			MyPhoton::getInstance().SetCheckWhoseTurn(true);

			int temp = rand()% 100;
			MyPhoton::getInstance().SetTurnNumToSend(temp);
		}

	}
}

void TicTacToe::Start()
{
}

void TicTacToe::Update(double deltaTime)
{
	MyPhoton::getInstance().run();

	UpdateWithReceivedData();

	if (MyPhoton::getInstance().CheckIsMyTurn() && MyPhoton::getInstance().CheckExecution())
	{
		CheckInputAndSend();
	}

	UpdateSign();

	CheckRestartGame();
}

void TicTacToe::Draw()
{
	for (int i = 0; i < gameObject.size(); ++i)
	{
		gameObject[i].Draw();
	}
}
