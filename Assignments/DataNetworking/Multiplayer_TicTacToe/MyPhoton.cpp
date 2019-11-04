#include "MyPhoton.h"
#include <iostream>
#include <ctime>

static const ExitGames::Common::JString appId = L"6938dee7-7680-4b00-88e3-d91a088cb81e"; // set your app id here
static const ExitGames::Common::JString appVersion = L"1.0";
static const ExitGames::Common::JString PLAYER_NAME = L"Windows";

//LoadBalancing::Listener& listener, const Common::JString& applicationID, 
//const Common::JString& appVersion, nByte connectionProtocol=Photon::ConnectionProtocol::DEFAULT, bool autoLobbyStats=false, nByte regionSelectionMode=RegionSelectionMode::DEFAULT

// functions
MyPhoton::MyPhoton() : mLoadBalancingClient(*this, appId, appVersion, ExitGames::Photon::ConnectionProtocol::TCP, false, ExitGames::LoadBalancing::RegionSelectionMode::SELECT)
{
}

void MyPhoton::connect(void)
{
	std::wcout<<"Connecting..."<<std::endl;
	mLoadBalancingClient.connect(ExitGames::LoadBalancing::AuthenticationValues(), PLAYER_NAME);
}

void MyPhoton::disconnect(void)
{
	mLoadBalancingClient.disconnect();
}

void MyPhoton::sendMyData(void)
{
	mLoadBalancingClient.opRaiseEvent(true, dataToSend, 1, 1);
}

void MyPhoton::SetDataAndSend(int action)
{
	if (b_executeAction == true)
	{
		if (action != 0 && action != 10)
		{// change own state to 0 and send 1
			b_isMyTurn = 0;

			// last bit will be 1, means it is other player's turn 
			unsigned char temp = 0;
			// insert action first, then last bit for state
			temp = action;
			// shift 1 bits for state slot
			temp = temp << 1;
			// add in state -> 1
			temp += 1;

			// set data to send
			dataToSend = &temp;

			// only send once, since it is turn-based
			b_executeAction = false;

			// other's turn
			currentState = OTHERS_TURN;

			sendMyData();
			// after sent data, change to other player's turn
			b_isMyTurn = false;
		}
		else // dont change turn
		{
			// last bit will be 0, means it is your turn 
			unsigned char temp = 0;
			// insert action first, then last bit for state
			temp = action;
			// shift 1 bits for state slot
			temp = temp << 1;
			// add in state -> 1
			temp += 0;

			// set data to send
			dataToSend = &temp;

			if (action == 0)
			{
				// only send once, since it is turn-based
				b_executeAction = false;
			}

			sendMyData();
		}
	}
}

int MyPhoton::UnpackReceivedData()
{
	// set state to my turn, then return action
	unsigned char temp = 1;
	temp = *receivedData & temp;
	b_isMyTurn = temp;

	// get action by shifting left 1
	temp = *receivedData >> 1;

	if (temp != 10)
	{
		// your turn
		currentState = YOUR_TURN;
	}
	
	if (temp == 0)
	{
		currentState = OTHERS_TURN;
		b_isMyTurn = false;
		b_executeAction = false;
	}

	return temp;
}

void MyPhoton::SetExecuteAction(bool value)
{
	b_executeAction = value;
}

void MyPhoton::SetMousePosition(double x, double y)
{
	mouseXpos = x;
	mouseYpos = y;

	if (b_isMyTurn)
	{
		b_executeAction = true;
	}

	if (mouseYpos >= 244 && mouseYpos <= 334 && mouseXpos >= 600 && mouseXpos <= 780)
	{
		b_restartExecuteAction = true;
	}
	else
	{
		b_restartExecuteAction = false;
	}
}

Vector MyPhoton::GetMousePosition()
{
	Vector temp(mouseXpos, mouseYpos, 0.0f);
	return temp;
}

void MyPhoton::InitializeFirstMove(int value)
{
	b_isMyTurn = value;
}

bool MyPhoton::GetFirstPlayerCheck()
{
	return b_isFirstPlayer;
}

bool MyPhoton::CheckIsMyTurn()
{
	return b_isMyTurn;
}

