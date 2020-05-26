#pragma once

#include <LoadBalancing-cpp/inc/Client.h>
#include "Vector.h"

enum State
{
	WAITING,
	YOUR_TURN,
	OTHERS_TURN,
	END,
	IDLE
};

class MyPhoton : private ExitGames::LoadBalancing::Listener
{

public:
	MyPhoton();
	void run(void);
	void connect(void);
	void disconnect(void);

	static MyPhoton& getInstance()
	{
		static MyPhoton instance;
		return instance;
	}

	void sendMyData(void);
	
	// if executeAction = true, it will update and change it back to false
	// last bit is for state (change self to 0, and send 1), then 9 positions, 10 - 15 = other function
	// checking conditions in other function, send data (auto-call sendMyData)
	void SetDataAndSend(int action);

	// set state to my turn, then return action
	int UnpackReceivedData();

	// if the input is correct/proper, set b_executeAction = true, else false
	void SetExecuteAction(bool value);

	// whenever mouseIsPressed, call this function and b_executeAction = true
	// run in TicTacToe function to turn b_executeAction to false (in function before SetDataToSend) if conditions do not meet
	void SetMousePosition(double x, double y);
	Vector GetMousePosition();

	// set first player value = 1 and second player = 0
	void InitializeFirstMove(int value);

	bool GetFirstPlayerCheck();
	bool CheckIsMyTurn();
	bool CheckExecution();
	bool CheckRestartExecution();
	void SetRestartExecuteAction(bool value);

	void SetFirstPlayer(bool isFirstPlayer);
	void SetFirstTurn(bool isFirstTurn);

	State GetCurrentState();
	void SetCurrentState(State s);

	// get receive data and update in TicTacToe
	bool CheckReceivedData();
	// after update, change receive data back to false
	void DoneUpdateReceivedData();

	bool CheckWhoseTurn();
	void ReceiveWhoseTurnData();
	int GetTurnNum();
	void SetCheckWhoseTurn(bool value);
	void SetTurnNumToSend(int value);
	int GetReceivedTurnNum();

private:
	// receive and print out debug out here
	virtual void debugReturn(int debugLevel, const ExitGames::Common::JString& string);

	// implement your error-handling here
	virtual void connectionErrorReturn(int errorCode);
	virtual void clientErrorReturn(int errorCode);
	virtual void warningReturn(int warningCode);
	virtual void serverErrorReturn(int errorCode);

	// events, triggered by certain operations of all players in the same room
	virtual void joinRoomEventAction(int playerNr, const ExitGames::Common::JVector<int>& playernrs, const ExitGames::LoadBalancing::Player& player);
	virtual void leaveRoomEventAction(int playerNr, bool isInactive);
	virtual void customEventAction(int playerNr, nByte eventCode, const ExitGames::Common::Object& eventContent);

	virtual void onLobbyStatsResponse(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStatsResponse>& lobbyStats);
	virtual void onLobbyStatsUpdate(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStatsResponse>& lobbyStats);
	virtual void onAvailableRegions(const ExitGames::Common::JVector<ExitGames::Common::JString>& availableRegions, const ExitGames::Common::JVector<ExitGames::Common::JString>& availableRegionServers);

	// callbacks for operations on PhotonLoadBalancing server
	virtual void connectReturn(int errorCode, const ExitGames::Common::JString& errorString, const ExitGames::Common::JString& cluster);
	virtual void disconnectReturn(void);
	virtual void createRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);
	virtual void joinOrCreateRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);
	virtual void joinRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);
	virtual void joinRandomRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& gameProperties, const ExitGames::Common::Hashtable& playerProperties, int errorCode, const ExitGames::Common::JString& errorString);
	virtual void leaveRoomReturn(int errorCode, const ExitGames::Common::JString& errorString);
	virtual void joinLobbyReturn(void);
	virtual void leaveLobbyReturn(void);

	ExitGames::LoadBalancing::Client mLoadBalancingClient;

	//===========================================================================================================
	// for Tic Tc Toe

	// send one unsigned char
	unsigned char* dataToSend;

	double mouseXpos, mouseYpos;

	// mousePressed and is a correct/proper action
	bool b_executeAction;
	bool b_restartExecuteAction;

	// my turn = 1, other player's turn = 0
	bool b_isMyTurn;

	// am I first player
	bool b_isFirstPlayer;

	// get receive data and update in TicTacToe
	bool b_receivedData;

	// data received
	unsigned char* receivedData;

	// cache current state
	State currentState;

	bool b_checkWhoseTurn;
	int turnNum;
	int receivedTurnNum;
};