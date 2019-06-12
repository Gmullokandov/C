/*
	This is the console executable that makes use of the BullCow class.
	This acts as the view in a MVC pattern, and is responsible for all
	user interaction. For game logic see FBullCowGame class.
*/
#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

using namespace std;
using FText = string;
using int32 = int;

void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; //instantiate a new game

//The entry point of the game
int main()
{
	bool bPlayAgain = false;
	do
	{
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	}
	while(AskToPlayAgain() != 0);
	cout << endl;
	return 0; //exit the application
}

//introduce the game
void PrintIntro()
{
	cout << "Welcome to Bulls and Cows, a fun word game.\n";
	cout << endl;
	cout << "          }   {         ___ " << endl;
	cout << "          (o o)        (o o) " << endl;
	cout << "   /-------\\ /          \\ /-------\\ " << endl;
	cout << "  / | BULL |O            O| COW  | \\ " << endl;
	cout << " *  |-,--- |              |------|  * " << endl;
	cout << "    ^      ^              ^      ^ " << endl;
	cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?" << endl << endl;
	return;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	//Loop asking for guesses while the game is NOT won
	//and there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess();

		//submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		cout << "Bulls = " << BullCowCount.Bulls;
		cout << " Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
}

//Loop continuously until the user gets a valid guess
FText GetValidGuess()
{
	FText Guess = "";
	EWordStatus Status = EWordStatus::Invalid;
	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();
		cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		cout << ": Enter your guess: ";
		getline(cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EWordStatus::Wrong_Length:
			cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n" << endl;
			break;
		case EWordStatus::Not_Isogram:
			cout << "Please enter a word without repeating letters.\n" << endl;
			break;
		case EWordStatus::Not_Lowercase:
			cout << "Please enter all lowercase letters.\n" << endl;
			break;
		default:
			//assume guess is valid
			break;
		}
	} while (Status != EWordStatus::OKAY);
	return Guess;
}

bool AskToPlayAgain()
{
	cout << "Do your want to play again with the same hidden word? (y/n)";
	FText Response = "";
	getline(cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary() 
{
	if (BCGame.IsGameWon())
	{
		cout << "Well Done - YOU WIN!!!!\n";
	}
	else
	{
		cout << "Better luck next time!\n";
	}
}
