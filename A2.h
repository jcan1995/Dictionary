/*
SOURCE CODE
The purpose of this program is to follow a set of commands. It can either add a word, delete a word, search for words, and check the spelling of words.

3/16/2015
Joshua Cantero
cante008@cougars.csusm.edu
619.942.6705
Written over the span of 2 weeks.
*/
#ifndef DICTIONARY_H
#define DICTIONARY_H

#include<string>
using namespace std;

const int alphabet = 26;
class Dictionary
{
 private:
  const int maxWordsInDict;
  const int maxWordsPerFile;
  int totalWordsInDict;
  int numOfWordsInFile[alphabet];
  static bool failure;
  static bool success;

 public:
  Dictionary();//Default constructor
  Dictionary(int dictMaxWords, int fileMaxWords);//Constructor with parameters
  bool AddAWord(string word);//Function will add a word from a file and store in its correct file name.
  bool DeleteAWord(string word);//Function will delete a word from a file
  bool SearchForWord(string word);//Done
  bool PrintAFileInDict(string filename);//Will print a file 
  bool SpellChecking(string fileName);//Checks if words are mispelled
  bool InsertWordsIntoDict(string fileName);//Opens file names and uses AddAWord function to add the words into the correct file.
  void ProcessTransactionFile();
};

#endif
