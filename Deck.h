/*
 * Deck.h
 *
 *  Created on: 14 Kas 2020
 *      Author: Beyza
 */

#ifndef DECK_H_
#define DECK_H_
#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

class Deck {
	private:
		string deckArray[52];
		string waste[3][10];
		string tableau[7][20];
		string control[7][20];
		string stock[24];
		string foundation[4][13];
	public:
    	Deck(string file);
    	void display(ofstream& file);
    	void fill();
    	void openFromStock(ofstream& file);
    	void moveP(int spn, int spi, int dpn, ofstream& file);
    	void moveW(int pile, ofstream& file);
    	void moveF(int f, int p, ofstream& file);
    	void moveToFoundationPile(int pile, ofstream& file);
    	void moveToFoundationWaste(ofstream& file);
    	void open(int pile, ofstream& file);
    	void exit(ofstream& file);
    	void deleteElement(int index, string type);
    	void win(ofstream& file);
    	int length(string pile[20]);
    	int lengthF(string foundation[13]);
    	int lengthS();
    	int lengthW(string waste[10]);
    	int findFoundationNumber(string letter);
};



#endif /* DECK_H_ */
