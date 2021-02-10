/*
 * Deck.cpp
 *
 *  Created on: 13 Kas 2020
 *      Author: Beyza
 */

#include <iostream>
#include <fstream>
#include "Deck.h"
#include <string.h>
using namespace std;


Deck::Deck(string file) {
	ifstream MyReadFile(file);
	string line;
	int index = 51;
	while (getline (MyReadFile, line)) {
		deckArray[index] = line;
		index -= 1;
	}
	MyReadFile.close();
}


int Deck::length(string pile[20]) {
	int size = 0;
	for (int i = 0; i < 20; i++) {
		if (!pile[i].empty()) {
			size += 1;
		}
	}
	return size;
}


int Deck::lengthF(string foundation[13]) {
	int size = 0;
	for (int i = 0; i < 13; i++) {
		if (!foundation[i].empty()) {
			size += 1;
		}
	}
	return size;
}


int Deck::lengthS() {
	int size = 0;
	for (int i = 0; i < 24; i++) {
		if (!stock[i].empty()) {
			size += 1;
		}
	}
	return size;
}


int Deck::lengthW(string waste[10]) {
	int size = 0;
	for (int i = 0; i < 10; i++) {
		if (!waste[i].empty()) {
			size += 1;
		}
	}
	return size;
}


int Deck::findFoundationNumber(string letter) {
	if (letter == "H") {
		return 0;
	}
	else if (letter == "D") {
		return 1;
	}
	else if (letter == "S") {
		return 2;
	}
	else {
		return 3;
	}
}


void Deck::deleteElement(int index, string type) {
	if (type == "p") {
		int l = length(tableau[index]);
		for (int i = 0; i < l; i++) {
			if (tableau[index][i+1].empty()) {
				tableau[index][i] = "";
				control[index][i] = "";
			}
		}
	}
	else if (type == "f") {
		int l = lengthF(foundation[index]);
		for (int i = 0; i < l; i++) {
			if (foundation[index][i+1].empty()) {
				foundation[index][i] = "";
			}
		}
	}
}


void Deck::fill() {
	int index = 0;
	int n = 0;
	for (int i = n; i < 7; i++) {
		for (int j = n; j < 7; j++) {
			tableau[j][i] = deckArray[index];
			index += 1;
		}
		n += 1;
	}


	for (int k = 0; k < 7; k++) {
		for (int l = 0; l < length(tableau[k]) - 1; l++) {
			control[k][l] = "c";
		}
		control[k][length(tableau[k])-1] = "o";
	}

	int stockIndex = 0;
	for (int j = 28; j < 52; j++) {
		stock[stockIndex] = deckArray[j];
		stockIndex++;
	}

}


void Deck::display(ofstream& file) {
	if (lengthS() != 0) {
		file << "@@@ ";
	}
	else {
		file << "___ ";
	}

	int max = lengthW(waste[0]);
	if (max > 0) {
		for (int i = 0; i < 3; i++) {
			if (waste[i][max-1].empty()) {
				file << "___ ";
			}
			else {
				file << waste[i][max-1] << " ";
			}
		}
	}
	else if (max == 0) {
		for (int i = 0; i < 3; i++) {
			file << "___ ";
		}
	}
	file << "        ";

	for (int j = 0; j < 4; j++) {
		if (foundation[j][0].empty()) {
			file << "___ ";
		}
		else {
			int l = lengthF(foundation[j]);
			file << foundation[j][l-1] << " ";
		}
	}

	file << "\n\n";

	int maxRepeat = length(tableau[0]);
	for (int k = 1; k <= 6; k++) {
		if (maxRepeat < length(tableau[k])) {
			maxRepeat = length(tableau[k]);
		}
	}
	for (int l = 0; l <= maxRepeat + 1; l++) {
		for (int m = 0; m < 7; m++) {
			if (tableau[m][l].empty()) {
				file << "   ";
			}
			else {
				if (control[m][l] == "c") {
					file << "@@@";
				}
				else if (control[m][l] == "o") {
					file << tableau[m][l];
				}
			}
			file << "   ";
		}
		file << "\n";
	}
}


