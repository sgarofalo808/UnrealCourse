#include "FBullCowGame.h"

constexpr int32 MAX_TRIES = 3;
const FString HIDDEN_WORD = "slide";

FBullCowGame::FBullCowGame()
{
	Reset();
}

void FBullCowGame::Reset()
{
	MyCurrentTry = 1;
}

int32 FBullCowGame::GetMaxTries() const
{
	return MAX_TRIES;
}

int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

bool FBullCowGame::IsGameWon(BullCowCount counter) const
{	
	return (counter.Bulls == HIDDEN_WORD.length());
}

bool FBullCowGame::CheckGuessValidity(FString Guess)
{
	return (Guess.length() == HIDDEN_WORD.length());
}

BullCowCount FBullCowGame::SubmitGuess(FString Guess)
{
	MyCurrentTry++;

	BullCowCount counter;

	for (int32 i = 0; i < HIDDEN_WORD.length(); i++) {

		if (Guess[i] == HIDDEN_WORD[i]) {
			counter.Bulls++;
		}

		for (int32 j = 0; j < HIDDEN_WORD.length(); j++) {

			if (Guess[i] == HIDDEN_WORD[j]) {
				counter.Cows++;
				break;
			}

		}
	}

	return counter;
}
