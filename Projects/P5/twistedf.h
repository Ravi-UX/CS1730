#ifndef TWISTED_H
#define TWISTEDF_H
using namespace std;
extern string getUsedLetters(string guesses);
extern string getWord(string guesses, string word);
extern void printMessage(int tries, int maxTries, string guesses, string word);
extern string alternateWord(multimap<string,string> wordFamilies, string largestFam, char guess, string guesses, string wordToGuess, int len);

#endif
