#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include "A2.h"
using namespace std;




bool Dictionary::failure = false;//Set attribute "failure" equal to boolean type false.
bool Dictionary::success = true;//Set attribute "success" equal to boolean type true.

Dictionary::Dictionary():maxWordsInDict(10000), maxWordsPerFile(100)//Initialize constant members in the function header.
{
  totalWordsInDict = 0;//Set attribute totalWordsInDict to zero.

  for(int i = 0; i < alphabet; i++)//Loop through A-Z files and initialize it's number count to 0.
    {
      numOfWordsInFile[i] = 0;
    }
}

Dictionary::Dictionary(int dictMaxWords,int fileMaxWords):maxWordsInDict(dictMaxWords),maxWordsPerFile(fileMaxWords)//Initialize constant members int function header.
{
  totalWordsInDict = 0;//This attribute is the same as the default.

  for(int i = 0; i < alphabet; i++)
    {
      numOfWordsInFile[i] = 0;
    }
}

bool Dictionary:: AddAWord(string word)//Passing a word function that his read from the callee function.
{
  char c = toupper(word[0]);//Change first character of word to uppercase and set equal to c.
  int index = c - 'A';//Set an index by subtracting the character by 'A'. First letter in alphabet and gives an index by subtracting ASCCI codes.
  if(numOfWordsInFile[index] == maxWordsPerFile)//If the number of words in that certain file reaches its max allowed,print the following message and return failure.
    {
      // cout<<"Can not add word. Too many words already.";
      return failure;
    }
  if(totalWordsInDict == maxWordsInDict)//If the total words in the dictionary reaches its max allowed, print the following message and return failure.
    {
      // cout<<"Can not add word to the dictionary. Too many words.";
      return failure;
    }

  bool found = SearchForWord(word);//Call the "SearchForWord()" function while passing the word being added as a parameter to check if it exists or not. If so, print following message and return failure.
  if(found)
    {
      return failure;
    }

  ofstream fout;//Create output stream variable.
  string txtFile = "?.txt";//Set the file to be open equal to a dummy.
  txtFile[0] = c;//Set the first character of the dummy variable equal to character c that was initialized above.

    fout.open(txtFile.data(),ios::app);//Open the text file and do not overwrite anything.
   fout<<word<<" ";
  totalWordsInDict++;//Increment counts for both the number in the dictionary and file.
  numOfWordsInFile[index]++;
  return success;

}

bool Dictionary:: DeleteAWord(string wordToDelete)//Function that will delete a word from a file.
{
  vector<string>NewData;//Create a vector. This is used to overwrite a text file.
  char c = toupper(wordToDelete[0]);//Set c equal to the first letter of the word that's to be deleted.
  int index = c - 'A';//Create an index.
  string txtFile ="?.txt";//Serves the same purpose as it was used in AddAWord function.
  txtFile[0] = c;

  ofstream fout;
  ifstream fin;
  string word;
   fin.open(txtFile.data());//Open the text file.
  if(fin.fail())
  return failure;
   while(fin>>word)//While a word is read,continue.
     {
      if(word != wordToDelete)//If the word that does not want to be deleted is equal to a word in the textfile,save that word into the vector so it can be written in later.
	 {
	 NewData.push_back(word);//Pushback word into vector so it is saved.

	 }
	 else if(word == wordToDelete)//If a word does equal the word that's to be deleted, print the following message and decrement both counts.
	 {
	  totalWordsInDict--;
          numOfWordsInFile[index]--;
	 }
    }
	 fin.close();
	 fout.open(txtFile.data());
            for(int i = 0; i < NewData.size();i++)
	      {                                   //Go throught the vector and print out words into the text file. This will overwrite the previous text file.
		fout<<NewData[i]<<" ";
	      }
	    fout.close();
      return success;//Return success.
}


bool Dictionary:: SearchForWord(string word)//Function that searches for a word in a specific textfile.
{
  char c = toupper(word[0]);//Same purpose as before. To open a specific file according to the first character of the word.
  string fileName = "?.txt";
  fileName[0] = c;
  ifstream fin;
  string compare;
  fin.open(fileName.data());
  while(fin>>compare)//While a word is read, continure.
    {

      if(word == compare)//If the word passed in the parameters equals the word from the textfile return true.
	return success;
    }
  return failure;//Else return false.
}




