import sys
import random
from datetime import datetime

class MeinFeuer():
  # Contain all the information needed for the game, stored in an array of MeinWort

  def __init__(self, content):
    #
    # Initialize class MeinFeuer
    # meinworten: an array of MeinWort
    # number_of_worten: size of the array, equivalent to the number of questions available for a topic
    #
    self.meinworten = []
    self.number_of_worten = 0
    self.getMeinWorten(content)

  def getMeinWorten(self, content):
    #
    # Having the content (questions) for a specific topic, manipulate the data from the text file to get the Worts and append them to the meinworten array
    # We assume the data is loaded in content as follows: each line contains the four Wort variables (word, determinant, meaning, topic), each of them separated by comma and without spaces, forming those four variables a Wort. There are as many lines in the file as Worts for the topic
    # Therefore, first we split the content by endlines, getting a lines array, and then for each line get the four variables of a Wort by spliting by comma. Then, append the MeinWort.
    #
    lines = content.split('\n')
    self.number_of_worten = len(lines) - 1

    for index, line in enumerate(lines):
      worten = line.split(',')
      if (index != (self.number_of_worten)) :
        mw = MeinWort(worten[0], worten[1], worten[2], worten[3])
        self.meinworten.append(mw)
      else : break
      print worten[0]

  def printWorten(self):
    # Print word from each Wort in meinworten
    for mw in self.meinworten:
      print mw.getWord()

  def getNumberOfWorten(self):
    # Get size of meinworten, stored in number_of_worten
    return self.number_of_worten

  def getWort(self, position):
    # Get the Wort in index=position from the array meinworten
    return self.meinworten[position]


class MeinWort():
  # Contain all the information needed for a question or Wort
  
  def __init__(self, word, determinant, meaning, topic):
    #
    # Initialize class MeinWort
    # word: word in german to be questioned
    # determinant: right determinant for word
    # meaning: word meaning in english
    # topic: topic of the word. Could be used for future cases where there are more than one topic questioned
    #
    self.word = word
    self.determinant = determinant
    self.meaning = meaning
    self.topic = topic

  def getWord(self):
    # Get the Word variable value from the class
    return self.word

  def getDeterminant(self):
    # Get the Determinant variable value from the class
    return self.determinant

  def getMeaning(self):
    # Get the Meaning variable value from the class
    return self.meaning

  def getTopic(self):
    # Get the Topic variable value from the class
    return self.topic

  def setWord(self, newword):
    # Set the Word variable value to newword
    self.word = newword

  def setDeterminant(self, newdet):
    # Set the Determinant variable value to newdet
    self.determinant = newdet

  def setMeaning(self, newmeaning):
    # Set the Meaning variable value to newmeaning
    self.meaning = newmeaning

  def setTopic(self, newtopic):
    # Set the Topic variable value to newtopic
    self.topic = newtopic


def welcome():
  # Print a welcome message
  print "Welcome to MeinFeuer game. Please, choose your topic:"


def printTopic():
  # Print topics available
  print
  print "Topic 1. Body"
  print "Topic 2. Food"
  print "Topic 3. Animals"
  print


def getTopic(topic, isfilename):
  # Return the topic name or the text file name for a topic, depending on the value of isfilename. If we need the filename, isfilename should be called with value "yes", then we add ".txt"
  name = ""
  if topic == 1 : name = "body"
  elif topic == 2: name = "food"
  elif topic == 3: name = "animals"
  else : name = "notanoption"

  if (isfilename=="yes") : name += ".txt"
  return name


def initializeQuestions(number):
  # Create, initialize and return an array of size number, containing sorted values from 0 to number-1
  question_number = []
  [question_number.append(num) for num in range(number)]
  return question_number


