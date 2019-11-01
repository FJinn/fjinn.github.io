#ifndef TICTACTOE_H
#define TICTACTOE_H

#include "Sprite.h"
#include "GameObject.h"
#include <vector>

#include "MyPhoton.h"

class TicTacToe
{
private:
	std::vector<GameObject> gameObject;

	Sprite* logoSprite;
	Sprite* boardSprite;
	Sprite* firstPlayerSprite;
	Sprite* secondPlayerSprite;
	Sprite* firstPlayerWinSprite;
	Sprite* secondPlayerWinSprite;
	Sprite* emptySprite;
	Sprite* restartSprite;
	Sprite* undoSprite;
	Sprite* yourTurnSprite;
	Sprite* othersTurnSprite;
	Sprite* waitingSprite;
	Sprite* youWinSprite;
	Sprite* youLoseSprite;
	Sprite* tieSprite;

	bool slotPlaced[9];
	int previousSlotPlaced[2];

	bool youWin;

public:
	TicTacToe();
	~TicTacToe();

	void ClearBoard();

	// just for restart game
	void CheckRestartGame();

	// a function in update to check if data should be sent (set b_executeAction in MyPhoton to true/false)
	void CheckInputAndSend();
	// update own game
	// action 1-9 is to place choice on board
	// 10 = undo, 11 = new Game
	void UpdateGame(int &action, bool isReceivedData);
	// use mouse position to identify action
	int IdentifyAction(double xPos, double yPos);

	void UpdateSign();

	// check if win/lose
	void CheckEndCondition();

	// get received data and update
	void UpdateWithReceivedData();

	void Start();
	void Update(double deltaTime);
	void Draw();

};


#endif // !TICTACTOE