void Deck::openFromStock(ofstream& file) {
	file << "open from stock\n\n";
	file << "****************************************\n\n";
	if (lengthS() > 0) {
		int len = lengthW(waste[0]);
		for (int i = 0; i < 3; i++) {
			waste[i][len] = stock[i];
			stock[i] = "";
		}
		for (int j = 0; j < lengthS(); j++) {
			stock[j] = stock[j+3];
			stock[j+3] = "";
		}
	}

	else if (lengthS() == 0) {
		int l = lengthW(waste[0]);
		int index = 0;
		for (int j = 0 ; j < l ; j++) {
			for (int i = 0 ; i < 3; i++) {
				if (!waste[i][j].empty()) {
					stock[index] = waste[i][j];
					index += 1;
					waste[i][j] = "";
				}
			}
		}
	}
}


void Deck::moveP(int spn, int spi, int dpn, ofstream& file) {
	file << "move pile " << spn << " " << spi << " " << dpn << "\n\n";
	int lpd = length(tableau[dpn]);
	int lps = length(tableau[spn]);
	if (lpd > 0 && lps > 0) {
		int index = lps-1-spi;
		if (tableau[spn][lps-1-spi].substr(0,1) == "D" || tableau[spn][lps-1-spi].substr(0,1) == "H") {
			if (tableau[dpn][lpd-1].substr(0,1) == "S" || tableau[dpn][lpd-1].substr(0,1) == "C") {
				int n = stoi(tableau[spn][lps-1-spi].substr(1,2));
				int n2 = stoi(tableau[dpn][lpd-1].substr(1,2));
				if (n+1 == n2) {
					for (int i = 0; i <= spi; i++) {
						if (control[spn][index] == "o") {
							tableau[dpn][lpd] = tableau[spn][index];
							control[dpn][lpd] = "o";
							index += 1;
							lpd += 1;
							lps -= 1;
						}
					}
					for (int j = 0; j <= spi; j++) {
						deleteElement(spn, "p");
					}
				}
				else {
					file << "Invalid Move!\n\n";
				}
			}
			else {
				file << "Invalid Move!\n\n";
			}
		}
		else if (tableau[spn][lps-1-spi].substr(0,1) == "S" || tableau[spn][lps-1-spi].substr(0,1) == "C") {
			if (tableau[dpn][lpd-1].substr(0,1) == "H" || tableau[dpn][lpd-1].substr(0,1) == "D") {
				int n = stoi(tableau[spn][lps-1-spi].substr(1,2));
				int n2 = stoi(tableau[dpn][lpd-1].substr(1,2));
				if (n+1 == n2) {
					for (int i = 0; i <= spi; i++) {
						if (control[spn][index] == "o") {
							tableau[dpn][lpd] = tableau[spn][index];
							control[dpn][lpd] = "o";
							index += 1;
							lpd += 1;
							lps -= 1;
						}
					}
					for (int j = 0; j <= spi; j++) {
						deleteElement(spn, "p");
					}
				}
				else {
					file << "Invalid Move!\n\n";
				}
			}
			else {
				file << "Invalid Move!\n\n";
			}
		}
	}
	else if (lpd == 0 && lps > 0) {
		int k = stoi(tableau[spn][lps-1].substr(1,2));
		if (k == 13 && control[spn][lps-1] == "o") {
			tableau[dpn][0] = tableau[spn][lps-1];
			control[dpn][0] = "o";
			lpd += 1;
			deleteElement(spn, "p");
			lps -= 1;
		}
		else {
			file << "Invalid Move!\n\n";
		}
	}
	else if (lps == 0) {
		file << "Invalid Move!\n\n";
	}
	file << "****************************************\n\n";
}


