#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <time.h>
#include <map>
using namespace std;
/*
 * Returns a string of the alphabet where
 * any alphabet which is present in guesses is
 * is replaced with a _
 */
string getUsedLetters(string guesses)
{
    //Initialize return string
    string usedLetters;
    //Loop through alphabet and see which letters are used
    for (char i = 'a'; i <= 'z'; i++) {
        if (guesses.find(i) == (size_t) -1) {
            usedLetters +=  i;
        } else {
            usedLetters += "_";
        }
        usedLetters += " ";
    }
    return usedLetters;
}

/*
 * Returns a string which contains the letters guessed
 * in the word. The myster letters are represented by a -
 * Takes in the guesses, all the guesses the user made, and
 * the string word, the word to be guessed.
 */
string getWord(string guesses, string word)
{
    //Loop through word and see which characters have not been guessed
    string s;
    for (size_t i = 0; i < word.length(); i++) {
        if (guesses.find(word.at(i)) == (size_t) -1 ) {
            s += "-";
        } else {
            s += word.at(i);
        }
    }
    return s;
}

/*
 * Prints a message to stdin which displays the number of guesses left,
 * used letters, and the current word.
 * Takes in tries, maxTries, guesses, and word as parameters
 */
void printMessage(int tries, int maxTries, string guesses, string word)
{
    //Print messages to stdin
    int numGuesses = maxTries - tries;
    cout << "You have " << numGuesses << " guesses left." << endl;
    cout<< "Used letters: "  << getUsedLetters(guesses) << endl;
    cout << "Word: " << getWord(guesses, word) << endl;
}

/*
 * Returns a string which contains an alternate word to be guessed.
 * Takes in wordFamilies, largestFam, guess, guesses, wordToGuess, and len as
 * parameters.
 *
 */
string alternateWord(multimap<string,string> wordFamilies, string largestFam, char guess, string guesses, string wordToGuess, int len){
    multimap<string,string>::iterator it = wordFamilies.find(largestFam);
    //Loop through all elements with a specific key using iterator it
    for( int i = 0;  i < len;  i++ ) {
        string curr = (*it).second;
        if (curr.find(guess) == string::npos) {
            string pattern = getWord(guesses, wordToGuess);
            bool match = true;
            //Loop through current word to see if pattern matches
            for (size_t n = 0; n < curr.length(); n++) {
                if (pattern.at(n) != '-') {
                    if (curr.at(n) != pattern.at(n)) {
                        match = false;
                        multimap<string,string>::iterator temp = it;
                        ++temp;
                        wordFamilies.erase(it);
                        it = temp;
                        break;
                    }
                }
            }
            //Check if matching pattern is found
            if (match)
                return curr;
        }
    }
    return "";
}
