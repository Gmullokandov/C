#pragma once
#include "FBullCowGame.h"
#include<map>
#define TMap std::map

using namespace std;
using FString = string;
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

//sets the max tries to the length of the word
int32 FBullCowGame::GetMaxTries() const 
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,4},{4,7},{5,10},{6,15},{7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()]; 
}


void FBullCowGame::Reset()
{
	constexpr int32 MAX_TRIES = 5;
	const FString HIDDEN_WORD = "iphone";
	MyCurrentTry = 1;
	MyHiddenWord = HIDDEN_WORD;
	bGameIsWon = false;
	return;
}

EWordStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
	{
		return EWordStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess))
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
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	//loop through all letters in the guess
	int32 WordLength = MyHiddenWord.length();//assuming the same length as guess
	for (int32 i = 0; i < WordLength; i++)
	{
		for (int32 j = 0; j < WordLength; j++)
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
	if (BullCowCount.Bulls == WordLength) 
	{
		bGameIsWon = true;
	}
	else 
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	//treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }
	
	TMap<char, bool> LetterSeen;//setup our map
	for (auto Letter : Word)
	{
		Letter = tolower(Letter); //handle mixed case
		if (LetterSeen[Letter]) // if the letter is in the map
		{
			return false; //we do not have an isogram
		}
		else
		{
			LetterSeen[Letter] = true;
		}
	}
	return true; //for example in cases when /0 is entered
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter))//If not a lowercase letter
		{
			return false;
		}
	}
	return true;
}
