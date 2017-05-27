#pragma once

#include <string>

using FString = std::string;
using int32 = int;

struct BullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessValidity {
	OK,
	WRONG_LENGTH,
	NOT_AN_ISOGRAM
};

class FBullCowGame {

public:
	FBullCowGame();
	void Reset();
	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	bool IsGameWon(BullCowCount) const;
	EGuessValidity CheckGuessValidity(FString);
	BullCowCount SubmitGuess(FString);

private:
	int32 MyCurrentTry;
	FString MyCurrentWord;

	bool IsIsogram(FString) const;

};