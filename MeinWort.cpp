//
//  MeinWort.cpp
//  testing
//
//  Created by Enric Piferrer Torres on 8/3/18.
//  Copyright © 2018 Enric Piferrer Torres. All rights reserved.
//

#include "MeinWort.hpp"

#include <string>
#include <iostream>

using namespace std;

MeinWort::MeinWort(){}

MeinWort::MeinWort(string newword, string newdet, string newmeaning)
{
  /* First customized constructor */
  word = newword;
  determinant = newdet;
  meaning = newmeaning;
}

MeinWort::MeinWort(string newword, string newdet, string newmeaning, string newtopic)
{
  /* Second customized constructor */
  word = newword;
  determinant = newdet;
  meaning = newmeaning;
  topic = newtopic;
}

string MeinWort:: getWord()
{
  return word;
}

string MeinWort::getDeterminant()
{
  return determinant;
}

string MeinWort::getMeaning()
{
  return meaning;
}

string MeinWort::getTopic()
{
  return topic;
}

void MeinWort::setWord(string newword)
{
  word = newword;
}

void MeinWort::setDeterminant(string newdet)
{
  determinant = newdet;
}

void MeinWort::setMeaning(string newmeaning)
{
  meaning = newmeaning;
}

void MeinWort::setTopic(string newtopic)
{
  topic = newtopic;
}
