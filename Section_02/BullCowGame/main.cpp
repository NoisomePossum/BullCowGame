/* This is the console executable that makes use of the BullCow class
This acts as the view in a MVC pattern and is responsible for all user interaction
For game logic see the FBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax Unreal friendly
using FText = std::string;

// function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // instantiate a new game which we reuse across plays

int main() 
{
	do {
		PrintIntro();
		PlayGame();
	} while (AskToPlayAgain());
	
	return 0; // exit the application
}


void PrintIntro() 
{
	std::cout << "\n\nWelcome to Bulls and Cows, a fantabulous word game.\n";
	std::cout << std::endl;
	std::cout << "          }   {         ___ " << std::endl;
	std::cout << "          (o o)        (o o) " << std::endl;
	std::cout << "   /-------\\ /          \\ /-------\\ " << std::endl;
	std::cout << "  / | BULL |O            O| COW  | \\ " << std::endl;
	std::cout << " *  |-,--- |              |------|  * " << std::endl;
	std::cout << "    ^      ^              ^      ^ " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;
	return;
}

// plays a single game up to game win or lose screen
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// loop asking for guesses while the game is NOT won
	// and there are still tries remaining
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();

		// submit valid guess to the game and receive counts
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
}

// loop continually until the user gives a valid guess
FText GetValidGuess()
{
	FText playerGuess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();

		// get a guess from the player
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << "\nBe my guest. Have a guess: ";
		
		getline(std::cin, playerGuess);

		// check the guess validity
		Status = BCGame.CheckGuessValidity(playerGuess);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter an isogram (a word containing no repeating letters).\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter a word in all lowercase letters.\n\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
			break;
		default:
			// assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return playerGuess;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same hidden word (y/n)?";
	FText Response = "";
	getline(std::cin, Response);

	std::cout << "First char:";

	if (Response[0] == 'y' || Response[0] == 'Y') 
	{
		std::cout << " true.\n";
		return true;
	}
	else 
	{
		std::cout << " false.\n";
		return false;
	}
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "GOOD JOB - A WINNER IS YOU!\n";
	}
	else
	{
		std::cout << "Better luck next time.\n";
	}
}
