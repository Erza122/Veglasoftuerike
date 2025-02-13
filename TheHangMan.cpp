#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


void displayWord(const string& word, const vector<bool>& guessedLetters) {
    for (size_t i = 0; i < word.length(); i++) {
        if (guessedLetters[i]) {
            cout << word[i] << " ";
        } else {
            cout << "_ ";
        }
    }
    cout << endl;
}

bool checkLetter(char letter, const string& word, vector<bool>& guessedLetters) {
    bool found = false;
    for (size_t i = 0; i < word.length(); i++) {
        if (word[i] == letter && !guessedLetters[i]) {
            guessedLetters[i] = true;
            found = true;
        }
    }
    return found;
}


bool isWordGuessed(const vector<bool>& guessedLetters) {
    for (bool guessed : guessedLetters) {
        if (!guessed) {
            return false;
        }
    }
    return true;
}

int main() {
    
    vector<string> wordList = {"programming", "algorithm", "computer", "hangman", "challenge"};
    
    
    string word = wordList[rand() % wordList.size()];
    vector<bool> guessedLetters(word.length(), false);

    int attempts = 6;  
    char guess;
    bool guessedCorrectly;

    cout << "Welcome to Hangman Game!" << endl;

    while (attempts > 0) {
        cout << "\nYou have " << attempts << " attempts left." << endl;
        cout << "Guess the word: ";
        displayWord(word, guessedLetters);

        cout << "Enter a letter: ";
        cin >> guess;

        
        guess = tolower(guess);

        guessedCorrectly = checkLetter(guess, word, guessedLetters);

        if (guessedCorrectly) {
            cout << "Good guess!" << endl;
        } else {
            attempts--;
            cout << "Wrong guess!" << endl;
        }

        
        if (isWordGuessed(guessedLetters)) {
            cout << "\nCongratulations! You've guessed the word: " << word << endl;
            break;
        }
    }

    if (attempts == 0) {
        cout << "\nGame Over! The word was: " << word << endl;
    }

    return 0;
}
