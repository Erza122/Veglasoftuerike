#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <ctime>

using namespace std;

// Function to display the hangman figure based on the number of attempts left
void displayHangman(int attempts) {
    cout << "\n";
    if (attempts == 6) {
        cout << "    -----\n";
        cout << "    |   |\n";
        cout << "        |\n";
        cout << "        |\n";
        cout << "        |\n";
        cout << "        |\n";
        cout << "  ==========\n";
    }
    else if (attempts == 5) {
        cout << "    -----\n";
        cout << "    |   |\n";
        cout << "    O   |\n";
        cout << "        |\n";
        cout << "        |\n";
        cout << "        |\n";
        cout << "  ==========\n";
    }
    else if (attempts == 4) {
        cout << "    -----\n";
        cout << "    |   |\n";
        cout << "    O   |\n";
        cout << "    |   |\n";
        cout << "        |\n";
        cout << "        |\n";
        cout << "  ==========\n";
    }
    else if (attempts == 3) {
        cout << "    -----\n";
        cout << "    |   |\n";
        cout << "    O   |\n";
        cout << "   /|   |\n";
        cout << "        |\n";
        cout << "        |\n";
        cout << "  ==========\n";
    }
    else if (attempts == 2) {
        cout << "    -----\n";
        cout << "    |   |\n";
        cout << "    O   |\n";
        cout << "   /|\\  |\n";
        cout << "        |\n";
        cout << "        |\n";
        cout << "  ==========\n";
    }
    else if (attempts == 1) {
        cout << "    -----\n";
        cout << "    |   |\n";
        cout << "    O   |\n";
        cout << "   /|\\  |\n";
        cout << "   /    |\n";
        cout << "        |\n";
        cout << "  ==========\n";
    }
    else if (attempts == 0) {
        cout << "    -----\n";
        cout << "    |   |\n";
        cout << "    O   |\n";
        cout << "   /|\\  |\n";
        cout << "   / \\  |\n";
        cout << "        |\n";
        cout << "  ==========\n";
        cout << "Game Over! The word was guessed incorrectly.\n";
    }
}

// Function to display the current state of the guessed word
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

// Function to check if the letter is in the word
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

// Function to check if the word is completely guessed
bool isWordGuessed(const vector<bool>& guessedLetters) {
    for (bool guessed : guessedLetters) {
        if (!guessed) {
            return false;
        }
    }
    return true;
}

// Function to load words from a file
vector<string> loadWordsFromFile(const string& filename) {
    vector<string> words;
    ifstream file(filename);

    if (!file) {
        cout << "Error: Could not open file!" << endl;
        return words;
    }

    string word;
    while (getline(file, word)) {
        word.erase(remove_if(word.begin(), word.end(), ::isspace), word.end());
        if (!word.empty()) {
            words.push_back(word);
        }
    }

    file.close();
    return words;
}

int main() {
    // Specify the absolute path to the dictionary file
    string filename = "C:/Users/HP/Desktop/Vegla/Veglasoftuerike/dictionary.txt";

    // Load words from the file
    vector<string> wordList = loadWordsFromFile(filename);

    if (wordList.empty()) {
        cout << "No words loaded from the dictionary." << endl;
        return 1;
    }

    srand(time(0));

    // Randomly select a word
    string word = wordList[rand() % wordList.size()];
    vector<bool> guessedLetters(word.length(), false);

    int attempts = 6;
    char guess;
    bool guessedCorrectly;

    cout << "Welcome to Hangman Game!" << endl;

    while (attempts > 0) {
        cout << "\nYou have " << attempts << " attempts left." << endl;
        displayHangman(attempts);  // Display hangman figure

        cout << "Guess the word: ";
        displayWord(word, guessedLetters);

        cout << "Enter a letter: ";
        cin >> guess;

        guess = tolower(guess);  // Make the guess case-insensitive

        guessedCorrectly = checkLetter(guess, word, guessedLetters);

        if (guessedCorrectly) {
            cout << "Good guess!" << endl;
        } else {
            attempts--;
            cout << "Wrong guess!" << endl;
        }

        // Check if the word is fully guessed
        if (isWordGuessed(guessedLetters)) {
            cout << "\nCongratulations! You've guessed the word: " << word << endl;
            break;
        }
    }

    if (attempts == 0) {
        displayHangman(0);  // Display the final figure when game is over
        cout << "\nThe word was: " << word << endl;
    }

    return 0;
}
