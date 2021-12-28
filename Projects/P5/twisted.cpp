#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <time.h>
#include <map>
#include "twistedf.h"
using namespace std;

/*
 * main method for game of twisted. Takes argc and argv as arguments.
 * returns 0 on success
 */
int main(int argc, char * argv[])
{
	string guesses;
    string wordToGuess;
	int tries = 0;
    size_t wordLength;
    int maxTries;
    int numLetters;
    multimap<string, string> wordFamilies;
    string largestFam;
    //Prompt user for word length
    cout << "Enter a word length: "; cin >> wordLength;
    //Prompt user for number of tries
    cout << "Maximum number of guesses: "; cin >> maxTries;
    vector<string> outputs;
    string temp;
    ifstream inFile;
    string fileName;
    int attempts = 0;
    //Get text file for words
    if (argc == 2) {
        fileName = argv[1];
    } else {
        fileName = "Dictionary.txt";
    }
    //Store words in a vector
    inFile.open(fileName);
    while (inFile >> temp) {
         if (wordLength == temp.length())
             outputs.push_back(temp);
     }
    inFile.close();
    numLetters = wordLength;
    wordToGuess = outputs[0];
    //Start game
    while (tries < maxTries) {
		printMessage(tries, maxTries, guesses, wordToGuess);
        //Prompt user for guess
		char guess = '?';
        if (tries == 0) {
            while (guess < 97 || guess > 122) {
                cout << "Enter guess: "; cin >> guess;
            }
        } else {
            while (guess < 97 || guess > 122 || guesses.find(guess) != string::npos) {
                cout << "Enter guess: "; cin >> guess;
            }
        }
        //Add guess to guessed letters
        guesses += guess;
        //Create an initial list of words based on first guess
        if (attempts == 0) {
            //Store words according to word families in a multimap
            for (size_t i = 0, e = outputs.size(); i != e; ++i) {
                string curr = outputs[i];
                string family = "";
                for (size_t n = 0; n < curr.length(); n++) {
                    if (curr.at(n) == guess) {
                        family += i;
                    }
                }
                wordFamilies.insert(pair<string, string>(family, curr));
            }
            size_t max = -1;
            //Find largest family
            for( multimap<string, string>::iterator it = wordFamilies.begin();  it != wordFamilies.end();  ++it ) {
                if ( wordFamilies.count((*it).first) > max) {
                    max = wordFamilies.count((*it).first);
                    largestFam = (*it).first;
                }
            }
            //Remove all other word families from multimap
            for (multimap<string, string>::iterator it = wordFamilies.begin(); it != wordFamilies.end();) {
                if ((*it).first.compare(largestFam) != 0) {
                    multimap<string, string>::iterator temp = it;
                    ++temp;
                    wordFamilies.erase(it);
                    it = temp;
                } else {
                    ++it;
                }
            }
            wordToGuess = (*wordFamilies.find(largestFam)).second;
            attempts++;
        }
        //cout << wordToGuess<< endl;
        //Check if the user's guess has any matches
        if (wordToGuess.find(guess) == string::npos) {
            cout << "Sorry, there are no " << guess << "'s." << endl;
            tries++;
        } else {
            //If there are not matches check if there is an alternative word
            string temp = alternateWord(wordFamilies, largestFam, guess, guesses, wordToGuess, wordFamilies.count(largestFam));
            //Check if word exists
            if (!temp.empty()) {
                wordToGuess = temp;
                temp.clear();
                cout << "Sorry, there are no " << guess << "'s." << endl;
                tries++;
            } else {
                //If not alternate exists, the letter is revealed
                int matches = 0;
                for (size_t i = 0; i < wordToGuess.length(); i++) {
                    if (wordToGuess.at(i) == guess) {
                        matches++;
                    }
                }
                if (matches > 1) {
                    cout << "Yes, there are " << matches << " copies of a " << guess << "." << endl;
                } else {
                    cout << "Yes, there is 1 copy of a " << guess << "." << endl;
                }
                numLetters -= matches;
            }
        }
        cout << endl;

        //Check if the user won or lost
        bool gameOver = false;
        if (numLetters == 0) {
            cout << "You guessed all the letters. You win!" << endl;
            gameOver = true;
        } else {
            if (tries == maxTries) {
                cout << "You are out of tries. Game Over!" << endl;
                gameOver = true;
            }
        }
        //Check if the game has ended
        if (gameOver) {
            char newGame;
            //Prompt user for new game
            while (newGame != 'y' && newGame != 'n') {
                cout << "Do you want to play another game? (y/n) "; cin >> newGame;
            }
            if (newGame == 'n') {
                exit(1);
            }
            //Prepare for new game
            cout << "Enter a word length: "; cin >> wordLength;
            cout << "Maximum number of guesses: "; cin >> maxTries;
            //Reinitialize variables and vector based on new criteria
            numLetters = wordLength;
            outputs.clear();
            inFile.open(fileName);
            while (inFile >> temp) {
                if (wordLength == temp.length())
                    outputs.push_back(temp);
            }
            inFile.close();
            wordToGuess = outputs[0];
            wordFamilies.clear();
            guesses.clear();
            largestFam.clear();
            attempts = 0;
            tries = 0;
        }
	}

	return 0;
}
