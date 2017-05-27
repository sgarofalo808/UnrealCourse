#include <iostream>
#include <string>
#include <algorithm>
#include "main.h"
#include "FBullCowGame.h"

constexpr int32 WORD_LENGTH = 5;

FBullCowGame BCGame;

int32 main() {

	printIntro();

	do {
		playGame();
	} while (askToPlayAgain());

	return 0;
}

void printIntro() {

	std::cout << "Welcome to Bulls and Cows!" << std::endl;
	std::cout << "Guess the " << WORD_LENGTH << " letter word isogram" << std::endl;

	FText username = "";
	std::cout << std::endl << "Please tell me your name: ";
	std::getline(std::cin, username);

}

void playGame() {

	std::cout << "Let's begin with the game then..." << std::endl << std::endl;

	bool gameWon = false;

	while (!gameWon && BCGame.GetCurrentTry() <= BCGame.GetMaxTries()) {
		FText Guess = getGuess();
		std::cout << "Your guess was " << Guess << std::endl;

		switch (BCGame.CheckGuessValidity(Guess)) {

		case EGuessValidity::OK: {

			BullCowCount counter = BCGame.SubmitGuess(Guess);
			std::cout << " BULLS: " << counter.Bulls << " Cows: " << counter.Cows << std::endl;

			if (BCGame.IsGameWon(counter)) {
				std::cout << "YOU ARE A WINNER!" << std::endl;
				gameWon = true;
				break;
			}
			else {
				if (BCGame.GetCurrentTry() > BCGame.GetMaxTries()) {
					std::cout << "YOU ARE A LOOSER!" << std::endl;
					break;
				}
			}

			break;
		}

		case EGuessValidity::NOT_AN_ISOGRAM: {
			std::cout << "Guess is not an isogram" << std::endl;
			break;
		}

		case EGuessValidity::WRONG_LENGTH: {
			std::cout << "Invalid guess length" << std::endl;
			break;
		}

		default: {
			std::cout << "Invalid just because" << std::endl;
			break;
		}
		}
	}
}

FText getGuess() {

	std::cout << std::endl << "Try " << BCGame.GetCurrentTry() << ". Tell me what's your guess: ";
	FText guess = "";
	std::getline(std::cin, guess);
	std::transform(guess.begin(), guess.end(), guess.begin(), ::tolower);

	return guess;
}

bool askToPlayAgain() {

	std::cout << std::endl << "Do you want to play again? ";
	FText option = "";
	std::getline(std::cin, option);

	if (option[0] == 'y' || option[0] == 'Y') {
		BCGame.Reset();
		return true;
	}
	else {
		return false;
	}

}