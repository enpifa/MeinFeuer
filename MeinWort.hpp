//
//  MeinWort.hpp
//  testing
//
//  Created by Enric Piferrer Torres on 8/3/18.
//  Copyright © 2018 Enric Piferrer Torres. All rights reserved.
//

#ifndef MeinWort_hpp
#define MeinWort_hpp

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MeinWort {
private:
  string word;
  string determinant;
  string meaning;
  string topic;
public:
  MeinWort();
  MeinWort(string newword, string newdet, string newmeaning);
  MeinWort(string newword, string newdet, string newmeaning, string topic);
  string getWord();
  string getDeterminant();
  string getMeaning();
  string getTopic();
  void setWord(string newword);
  void setDeterminant(string newdet);
  void setMeaning(string newmeaning);
  void setTopic(string newtopic);
  
};

#endif /* MeinWort_hpp */
