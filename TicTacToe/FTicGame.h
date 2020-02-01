#pragma once
#include <string>
#include <iostream>

using FString = std::string;
using int32 = int;

struct FTicState
{
	int32 PlayerOneGoes = 0;
	int32 PlayerTwoGoes = 0;
	FString GameScreen[3][3] = {" "};
};

enum class EGameComplete
{
	In_Play,
	PlayerOneWon,
	PlayerTwoWon,
	Tied
};

enum class EInputValidity
{
	Valid,
	Character_Already_Used,
	Invalid_Character
};

class FTicGame
{
public: // could be better to leave all as const and then change accordingly
	FTicGame();

	int32 GetPlayerNumber() const;
	//FTicState GetGameState() const; might not be needed
	EGameComplete IsGameComplete(FTicState, int32) const;
	void Reset();
	EInputValidity IsValidInput(FString) const; // input in form 'NUMBER X/O'
	void ShowScreen(FTicState) const;
	void SwapTurn();
	FTicState SendInput(FTicState, int32);

private:
	int32 PlayerNumber;
};