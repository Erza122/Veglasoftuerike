#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#include <ctime>
#include <cstdlib>

using namespace std;


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


void giveHint(const string& word, vector<bool>& guessedLetters) {
    vector<int> unguessedPositions;
    for (size_t i = 0; i < word.length(); i++) {
        if (!guessedLetters[i]) {
            unguessedPositions.push_back(i);
        }
    }

    if (!unguessedPositions.empty()) {
        int randomIndex = rand() % unguessedPositions.size();
        int position = unguessedPositions[randomIndex];
        guessedLetters[position] = true; 
        cout << "Hint: The letter at position " << position + 1 << " is '" << word[position] << "'." << endl;
    } else {
        cout << "No more hints available!" << endl;
    }
}

int main() {

    string filename = "C:/Users/HP/Desktop/Vegla/Veglasoftuerike/dictionary.txt";


    vector<string> wordList = loadWordsFromFile(filename);

    if (wordList.empty()) {
        cout << "No words loaded from the dictionary." << endl;
        return 1;
    }

    srand(time(0));

  
    string word = wordList[rand() % wordList.size()];
    vector<bool> guessedLetters(word.length(), false);

    int attempts = 6;
    int hintCount = 3;
    char guess;
    bool guessedCorrectly;

    cout << "Welcome to Hangman Game!" << endl;
    cout << "You have " << hintCount << " hints available." << endl;

    while (attempts > 0) {
        cout << "\nYou have " << attempts << " attempts left." << endl;
        cout << "You have " << hintCount << " hints remaining." << endl;
        displayHangman(attempts);  

        cout << "Guess the word: ";
        displayWord(word, guessedLetters);

        cout << "Enter a letter or type 'hint' to use a hint: ";
        cin >> guess;

        if (guess == 'h' || guess == 'H') {
            if (hintCount > 0) {
                giveHint(word, guessedLetters);
                hintCount--;  
            } else {
                cout << "Sorry, you have no more hints left." << endl;
                continue;  
            }
        } else {
            guess = tolower(guess);  

            guessedCorrectly = checkLetter(guess, word, guessedLetters);

            if (guessedCorrectly) {
                cout << "Good guess!" << endl;
            } else {
                attempts--;
                cout << "Wrong guess!" << endl;
            }
        }

        
        if (isWordGuessed(guessedLetters)) {
            cout << "\nCongratulations! You've guessed the word: " << word << endl;
            break;
        }
    }

    if (attempts == 0) {
        displayHangman(0);  
        cout << "\nThe word was: " << word << endl;
    }

    return 0;
}