void Deck::moveW(int pile, ofstream& file) {
	file << "move waste " << pile << "\n\n";
	int l = length(tableau[pile]);
	int l0 = lengthW(waste[0]);
	int l1 = lengthW(waste[1]);
	int l2 = lengthW(waste[2]);
	if (l != 0 && control[pile][l-1] == "o") {
		if (l2 != 0 && !waste[2][l0-1].empty()) {
			int n = stoi(tableau[pile][l-1].substr(1,2));
			int n2 = stoi(waste[2][l0-1].substr(1,2));
			if (tableau[pile][l-1].substr(0,1) == "D" || tableau[pile][l-1].substr(0,1) == "H") {
				if (waste[2][l0-1].substr(0,1) == "S" || waste[2][l0-1].substr(0,1) == "C") {
					if (n2 + 1 == n && control[pile][l-1] == "o") {
						tableau[pile][l] = waste[2][l0-1];
						control[pile][l] = "o";
						waste[2][l0-1] = "";
					}
					else {
						file << "Invalid Move!\n\n";
					}
				}
				else {
					file << "Invalid Move!\n\n";
				}
			}
			if (tableau[pile][l-1].substr(0,1) == "S" || tableau[pile][l-1].substr(0,1) == "C") {
				if (waste[2][l0-1].substr(0,1) == "D" || waste[2][l0-1].substr(0,1) == "H") {
					if (n2 + 1 == n && control[pile][l-1] == "o") {
						tableau[pile][l] = waste[2][l0-1];
						control[pile][l] = "o";
						waste[2][l0-1] = "";
					}
					else {
						file << "Invalid Move!\n\n";
					}
				}
				else {
					file << "Invalid Move!\n\n";
				}
			}
		}
		else if (l1 != 0 && !waste[1][l0-1].empty()) {
			int n = stoi(tableau[pile][l-1].substr(1,2));
			int n2 = stoi(waste[1][l0-1].substr(1,2));
			if (tableau[pile][l-1].substr(0,1) == "D" || tableau[pile][l-1].substr(0,1) == "H") {
				if (waste[1][l0-1].substr(0,1) == "S" || waste[1][l0-1].substr(0,1) == "C") {
					if (n2 + 1 == n && control[pile][l-1] == "o") {
						tableau[pile][l] = waste[1][l0-1];
						control[pile][l] = "o";
						waste[1][l0-1] = "";
					}
					else {
						file << "Invalid Move!\n\n";
					}
				}
				else {
					file << "Invalid Move!\n\n";
				}
			}
			else if (tableau[pile][l-1].substr(0,1) == "S" || tableau[pile][l-1].substr(0,1) == "C") {
				if (waste[1][l0-1].substr(0,1) == "D" || waste[1][l0-1].substr(0,1) == "H") {
					if (n2 + 1 == n && control[pile][l-1] == "o") {
						tableau[pile][l] = waste[1][l0-1];
						control[pile][l] = "o";
						waste[1][l0-1] = "";
					}
					else {
						file << "Invalid Move!\n\n";
					}
				}
				else {
					file << "Invalid Move!\n\n";
				}
			}
		}

		else if (l0 != 0 && !waste[0][l0-1].empty()) {
			int n = stoi(tableau[pile][l-1].substr(1,2));
			int n2 = stoi(waste[0][l0-1].substr(1,2));
			if (tableau[pile][l-1].substr(0,1) == "D" || tableau[pile][l-1].substr(0,1) == "H") {
				if (waste[0][l0-1].substr(0,1) == "S" || waste[0][l0-1].substr(0,1) == "C") {
					if (n2 + 1 == n && control[pile][l-1] == "o") {
						tableau[pile][l] = waste[0][l0-1];
						control[pile][l] = "o";
						waste[0][l0-1] = "";
					}
					else {
						file << "Invalid Move!\n\n";
					}
				}
				else {
					file << "Invalid Move!\n\n";
				}
			}
			else if (tableau[pile][l-1].substr(0,1) == "S" || tableau[pile][l-1].substr(0,1) == "C") {
				if (waste[0][l0-1].substr(0,1) == "D" || waste[0][l0-1].substr(0,1) == "H") {
					if (n2 + 1 == n && control[pile][l-1] == "o") {
						tableau[pile][l] = waste[0][l0-1];
						control[pile][l] = "o";
						waste[0][l0-1] = "";
					}
					else {
						file << "Invalid Move!\n\n";
					}
				}
				else {
					file << "Invalid Move!\n\n";
				}
			}
		}
		else {
			file << "Invalid Move!\n\n";
		}
	}
	else if (l == 0) {
		if (l2 != 0 && !waste[2][l0-1].empty()) {
			if (stoi(waste[2][l0-1].substr(1,2)) == 13) {
				tableau[pile][0] = waste[2][l0-1];
				control[pile][0] = "o";
				waste[2][l0-1] = "";
			}
			else {
				file << "Invalid Move!\n\n";
			}
		}
		else if (l1 != 0 && !waste[1][l0-1].empty()) {
			if (stoi(waste[1][l0-1].substr(1,2)) == 13) {
				tableau[pile][0] = waste[1][l0-1];
				control[pile][0] = "o";
				waste[1][l0-1] = "";
			}
			else {
				file << "Invalid Move!\n\n";
			}
		}
		else if (l0 != 0 && !waste[0][l0-1].empty()) {
			if (stoi(waste[0][l0-1].substr(1,2)) == 13) {
				tableau[pile][0] = waste[0][l0-1];
				control[pile][0] = "o";
				waste[0][l0-1] = "";
			}
			else {
				file << "Invalid Move!\n\n";
			}
		}
	}
	file << "****************************************\n\n";
}


