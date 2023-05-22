
#include "FBullCowGame.h"
#pragma once
FBullCowGame::FBullCowGame()
{
	Reset();
}

void FBullCowGame::Reset()
{
	SetSecretWord();
	MyCurrentTry = 1;
	bIsGameWon = false;
	return;
}

int FBullCowGame::GetMaxTries() const
{
	TMap<int, int> WordLengthToMaxTries{ {3,4},{4,7},{5,9},{6,16} };
	return WordLengthToMaxTries[GetHiddenWordLength()];
}

int FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

int FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const
{

	return bIsGameWon;
}

EGuessStatus FBullCowGame::CheckGuessValidity(std::string Guess) const
{
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	}
	else if(!IsLowerCase(Guess))
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}
	else
	{
		return EGuessStatus::OK;
	}
	
}

FBullCowCount FBullCowGame::SubmitValidGuess(std::string Guess)
{

	MyCurrentTry++;
	FBullCowCount FBullCowCount;
	int WordLength = MyHiddenWord.length();
	for (int i = 0; i < WordLength;i++) 
	{
		for (int j = 0; j < WordLength; j++) 
		{
			if (Guess[j] == MyHiddenWord[i]) {
				if (j == i) FBullCowCount.Bulls++;
				else FBullCowCount.Cows++;
			}
		}
	}
	if (FBullCowCount.Bulls == GetHiddenWordLength()) bIsGameWon = true;
	return FBullCowCount;
}

void FBullCowGame::SetWordLength(int WordLength)
{
	MyWordLength = WordLength;
	return;
}

void FBullCowGame::SetSecretWord()
{
	srand((unsigned int)(time(NULL)));
	int RandomNumber = (rand() % 10);
	switch (MyWordLength) {
	case 3: MyHiddenWord = ThreeLetterWords[RandomNumber];
		break;
	case 4: MyHiddenWord = FourLetterWords[RandomNumber];
		break;
	case 5: MyHiddenWord = FiveLetterWords[RandomNumber];
		break;
	case 6: MyHiddenWord = SixLetterWords[RandomNumber];
		break;
	}
	return;
}

bool FBullCowGame::IsLowerCase(std::string Word) const
{
	for (auto Letter : Word) {
		if (islower(Letter)) return true;
		else return false;
	}
	return true;
}

bool FBullCowGame::IsIsogram(std::string Word) const
{
	if (Word.length() <= 1) return true;

	TMap <char, bool> LetterSeen;
	for (auto Letter : Word) {
		Letter = tolower(Letter);
		if (LetterSeen[Letter]) return false;
		else 
		{
			LetterSeen[Letter] = true;
		}
	}
	return true;
}
