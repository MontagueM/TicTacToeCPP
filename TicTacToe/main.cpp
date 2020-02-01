#include <string>
#include <iostream>
#include "FTicGame.h"

using FText = std::string;
using int32 = int;

void PlayGame(FTicState);
void PrintIntro();
FString GetInput();
bool WantToPlayAgain();

FTicGame TicGame;

int main()
{
	bool bRepeat = false;
	do
	{
		FTicState EmptyTicState;
		PrintIntro();
		TicGame.ShowScreen(EmptyTicState);
		PlayGame(EmptyTicState);
		bRepeat = WantToPlayAgain();
	} while (bRepeat);

	return 0;
}

void PlayGame(FTicState TicState)
{
	// Show screen to player

	// Ask for input from player 1/2

	//FString Input = std::cout << ""; do not do these lines. Disobeys abstraction. Instead do below
	//std::getline(std::cin, Guess);
	FText Input = GetInput();
	// If input valid
	EInputValidity validity = TicGame.IsValidInput(Input);
	if (validity == EInputValidity::Valid)
	{
		// Submit input
		TicState = TicGame.SendInput(TicState, std::stoi(Input));
		// Show new screen before win chance
		TicGame.ShowScreen(TicState);
		// Check if won
		// abstraction issue here, put into a new fn
		EGameComplete CompletionState = TicGame.IsGameComplete(TicState, std::stoi(Input));
		if (CompletionState == EGameComplete::In_Play)
		{
			// If not, continue PlayGame()
			TicGame.SwapTurn();
			PlayGame(TicState);
		}
		else
		{
			// If so, send back to main.cpp
			if (CompletionState == EGameComplete::PlayerOneWon)
			{
				std::cout << "\nPlayer 1 has won!\n";
			}
			else if (CompletionState == EGameComplete::PlayerTwoWon)
			{
				std::cout << "\nPlayer 2 has won!\n";
			}
			else if (CompletionState == EGameComplete::Tied)
			{
				std::cout << "\nGame has tied!\n";
			}
			return;
		}
	}
	else
	{
		PlayGame(TicState);
	}
}

void PrintIntro()
{
	std::cout << "Welcome to C++ TicTacToe. When in play, the screen will show the current state.\n";
	std::cout << "To play, write the number 1-9 where 1 is top-left and 9 bottom-right.\n";
	return;
}

FString GetInput()
{
	FText Guess = "";
	std::cout << "Enter your play player " << TicGame.GetPlayerNumber() + 1 << ": ";
	std::getline(std::cin, Guess);
	return Guess;
}

bool WantToPlayAgain()
{
	FText PlayAgain = "";
	std::cout << "\n\nWould you like to play again? ";
	std::getline(std::cin, PlayAgain);
	if (tolower(PlayAgain[0]) == 'y')
	{
		return true;
	}
	else
	{
		return false;
	}
}