def shuffleQuestions(qn, number):
  # Shuffle the values of qn by using random functions. By setting up a random seed depending on time, each execution shuffles the question in different order. For each position in the array qn, swap the value with the value of a random position
  # qn: we assume it contains a sorted list of values from 0 to number-1
  # number: size of qn
  random.seed(datetime.now())

  for num in range(number):
    random_position = random.randint(0,number-1)
    tmp = qn[random_position]
    qn[random_position] = qn[num]
    qn[num] = tmp

  return qn


def determineDeterminant(det):
  # Convert the user's answer into the equivalent determinant. We assume det contains the user answer, and should be a, b, or c
  if det == "a" : det = "der"
  elif det == "b" : det = "die"
  elif det == "c" : det = "das"
  else : det = "schlecht"

  return det


def printScores(points, num):
  # Print the final scores
  # points: number of correct answers
  # num: number of questions
  print "\nDie ende!"
  print "Correct answers: " + str(points)
  print ["That is perfection!" if points == num else str("%4.2f%%" % (float(points*100)/num))]


def saveGame(points, topic, total):
  # Create or open the gamestats file and append the game stats: correct answers (points), number of questions (total), and the topic chosen, together with the date.
  game = open("gamestats.txt","a+")
  
  mydata = "\n-----------------------------------------------------------"
  mydata += str(datetime.now().strftime("%Y-%m-%d %H:%M"))
  mydata += "\nTopic: " + str(topic)
  score = float(points)/total
  mydata += "\nScore: " + str(points) + "/" + str(total) + " : " + str("%4.2f%%" % (100*score)) + "\n"

  game.write(mydata)
  game.close()


def playTopic(mf):
  # Play the topic chosen by the user. We assume mf is a MeinFeuer that contains all the information to ask questions to the user. The question_number array contains the questions to be asked, shuffled randomly. Points variable stores the number of correct answers. Each question has two parts: first, determine the determinant appropiate for the german word; second, guess the meaning. An answer is considered correct if both parts are answered correctly. Otherwise, the answer is wrong and a message is displayed showing the mistake.
  question_number = initializeQuestions(mf.getNumberOfWorten())
  question_number = shuffleQuestions(question_number, mf.getNumberOfWorten())

  question = 1
  points = 0
  
  print "\nTotal number of questions: " + str(mf.getNumberOfWorten())

  for i in range(mf.getNumberOfWorten()):
    qnum = question_number[i]
    
    print "\nQUESTION " + str(question) + ": " + str(mf.getWort(qnum).getWord())
    print "Determinant:\na) der\nb) die\nc) das"
    
    det = str(raw_input("Your answer (a, b or c): "))
    det = determineDeterminant(det.lower())
    
    print "\nMeaning?"
    meaning = str(raw_input("Your answer: "))
    
    if (mf.getWort(qnum).getDeterminant() == det and mf.getWort(qnum).getMeaning() == meaning) :
      print "Das ist gut!"
      points += 1
    else :
      if (mf.getWort(qnum).getDeterminant() != det) :
        print "Nein! The determinant is " + str(mf.getWort(qnum).getDeterminant())
      if (mf.getWort(qnum).getMeaning() != meaning) :
        print "Nein! It means " + str(mf.getWort(qnum).getMeaning())
    
    question += 1

  printScores(points, mf.getNumberOfWorten())

  return points


def main():
  # The main function creates a dialog between the user and the program. The user choses the topic to play, and the program loads the words for the topic, stored in a txt file the name of the topic. The content of the file is read, the MeinFeuer is loaded, and the game starts. Once all the questions are asked, the game stores the results and finishes.
  welcome()
  
  printTopic()

  topic = int(raw_input("Your choice: "))
  
  print "\nLoading topic " + str(topic) + "...\n"

  file = open(getTopic(topic, isfilename="yes"),"r")
  
  if file.mode == 'r':
    content = file.read()
    mf = MeinFeuer(content)
    points = playTopic(mf)
    saveGame(points, getTopic(topic, isfilename="no"), mf.getNumberOfWorten())


if __name__== "__main__":
  main()
