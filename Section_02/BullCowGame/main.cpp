#include <iostream>
#include <string>
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

	std::cout << "Welcome to Bulls and Cows biatch!" << std::endl;
	std::cout << "Guess the " << WORD_LENGTH << " letter word isogram" << std::endl;

	FText username = "";
	std::cout << std::endl << "Please tell me your name: ";
	std::getline(std::cin, username);

	std::cout << std::endl << "So... your name is " << username << ". Nice name biatch!" << std::endl;

}

void playGame() {
	
	std::cout << "Let's begin with the game then..." << std::endl << std::endl;

	for (int32 i = 0; i < BCGame.GetMaxTries(); i++) {
		FText Guess = getGuess();
		std::cout << "Your guess was " << Guess << std::endl;
		
		if (BCGame.CheckGuessValidity(Guess)) {
			
			BullCowCount counter = BCGame.SubmitGuess(Guess);
			std::cout << " BULLS: " << counter.Bulls << " Cows: " << counter.Cows << std::endl;
			
			if (BCGame.IsGameWon(counter)) {
				std::cout << "YOU FUCKING WON!!!!!!!!!!!!!!!" << std::endl;
				break;
			}
			else {
				if (BCGame.GetCurrentTry() > BCGame.GetMaxTries()) {
					std::cout << "YOU ARE A LOOSER BIATCH!!" << std::endl;
					break;
				}
			}
		}
		else {
			std::cout << "Invalid guess length" << std::endl;
		}
		
	}
}

FText getGuess() {

	std::cout << std::endl << "Try " << BCGame.GetCurrentTry() << ". Tell me what's your guess: ";
	FText guess = "";
	std::getline(std::cin, guess);

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