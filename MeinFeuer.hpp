//
//  MeinFeuer.hpp
//  testing
//
//  Created by Enric Piferrer Torres on 8/3/18.
//  Copyright © 2018 Enric Piferrer Torres. All rights reserved.
//

#ifndef MeinFeuer_hpp
#define MeinFeuer_hpp

#include <stdio.h>
#include "MeinWort.hpp"

#include <string>
#include <iostream>
#include <vector>

using namespace std;

class MeinFeuer {
private:
  vector<MeinWort> *meinworten = new vector<MeinWort> ();
public:
  MeinFeuer();
  MeinFeuer(int size, vector<MeinWort> *mw);
  void addWort(MeinWort mw);
  void removeWort(MeinWort mw);
  MeinWort getWort(int position);
  void printTopicOptions();
};

#endif /* MeinFeuer_hpp */
