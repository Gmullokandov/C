#pragma once
#include <string>

using namespace std;
using FString = string;
using int32 = int;

struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EWordStatus
{
	Invalid,
	OKAY,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame 
{
public:
	FBullCowGame();
	void Reset(); // TODO make a more rich return value
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EWordStatus CheckGuessValidity(FString) const; // TODO make a more rich return value

	// counts bulls and cows, and increases turn # assuming valid guess
	FBullCowCount SubmitGuess(FString);

private:
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
};