bool Dictionary:: SpellChecking(string fileName)//This function is used to check the spelling from myEssay.txt
{
  ifstream fin;
  string word;
  fin.open(fileName.data());
  if(fin.fail())//If file fails to open return failure.
    return failure;


    cout<<"\n---------------Mispelled words------------------"<<endl;
  while(fin>>word)
    {
      bool check = SearchForWord(word);//Use this function to check if the word read matches a word in the other text file.
      if(!check)

       	cout<<"'"<<word<<"'"<<" is mispelled." <<endl;//If there's no match,print this message.
    }
   return success;
}


bool Dictionary:: InsertWordsIntoDict(string fileName)//Open a text file and enter its contents into its text file.
{
  ifstream fin;
  string word;

  fin.open(fileName.data());
  if(fin.fail())
    {
    return failure;
    }

  while(fin>>word)//While a word is read from the text file, continue.
    {
      bool check = AddAWord(word);//Use this function to add a word into its correct textfile.
      if(!check)
	cout<<"'"<<word<<"'"<<" is already in the dictionary!"<<endl;
    }

  return success;
}





bool Dictionary:: PrintAFileInDict(string filename)
{
  ifstream fin;
  string word;
  vector<string>words;//Vector was used more for formatting purposes. No more than 5 words per line.

  fin.open(filename.data());
  if(fin.fail())
    return failure;
  cout<<"\n\nWords in "<<filename<<endl;
  cout<<"------------------------------------------------"<<endl;
  while(fin>>word)//While a word is read, continue on and push the word into the vector.
    {
      words.push_back(word);

    }
  for(int i = 0; i < words.size();i++)//Display the vector.
    {
      if(i % 5 == 0)
	cout<<endl;//Display a end line if there are more than 5 words per line.

      cout<<words[i]<<" ";
    }
  cout<<endl;
  cout<<"\n------------------------------------------------"<<endl;

  return success;
}

void Dictionary:: ProcessTransactionFile()
{
  string filename;
  string cmd;
  cout<<"Enter Transaction file name: ";
  cin>>filename;
  string word;
  ifstream fin;
  fin.open(filename.data());

  if(fin.fail())//If file fails to open, print following message and quit program.
    {
      cout<<"File does not exxist!"<<endl;
      exit(1);
    }
  while(fin>>cmd)//While a command is read from the transaction file.
    {

      if(cmd == "AddW")//If the command equals a specific word, call its function, read in the next string, and pass that through the parameters.
      {
	fin >> word;
	
	bool check = AddAWord(word);
	if(check==success)
	  cout<<word<<" was successfully added!"<<endl;
	else
	  cout<<word<<" cannot be added!"<<endl;
        }

    else if(cmd == "DeleteW")
      {
	fin >> word;
	bool check = DeleteAWord(word);
	if(check)
	  cout<<word<<" was deleted!"<<endl;
	else
	  cout<<word<<" can not be deleted!"<<endl;
      }

    else if(cmd == "SearchW")
      {
	fin >> word;
	bool check = SearchForWord(word);
	if(check)
	  cout<<word<<" was found!"<<endl;
	else
	  cout<<word<<" was not found!"<<endl;
      }

    else if(cmd == "PrintF")
      {
	fin>>word;
	bool check = PrintAFileInDict(word);
	if(!check)
	  cout<<word<<" does not exist!"<<endl;
      }

    else if(cmd == "SpellCheck")
      {
	fin >> word;
	bool check = SpellChecking(word);
	if(check)
	cout<<"\n------------------------------------------------"<<endl;
      }
    else if(cmd == "InsertF")
      {
	fin >> word;
	bool check = InsertWordsIntoDict(word);
	if(!check)
	  cout<<word<<" does not exist!"<<endl;
	else
	  cout<<word<<" words were successfully added!"<<endl;
      }
    }
}
