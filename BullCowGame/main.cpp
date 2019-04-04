/*
	This is the console executable that makes use of the BullCow class.
	This acts as the view in a MVC pattern, and is responsible for all
	user interaction. For game logic see FBullCowGame class.
*/
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

FBullCowGame BCGame; //instantiate a new game

//The entry point of the game
int main()
{
	do
	{
		PrintIntro();
		PlayGame();
	}
	while(AskToPlayAgain() != 0);
	//TODO add game summary
	cout << endl;
	return 0; //exit the application
}

//introduce the game
void PrintIntro()
{
	cout << "Welcome to Bulls and Cows, a fun word game." << endl;
	cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?" << endl << endl;
	return;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
	//Loop for the number of turns asking for guesses
	//TODO change from for to while loop once we are validating tries
	for (int32 count = 1; count <= MaxTries; count++)
	{
		FText Guess = GetValidGuess();
		//submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);
		cout << "Bulls = " << BullCowCount.Bulls;
		cout << " Cows = " << BullCowCount.Cows;
		cout << endl << endl;
	}
	// TODO summarise game
}

//Loop continuously until the user gets a valid guess
FText GetValidGuess()
{
	EWordStatus Status = EWordStatus::Invalid;
	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();
		FText Guess = "";
		cout << "Try " << CurrentTry << ": Enter your guess: ";
		getline(cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EWordStatus::Wrong_Length:
			cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word." << endl;
			break;
		case EWordStatus::Not_Isogram:
			cout << "Please enter a word without repeating letters." << endl;
			break;
		case EWordStatus::Not_Lowercase:
			cout << "Please enter all lowercase letters" << endl;
			break;
		default:
			return Guess;
		}
		cout << endl;
	} while (Status == EWordStatus::OKAY);
}

bool AskToPlayAgain()
{
	cout << "Do your want to play again? (y/n)";
	FText Response = "";
	getline(cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}