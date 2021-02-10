/*
 * Commands.h
 *
 *  Created on: 14 Kas 2020
 *      Author: Beyza
 */

#ifndef COMMANDS_H_
#define COMMANDS_H_

#include <iostream>
#include <fstream>
#include <sstream>
#include "Deck.h"
using namespace std;

class Commands {
	public:
		Deck deck;
		Commands(string deckFile, string commandFile, string outputFile);
};



#endif /* COMMANDS_H_ */
