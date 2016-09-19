#include<iostream>
#include<string>
#include<vector>
#include<fstream>
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
  Dictionary();//Done
  Dictionary(int dictMaxWords, int fileMaxWords);//Done
  bool AddAWord(string word);//Done
  bool DeleteAWord(string word);//Done
  bool SearchForWord(string word);//Done
  bool PrintAFileInDict(string filename);//Done
  bool SpellChecking(string fileName);//Done
  bool InsertWordsIntoDict(string fileName);//Done
  void ProcessTransactionFile();
};

bool Dictionary::failure = false;//Set the attribute "failure" to bool type false
bool Dictionary::success = true;//Set the attribute "success" to bool type true

Dictionary::Dictionary():maxWordsInDict(10000), maxWordsPerFile(100)//constant members initialized in the header of the function
{
  totalWordsInDict = 0;
 
  for(int i = 0; i < alphabet; i++)
    {
      numOfWordsInFile[i] = 0;
    }
}

Dictionary::Dictionary(int dictMaxWords,int fileMaxWords):maxWordsInDict(dictMaxWords),maxWordsPerFile(fileMaxWords)
{
   totalWordsInDict = 0;

  for(int i = 0; i < alphabet; i++)
    {
      numOfWordsInFile[i] = 0;
    }
}

bool Dictionary:: AddAWord(string word)
{
  char c = toupper(word[0]);
  int index = c - 'A';
  if(numOfWordsInFile[index] == maxWordsPerFile)
    {
      cout<<"Can not add word. Too many words already.";
	return failure;
    }
  if(totalWordsInDict == maxWordsInDict)
    {
      cout<<"Can not add word to the dictionary. Too many words.";
	return failure;
    }

  bool found = SearchForWord(word);
  if(found)
    {
      cout<<"'"<<word<<"'"<<" already exists! Cannot add!"<<endl;
      return failure;
    }

      ofstream fout;
      string txtFile = "?.txt";
      txtFile[0] = c;

      fout.open(txtFile.data(),ios::app);
      fout<<word<<" ";
      cout<<"'"<<word<<"'"<<" has been successfully added to "<<txtFile<<" !"<<endl;
      totalWordsInDict++;
      numOfWordsInFile[index]++;
      return success;
    
}

bool Dictionary:: DeleteAWord(string wordToDelete)
{
  vector<string>NewData;
  char c = toupper(wordToDelete[0]);
  int index = c - 'A';
  string txtFile ="?.txt";
  txtFile[0] = c;

  ofstream fout;
  ifstream fin;
  string word;
  fin.open(txtFile.data());
  while(fin>>word)
    {
      if(word != wordToDelete)
	{
	  NewData.push_back(word);
	  
	}
      else if(word == wordToDelete)
	{
	  totalWordsInDict--;
	  numOfWordsInFile[index]--;
	  return failure;
	}

      for(int i = 0; i < NewData.size();i++)
	fout<<NewData[i]<<" ";
      return success;
    }
  fin.close();

  fout.open(txtFile.data());
    for(int i = 0; i < NewData.size(); i++)
      {
	fout<<NewData[i]<<" "<<endl;
      }
    
  fout.close();
}

bool Dictionary:: SearchForWord(string word)
{
  char c = toupper(word[0]);
  string fileName = "?.txt";
  fileName[0] = c;
  ifstream fin;
  string compare;
  fin.open(fileName.data());
  while(fin>>compare)
    {
      if(word == compare)
	  return true;
    }
  return false;//This was changed 1:35
}




bool Dictionary:: SpellChecking(string fileName)
{
  ifstream fin;
  string word;
  fin.open(fileName.data());
  if(fin.fail())
    return failure;


  cout<<"\n---------------Mispelled words------------------"<<endl;
  while(fin>>word)  
    {
      bool check = SearchForWord(word);
      if(!check)//this was changed 1:50

	cout<<"'"<<word<<"'"<<" is mispelled." <<endl;
    }
  cout<<"\n------------------------------------------------"<<endl;

  return success;//this was changed 1:50
}

bool Dictionary:: InsertWordsIntoDict(string fileName)
{
  ifstream fin;
  string word;

  fin.open(fileName.data());
  if(fin.fail())
    {
      return failure;
    }

  while(fin>>word)
    {
      bool check = AddAWord(word);

      // if(!check)
      //return failure;
    }
  return success;
}





bool Dictionary:: PrintAFileInDict(string filename)
{
  ifstream fin;
  string word;
  vector<string>words;

  fin.open(filename.data());
    if(fin.fail())
      return failure;  
    cout<<"\n\nWords in "<<filename<<endl;
    cout<<"------------------------------------------------"<<endl;
    while(fin>>word)
      {
	words.push_back(word);
	
     }
    for(int i = 0; i < words.size();i++)
      {
	if(i % 5 == 0)
	  cout<<endl;

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

  while(fin>>cmd)
    {
  if(cmd == "AddW")
    {
      fin >> word;
      AddAWord(word);
    }
 
  else if(cmd == "DeleteW")
    {
      fin >> word;
      DeleteAWord(word);
    }
 
  else if(cmd == "SearchW")
    {
      fin >> word;
      SearchForWord(word);
    }
 
  else if(cmd == "PrintF")
    {
      fin>>word;
      PrintAFileInDict(word);
    }
 
  else if(cmd == "SpellCheck")
    {
      fin >> word;
      SpellChecking(word);
    }
  else if(cmd == "InsertF")
    {
      fin >> word;
      InsertWordsIntoDict(word);
    }
    }
}

int main()
{
  Dictionary Oxford;
  Oxford.ProcessTransactionFile();
}
 



