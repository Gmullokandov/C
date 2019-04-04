#include "FBullCowGame.h"


using namespace std;
using FString = string;
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 10;
	const FString HIDDEN_WORD = "planet";
	MyCurrentTry = 1;
	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	return;
}

bool FBullCowGame::IsGameWon() const
{
	return false;
}

EWordStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (false)
	{
		return EWordStatus::Not_Isogram;
	}
	else if (false)
	{
		return EWordStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EWordStatus::Wrong_Length;
	}
	else
	{
		return EWordStatus::OKAY;
	}
}

//receives a VALID guess, increments turns and returns count
FBullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
	//increment the turn number
	MyCurrentTry++;
	//setup a return variable
	FBullCowCount BullCowCount;
	//loop through all letters in the guess
	int32 HiddenWordLength = MyHiddenWord.length();
	for (int32 i = 0; i < HiddenWordLength; i++)
	{
		for (int32 j = 0; j < HiddenWordLength; j++)
		{
			if (Guess[j] == MyHiddenWord[i])
			{
				if (i == j)
				{
					BullCowCount.Bulls++;
				}
				else
				{
					BullCowCount.Cows++;
				}
			}
		}
	}
	return BullCowCount;
}
