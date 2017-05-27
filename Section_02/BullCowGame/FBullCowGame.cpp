#include "FBullCowGame.h"
#include <map>
#define TMap std::map

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

EGuessValidity FBullCowGame::CheckGuessValidity(FString Guess)
{
	EGuessValidity result = EGuessValidity::OK;

	if (Guess.length() != HIDDEN_WORD.length()) {
		result = EGuessValidity::WRONG_LENGTH;
	}
	else if (!IsIsogram(Guess)) {
		result = EGuessValidity::NOT_AN_ISOGRAM;
	}

	return result;
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

bool FBullCowGame::IsIsogram(FString Word) const
{
	if (Word.length() <= 1) {
		return true;
	}

	bool result = true;
	TMap <char, bool> LetterSeen;

	for (char Letter : Word) {

		if (LetterSeen[Letter]) {
			result = false; // There is a duplicated letter.
		}
		else {
			LetterSeen[Letter] = true;
		}

	}

	return result;
}
