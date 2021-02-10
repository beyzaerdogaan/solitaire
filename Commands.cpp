/*
 * Commands.cpp
 *
 *  Created on: 13 Kas 2020
 *      Author: Beyza
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include "Commands.h"
#include "Deck.h"
using namespace std;


Commands::Commands(string deckFile, string commandFile, string outputFile) : deck(deckFile) {
	deck.fill();
	ofstream output;
	output.open(outputFile);
	output << "\n";
	deck.display(output);
	ifstream MyReadFile(commandFile);
	string line;
	while (getline (MyReadFile, line)) {
		if (line.substr(0,1) == "o") {
			if (line.substr(5,1) == "f") {
				deck.openFromStock(output);
			}
			else {
				int card = stoi(line.substr(5,1));
				deck.open(card, output);
			}
			deck.display(output);
		}

		else if (line.substr(0,1) == "e") {
			deck.exit(output);
			break;
		}

		else if (line.substr(0,1) == "m") {
			if (line.substr(8,1) == "f") {
				if (line.substr(19,1) == "p") {
					int pile = stoi(line.substr(24,1));
					deck.moveToFoundationPile(pile, output);
				}

				else if (line.substr(19,1) == "w") {
					deck.moveToFoundationWaste(output);
				}
			}

			else if (line.substr(5,1) == "p") {
				int sourcePile = stoi(line.substr(10,1));
				int sourcePileIndex = stoi(line.substr(12,2));
				int destinationPile = 0;
				if (sourcePileIndex > 9) {
					destinationPile = stoi(line.substr(15,1));
				}
				else {
					destinationPile = stoi(line.substr(14,1));
				}
				deck.moveP(sourcePile, sourcePileIndex, destinationPile, output);
			}

			else if (line.substr(5,1) == "w") {
				int pile = stoi(line.substr(11,1));
				deck.moveW(pile, output);
			}

			else if (line.substr(5,1) == "f") {
				int f = stoi(line.substr(16,1));
				int p = stoi(line.substr(18,1));
				deck.moveF(f, p, output);
			}
			deck.display(output);
		}
		deck.win(output);
	}
	MyReadFile.close();
	output.close();
}