void Deck::moveF(int f, int p, ofstream& file) {
	file << "move foundation " << f << " " << p << "\n\n";
	int len = lengthF(foundation[f]);
	int lengthP = length(tableau[p]);
	if (len != 0 && lengthP != 0) {
		string card = foundation[f][len-1];
		string letter = foundation[f][len-1].substr(0,1);
		int number = stoi(foundation[f][len-1].substr(1,2));
		string letterP = tableau[p][lengthP-1].substr(0,1);
		int numberP = stoi(tableau[p][lengthP-1].substr(1,2));
		if (number + 1 == numberP) {
			if (letter == "D" || letter == "H") {
				if (letterP == "S" || letterP == "C") {
					tableau[p][lengthP] = card;
					control[p][lengthP] = "o";
					foundation[f][len-1] = "";
				}
				else {
					file << "Invalid Move!\n\n";
				}
			}
			else if (letter == "S" || letter == "C") {
				if (letterP == "D" || letterP == "H") {
					tableau[p][lengthP] = card;
					control[p][lengthP] = "o";
					foundation[f][len-1] = "";
				}
				else {
					file << "Invalid Move!\n\n";
				}
			}
		}
		else {
			file << "Invalid Move!\n\n";
		}
	}

	else if (len != 0 && lengthP == 0) {
		file << "here\n";
		if (stoi(foundation[f][len-1].substr(1,2)) == 13) {
			tableau[p][0] = foundation[f][len-1];
			control[p][0] = "o";
			foundation[f][len-1] = "";
		}
		else {
			file << "Invalid Move!\n\n";
		}
	}

	else {
		file << "Invalid Move!\n\n";
	}

	file << "****************************************\n\n";
}


void Deck::moveToFoundationPile(int pile, ofstream& file) {
	file << "move to foundation pile " << pile << "\n\n";
	int len = length(tableau[pile]);
	if (len != 0 && control[pile][len-1] == "o") {
		string letter = tableau[pile][len-1].substr(0,1);
		int num = stoi(tableau[pile][len-1].substr(1,2));
		int f = findFoundationNumber(letter);
		int num2 = 0;
		if (lengthF(foundation[f]) != 0) {
			num2 = stoi(foundation[f][lengthF(foundation[f])-1].substr(1,2));
		}
		else {
			num2 = 0;
		}
		if (num2 + 1 == num) {
			foundation[f][lengthF(foundation[f])] = tableau[pile][len-1];
			deleteElement(pile, "p");
		}
		else {
			file << "Invalid Move!\n\n";
		}
	}
	else {
		file << "Invalid Move!\n\n";
	}
	file << "****************************************\n\n";
}



