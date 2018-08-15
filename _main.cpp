#include "MeinFeuer.hpp"
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <sstream>

using namespace std;

void printMenuOptions();
void problem_testingbits();
void problem_meinfeuer();
void initializeQuestions(int qn[], const int size);
void shuffleQuestions(int qn[], const int size);
void determineDeterminant(string &det);
void readNewWort(MeinWort &mw, string line);
void readMeinFeuer(MeinFeuer &mf, string filename, int &num);
void playOneRound(MeinFeuer &mf, int num);
void printScores(int points, int num);

int main()
{
  /*
   The programs prints a menu for the user to choose an option. Each option refers to a different problem.
   Once the user enters the option, the program executes the option and ends.
   */
  cout << "Welcome to my C++ tester" << endl;
  printMenuOptions();
  
  int option;
  cin >> option;
  
  switch(option) {
    case 1:
      /* Another game, nothing to do with MeinFeuer */
      problem_testingbits();
      break;
      
    case 2:
      problem_meinfeuer();
      break;
      
    default:
      break;
  }
  
  cout << endl << "Closing. Thank you!" << endl;
  
  return 0;
}

void printMenuOptions()
{
  /*
   Print the menu options available for the user.
   */
  cout << "What would you like to do today?" << endl;
  cout << endl << "Option 1: Testing bits" << endl;
  cout << "Option 2: Open Mein Feuer" << endl;
  cout << "Option 0: Exit" << endl;
}

void problem_meinfeuer()
{
  /*
   Manage the operations for the MeinFeuer program. First, the user enters the topic option. Then the program loads the topic and starts the game. We assume there is no file named 'notafile.txt' in the directory. This is used to control when the user selects an option that is not available. As the admin creates more topics, more options should be added to the switch conditional and to the 'printTopicOptions' function.
   */
  MeinFeuer mf;
  mf.printTopicOptions();
  
  int topic;
  cin >> topic;
  string filename = "notafile.txt";
  
  switch(topic)
  {
    case 1:
      filename = "body.txt";
      break;
    
    case 2:
      filename = "animals.txt";
      break;
      
    case 3:
      filename = "colors.txt";
      break;
      
    case 4:
      filename = "food.txt";
      break;
      
    default:
      break;
  }
  
  cout << "Loading words..." << endl;
  
  int number_of_words=0;
  readMeinFeuer(mf, filename, number_of_words);
  
  cout << "Starting game..." << endl;
  
  playOneRound(mf, number_of_words);
}

void initializeQuestions(int qn[], const int size)
{
  /* 
   Initialize the array with the number of questions for the topic selected by the user. Depending on the topic, there will be more/less number of questions available.
   size: number of questions for the topic and size of the array qn.
   qn: array that stores the questions number.
   */
  for (int i = 0; i < size; i++)
    qn[i] = i;
}

void shuffleQuestions(int qn[], const int size)
{
  /* 
   Shuffle the question numbers to modify the order the questions are shown to the user every execution. The methodology used performs a swap between each item in the array and a random item in the array. The random seed is modified depending on time of execution to get different randomization every execution.
   size: number of question for the topic and size of the array qn.
   qn: array that stores the questions number.
   */
  srand (time(NULL));
  
  for (int i = size-1; i > 0; i--)
  {
    /* Pick a random index from 0 to i */
    int j = rand() % (i+1);
    
    /* Swap item at position i with the item at random index j */
    int tmp = qn[i];
    qn[i] = qn[j];
    qn[j] = tmp;
  }
}

void determineDeterminant(string &det)
{
  if (det == "a") det = "der";
  else if (det == "b") det = "die";
  else if (det == "c") det = "das";
  else det = "schlecht";
}

void readNewWort(MeinWort &mw, string line)
{
  /* 
   This function reads a new MeinWort from 'line' and stores the four components in 'mw'. 
   */
  int data = 0;
  string word;
  stringstream linestream(line);
  
  while (getline(linestream, word, ',')) {
    if (data==0) mw.setWord(word);
    else if (data==1) mw.setDeterminant(word);
    else if (data==2) mw.setMeaning(word);
    else mw.setTopic(word);
    data++;
  }
}

void readMeinFeuer(MeinFeuer &mf, string filename, int &num)
{
  /* 
   This function reads from the file 'filename' and stores its information in 'mf'. The file contains all the words to be guessed for the topic selected. Each line contains four strings, which form a MeinWort, or a word to be guessed. We assume the file contains one word-to-guess per line, with each component separated by a comma without spaces. For examples: "Zahn,der,tooth,body" could be in one line, being equivalent to "word,determinant,meaning,topic".
   */
  ifstream file;
  string name_of_file = "/Users/lepetitpifa/Documents/_testing_cpp/testing/testing/" + filename;
  file.open(name_of_file);
  
  if (!file) {
    /* If the file is not succesfully open, close the application */
    
    cout << "Unable to read this file..." << endl;
    exit(1);
  } else {
    /* Each line from the file contains the four variables needed by a MeinWort, comma separated. First we read the line, and then we read each word. 'mf' stores all the words to play the chosen topic. */
    string line;
    while (getline(file, line, '\n')) {
      /* A new line has been read successfully, meaning there are still lines to be read in the file. 'mw' stores all the information needed for each word to guess */
      num++;
      cout << "Line " << num << ":  " << line << endl;
      
      MeinWort mw;
      readNewWort(mw, line);
      mf.addWort(mw);
    }
    cout << num << " words read." << endl;
  }
  
}

void playOneRound(MeinFeuer &mf, int num)
{
  /* 
   This function first creates a random order to ask the words of the topic chosen by the user, using the 'shuffleQuestions' function. After that, asks the questions in that random order and compares the user answers with the correct answers. If both determinant and meaning are guessed correctly, the answer is considered correct for that word. It finally uses 'printScores' to print the final scores.
   */
  int question_number[num];
  initializeQuestions(question_number, num);
  shuffleQuestions(question_number, num);
  
  int question = 1;
  int points = 0;
  
  for (int i = 0; i < num; i++)
  {
    int qnum = question_number[i];
    
    cout << endl << "QUESTION " << question << ": " << mf.getWort(qnum).getWord() << endl;
    cout << "Determinant: " << endl << "a) der" << endl << "b) die" << endl << "c) das" << endl;
    
    string det;
    cin >> det;
    
    determineDeterminant(det);
    
    cout << "Meaning?" << endl;
    
    string meaning;
    cin >> meaning;
    
    if (mf.getWort(qnum).getDeterminant() == det && mf.getWort(qnum).getMeaning() == meaning) {
      cout << "Das ist gut!" << endl;
      points++;
    } else {
      if (mf.getWort(qnum).getDeterminant() != det) cout << "Nein! The determinant is " << mf.getWort(qnum).getDeterminant() << endl;
      if (mf.getWort(qnum).getMeaning() != meaning) cout << "Nein! It means " << mf.getWort(qnum).getMeaning() << endl;
    }
    
    question++;
    
  }
  
  printScores(points, num);
  
}

void printScores(int points, int num)
{
  /* 
   Print scores of a round of the game. 
   */
  cout << endl << "Die ende!" << endl;
  cout << "Correct answers: " << points << endl;
  
  if (num == points) {
    cout << "That is perfection!" << endl;
  } else {
    double percentage = 100*points/num;
    cout << fixed << setprecision(2) << percentage << "%" << endl;
  }
}
