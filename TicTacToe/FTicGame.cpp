#include "FTicGame.h"

FTicGame::FTicGame() { Reset(); }

EGameComplete FTicGame::IsGameComplete(FTicState GameState, int32 LastPlay) const
{
	int32 Row = floor((LastPlay - 1) / 3);
	int32 Col = (LastPlay - 1) % 3;
	// check row
	int RowCount[2] = { 0 };
	for (int i = 0; i < 3; i++)
	{
		if (GetPlayerNumber() == 0 && GameState.GameScreen[Col][i] == "X")
		{
			RowCount[0]++;
		}
		else if (GetPlayerNumber() == 1 && GameState.GameScreen[Col][i] == "O")
		{
			RowCount[1]++;
		}
	}
	// check col
	int ColCount[2] = { 0 };
	for (int i = 0; i < 3; i++)
	{
		if (GetPlayerNumber() == 0 && GameState.GameScreen[i][Row] == "X")
		{
			ColCount[0]++;
		}
		else if (GetPlayerNumber() == 1 && GameState.GameScreen[i][Row] == "O")
		{
			ColCount[1]++;
		}
	}
	// check diagonal
	int DiagCount[2] = { 0 };
	for (int i = 0; i < 3; i++)
	{
		if (GetPlayerNumber() == 0 && GameState.GameScreen[i][i] == "X")
		{
			DiagCount[0]++;
		}
		else if (GetPlayerNumber() == 1 && GameState.GameScreen[i][i] == "O")
		{
			DiagCount[1]++;
		}
	}

	if (RowCount[0] == 3 || ColCount[0] == 3 || DiagCount[0] == 3)
	{
		return EGameComplete::PlayerOneWon;
	}
	else if (RowCount[1] == 3 || ColCount[1] == 3 || DiagCount[1] == 3)
	{
		return EGameComplete::PlayerTwoWon;
	}
	else
	{
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				if (GameState.GameScreen[i][j] == FString(""))
				{
					return EGameComplete::In_Play;
				}
			}
		}
		return EGameComplete::Tied;
	}
	return EGameComplete::In_Play;
} 

void FTicGame::Reset()
{
	constexpr int32 START_PLAYER_NUMBER = 0;
	PlayerNumber = START_PLAYER_NUMBER;
	FTicState NewGameState;
	NewGameState.PlayerOneGoes = 0;
	NewGameState.PlayerTwoGoes = 0;
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			NewGameState.GameScreen[i][j] = " ";
}

EInputValidity FTicGame::IsValidInput(FTicState GameState, FString Input) const
{
	int32 Row = floor((Input - 1) / 3);
	int32 Col = (Input - 1) % 3;

	// Number not in range (is length 1 -> is a number && in range)
	if (Input.length() != 1)
	{
		return EInputValidity::WrongLength;
	}
	else if (!Input.isdigit())
	{
		return EInputValidity::NotNumber;
	}
	else if (std::stoi(Input) < 1 || std::stoi(Input) > 9)
	{
		return EInputValidity::NotNumberInRange;
	}
	// Space already taken
	else if (GameState.GameScreen[Col][Row] != "")
	{
		return EInputValidity::SpaceAlreadyTaken;
	}
	else
	{
		return EInputValidity::Valid;
	}
}

void FTicGame::ShowScreen(FTicState NewGameState) const
{
	std::cout << "\n" << NewGameState.GameScreen[0][0] << " | " << NewGameState.GameScreen[1][0] << " | " << NewGameState.GameScreen[2][0] << "\n";
	std::cout << "---------";
	std::cout << "\n " << NewGameState.GameScreen[0][1] << " | " << NewGameState.GameScreen[1][1] << " | " << NewGameState.GameScreen[2][1] << "\n";
	std::cout << "---------";
	std::cout << "\n " <<NewGameState.GameScreen[0][2] << " | " << NewGameState.GameScreen[1][2] << " | " << NewGameState.GameScreen[2][2] << "\n";
	return;
}

void FTicGame::SwapTurn()
{
	if (PlayerNumber == 0)
	{
		PlayerNumber = 1;
		return;
	}
	else
	{
		PlayerNumber = 0;
		return;
	}
}

FTicState FTicGame::SendInput(FTicState TicState, int32 Input)
{
	int32 Row = floor((Input - 1) / 3);
	int32 Col = (Input - 1) % 3;
	//std::cout << "Row" << Row << " Col" << Col;
	if (GetPlayerNumber() == 0)
	{
		TicState.PlayerOneGoes++;
		TicState.GameScreen[Col][Row] = 'X';
	}
	else
	{
		TicState.PlayerTwoGoes++;
		TicState.GameScreen[Col][Row] = 'O';
	}
	return TicState;
}

int32 FTicGame::GetPlayerNumber() const { return PlayerNumber; }