void Deck::moveToFoundationWaste(ofstream& file) {
	file << "move to foundation waste\n\n";
	int l = lengthW(waste[0]);
	string letter;
	string card;
	int num = 0;
	int f = 0;
	int num2 = 0;
	if (l > 0) {
		if (!waste[2][l-1].empty()) {
			letter = waste[2][l-1].substr(0,1);
			f = findFoundationNumber(letter);
			num = stoi(waste[2][l-1].substr(1,2));
			if (lengthF(foundation[f]) != 0) {
				num2 = stoi(foundation[f][lengthF(foundation[f])-1].substr(1,2));
				if (num2 + 1 == num) {
					foundation[f][lengthF(foundation[f])] = waste[2][l-1];
					waste[2][l-1] = "";
				}
				else {
					file << "Invalid Move!\n\n";
				}
			}
			else {
				if (num == 1) {
					foundation[f][lengthF(foundation[f])] = waste[2][l-1];
					waste[2][l-1] = "";
				}
				else {
					file << "Invalid Move!\n\n";
				}
			}
		}

		else if (waste[2][l-1].empty() && !waste[1][l-1].empty()) {
			letter = waste[1][l-1].substr(0,1);
			f = findFoundationNumber(letter);
			num = stoi(waste[1][l-1].substr(1,2));
			if (lengthF(foundation[f]) != 0) {
				num2 = stoi(foundation[f][lengthF(foundation[f])-1].substr(1,2));
				if (num2 + 1 == num) {
					foundation[f][lengthF(foundation[f])] = waste[1][l-1];
					waste[1][l-1] = "";
				}
				else {
					file << "Invalid Move!\n\n";
				}
			}
			else {
				if (num == 1) {
					foundation[f][lengthF(foundation[f])] = waste[1][l-1];
					waste[1][l-1] = "";
				}
				else {
					file << "Invalid Move!\n\n";
				}
			}
		}

		else if (!waste[0][l-1].empty() && waste[1][l-1].empty() && waste[2][l-1].empty()) {
			letter = waste[0][l-1].substr(0,1);
			f = findFoundationNumber(letter);
			num = stoi(waste[0][l-1].substr(1,2));
			if (lengthF(foundation[f]) != 0) {
				num2 = stoi(foundation[f][lengthF(foundation[f])-1].substr(1,2));
				if (num2 + 1 == num) {
					foundation[f][lengthF(foundation[f])] = waste[0][l-1];
					waste[0][l-1] = "";
				}
				else {
					file << "Invalid Move!\n\n";
				}
			}
			else {
				if (num == 1) {
					foundation[f][lengthF(foundation[f])] = waste[0][l-1];
					waste[0][l-1] = "";
				}
				else {
					file << "Invalid Move!\n\n";
				}
			}
		}
	}
	else {
		file << "Invalid Move!\n\n";
	}
	file << "****************************************\n\n";
}


void Deck::open(int pile, ofstream& file) {
	file << "open " << pile << "\n\n";
	int l = length(tableau[pile]);
	if (l != 0) {
		if (control[pile][l-1] == "c") {
				control[pile][l-1] = "o";
		}
		else {
			file << "Invalid Move!\n\n";
		}
	}
	else {
		file << "Invalid Move!\n\n";
	}
	file << "****************************************\n\n";
}


void Deck::exit(ofstream& file) {
	file << "exit\n\n";
	file << "****************************************\n\n";
	file << "Game Over!\n";
}


void Deck::win(ofstream& file) {
	int f0, f1, f2, f3 = 0;
	if (lengthF(foundation[0]) != 0 && lengthF(foundation[1]) != 0 && lengthF(foundation[2]) != 0 && lengthF(foundation[3]) != 0) {
		f0 = stoi(foundation[0][lengthF(foundation[0]) - 1].substr(1,2));
		f1 = stoi(foundation[1][lengthF(foundation[1]) - 1].substr(1,2));
		f2 = stoi(foundation[2][lengthF(foundation[2]) - 1].substr(1,2));
		f3 = stoi(foundation[3][lengthF(foundation[3]) - 1].substr(1,2));
	}
	if (f0 == 13 && f1 == 13 && f2 == 13 && f3 == 13) {
		file << "****************************************\n\n";
		file << "You Win!\n\n";
		file << "Game Over!\n";
	}
}




