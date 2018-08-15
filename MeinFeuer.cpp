//
//  MeinFeuer.cpp
//  testing
//
//  Created by Enric Piferrer Torres on 8/3/18.
//  Copyright © 2018 Enric Piferrer Torres. All rights reserved.
//

#include "MeinFeuer.hpp"

#include <string>
#include <iostream>
#include <vector>

using namespace std;

MeinFeuer::MeinFeuer() {};

MeinFeuer::MeinFeuer(int size, vector<MeinWort> *mw)
{
  /* Constructor function */
  for (int s = 0; s < size; s++)
  {
    meinworten->push_back(mw->at(s));
  }
}

void MeinFeuer::addWort(MeinWort mw)
{
  meinworten->push_back(mw);
}

void MeinFeuer::removeWort(MeinWort mw)
{
  /* The remove function has some extra difficulty considering we need to first find the wort, and then remove it. */
  int position = 0;
  for (int i = 0; i < meinworten->size(); i++)
  {
    if (meinworten->at(i).getWord() == mw.getWord())
    {
      position = i;
      break;
    }
  }
  meinworten->erase(meinworten->begin() + position);
}

MeinWort MeinFeuer::getWort(int position)
{
  return meinworten->at(position);
}

void MeinFeuer::printTopicOptions()
{
  /*
   Print the topic options available for the user. Each topic refers to a different language section.
   */
  cout << "Please, choose your topic:" << endl;
  cout << endl << "Topic 1: Body" << endl;
  cout << "Topic 2: Animals" << endl;
  cout << "Topic 3: Colors" << endl;
  cout << "Topic 4: Food" << endl;
  cout << "Topic 100: All in" << endl;
  cout << "Exit: 0" << endl;
}