bool MyPhoton::CheckExecution()
{
	return b_executeAction;
}

bool MyPhoton::CheckRestartExecution()
{
	return b_restartExecuteAction;
}

void MyPhoton::SetRestartExecuteAction(bool value)
{
	b_restartExecuteAction = value;
}

void MyPhoton::SetFirstPlayer(bool isFirstPlayer)
{
	b_isFirstPlayer = isFirstPlayer;
}

void MyPhoton::SetFirstTurn(bool isFirstTurn)
{
	b_isMyTurn = isFirstTurn;
}

State MyPhoton::GetCurrentState()
{
	return currentState;
}

void MyPhoton::SetCurrentState(State s)
{
	currentState = s;
}

bool MyPhoton::CheckReceivedData()
{
	return b_receivedData;
}

void MyPhoton::DoneUpdateReceivedData()
{
	b_receivedData = false;
}

bool MyPhoton::CheckWhoseTurn()
{
	return b_checkWhoseTurn;
}

void MyPhoton::ReceiveWhoseTurnData()
{
	unsigned char temp = 0;
	temp = *receivedData;
	receivedTurnNum = (int)temp;

}

int MyPhoton::GetTurnNum()
{
	return turnNum;
}

void MyPhoton::SetCheckWhoseTurn(bool value)
{
	b_checkWhoseTurn = value;
}

void MyPhoton::SetTurnNumToSend(int value)
{
	turnNum = value;
	unsigned char temp = turnNum;
	dataToSend = &temp;

	sendMyData();
}

int MyPhoton::GetReceivedTurnNum()
{
	return receivedTurnNum;
}

void MyPhoton::run(void)
{
	mLoadBalancingClient.service();
}

// protocol implementations

void MyPhoton::debugReturn(int debugLevel, const ExitGames::Common::JString& string)
{
}

void MyPhoton::connectionErrorReturn(int errorCode)
{
	std::wcout<<"connectionErrorReturn : "<<errorCode<<std::endl;
}

void MyPhoton::clientErrorReturn(int errorCode)
{
	std::wcout<<"clientErrorReturn : "<<errorCode<<std::endl;
}

void MyPhoton::warningReturn(int warningCode)
{
	std::wcout<<"warningReturn : "<<warningCode<<std::endl;
}

void MyPhoton::serverErrorReturn(int errorCode)
{
	std::wcout<<"serverErrorReturn : "<<errorCode<<std::endl;
}

void MyPhoton::joinRoomEventAction(int playerNr, const ExitGames::Common::JVector<int>& playernrs, const ExitGames::LoadBalancing::Player& player)
{
	if (playernrs.getSize() == 1)
	{
		std::wcout << "joinRoomEventAction" << std::endl;
		std::wcout << "Player Joined!" << std::endl;
	}
	else if(playernrs.getSize() == 2)
	{
		std::wcout << "joinRoomEventAction" << std::endl;
		std::wcout << "Player Joined!" << std::endl;

		/*
		if (b_isFirstPlayer)
		{
			// first player
			InitializeFirstMove(1);

			// player 1 state
			currentState = YOUR_TURN;
		}
		else
		{
			// second player
			InitializeFirstMove(0);

			// player 2 state
			currentState = OTHERS_TURN;
		}
		*/
		if (currentState == WAITING)
		{
			int turn = rand() % 100;
			SetTurnNumToSend(turn);
		}
	}
	
	/*
	if (playernrs.getSize() >= 2)
		sendMyData();
	*/

	// test to get button/object position
	//InitializeFirstMove(1);
}

void MyPhoton::leaveRoomEventAction(int playerNr, bool isInactive)
{
	std::wcout<<"leaveRoomEventAction"<<std::endl;
}

void MyPhoton::customEventAction(int playerNr, nByte eventCode, const ExitGames::Common::Object& eventContent)
{
	receivedData = ExitGames::Common::ValueObject<unsigned char*>(eventContent).getDataCopy();

	if (currentState == WAITING)
	{
		if (receivedData)
		{
			// ====================================================
			ReceiveWhoseTurnData();
			b_checkWhoseTurn = true;

			return;
		}
	}

	if (receivedData)
	{
		std::cout << "received : " << receivedData << std::endl;
		
		// ====================================================
		b_receivedData = true;
	}
	else
		std::cout << "invalid data" << std::endl;
}

void MyPhoton::connectReturn(int errorCode, const ExitGames::Common::JString& errorString, const ExitGames::Common::JString& cluster)
{
	if(errorCode)
		std::wcout<<"Failed to connect : "<<errorString.cstr()<<std::endl;
	else
	{
		std::wcout<<"Connected to Photon Server."<<std::endl;
		
		std::wcout<<"Trying to join a random room..."<<std::endl;
		mLoadBalancingClient.opJoinRandomRoom();
	}
}

void MyPhoton::disconnectReturn(void)
{
	std::wcout<<"disconnected"<<std::endl;
}

void MyPhoton::createRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& /*gameProperties*/, const ExitGames::Common::Hashtable& /*playerProperties*/, int errorCode, const ExitGames::Common::JString& errorString)
{
	std::wcout<<"createRoomReturn"<<std::endl;
}

void MyPhoton::joinOrCreateRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& /*gameProperties*/, const ExitGames::Common::Hashtable& /*playerProperties*/, int errorCode, const ExitGames::Common::JString& errorString)
{
	std::wcout<<"joinOrCreateRoomReturn"<<std::endl;
}

void MyPhoton::joinRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& /*gameProperties*/, const ExitGames::Common::Hashtable& /*playerProperties*/, int errorCode, const ExitGames::Common::JString& errorString)
{
	std::wcout<<"joinRoomReturn"<<std::endl;
}

void MyPhoton::joinRandomRoomReturn(int localPlayerNr, const ExitGames::Common::Hashtable& /*gameProperties*/, const ExitGames::Common::Hashtable& /*playerProperties*/, int errorCode, const ExitGames::Common::JString& errorString)
{
	std::wcout<<"joinRandomRoomReturn"<<std::endl;

	if(errorCode)
	{
		std::wcout<<"Failed to join a random room : "<<errorCode<<", "<<errorString.cstr()<<std::endl;

		if(errorCode == 32760) //no match found error code
		{
			std::wcout<<"Creating a room..."<<std::endl;
			//try to create a room and wait;
			ExitGames::Common::JString name;
			name += GETTIMEMS();
			mLoadBalancingClient.opCreateRoom(name, ExitGames::LoadBalancing::RoomOptions().setMaxPlayers(2));

			/*
			// first player
			std::wcout << "You Are First Player!" << std::endl;
			b_isFirstPlayer = true;
			*/

			// wait for other
			currentState = WAITING;
		}

		return;
	}
/*
	// Second player
	std::wcout << "You Are Second Player!" << std::endl;
	b_isFirstPlayer = false;
*/

	// wait for other
	currentState = WAITING;
}

void MyPhoton::leaveRoomReturn(int errorCode, const ExitGames::Common::JString& errorString)
{
	std::wcout<<"leaveRoomReturn"<<std::endl;
}

void MyPhoton::joinLobbyReturn(void)
{
	std::wcout<<"joinLobbyReturn"<<std::endl;
}

void MyPhoton::leaveLobbyReturn(void)
{
	std::wcout<<"leaveLobbyReturn"<<std::endl;
}

void MyPhoton::onLobbyStatsResponse(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStatsResponse>& lobbyStats)
{
	std::wcout<<"onLobbyStatsResponse"<<std::endl;
}

void MyPhoton::onLobbyStatsUpdate(const ExitGames::Common::JVector<ExitGames::LoadBalancing::LobbyStatsResponse>& lobbyStats)
{
	std::wcout<<"onLobbyStatsUpdate"<<std::endl;
}

void MyPhoton::onAvailableRegions(const ExitGames::Common::JVector<ExitGames::Common::JString>& availableRegions, const ExitGames::Common::JVector<ExitGames::Common::JString>& availableRegionServers)
{
	//std::wcout<<availableRegions[0]<<std::endl;
	//std::wcout<<availableRegions[1]<<std::endl;
	//mLoadBalancingClient.selectRegion(availableRegions[0]);
	mLoadBalancingClient.selectRegion("eu");
}
