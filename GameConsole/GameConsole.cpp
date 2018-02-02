#include "stdafx.h"
#include <iostream>
#include "Minesweeper.h"

using namespace std;

int main()
{
	char levelOpt;
	char reset;
	
	do {
		cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-" << endl;
		cout << "Minesweeper Game ASCII style!!" << endl;
		cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-" << endl << endl;
		cout << "[b]eginner 10X10" << "	[i]ntermediate 16X16" << endl;
		cout << "[a]dvance 16X30" << "		[e]xit game" << endl;
		cout << ":::: Select level or cancel game: ";
		cin >> levelOpt;
		cout << endl;

		switch (levelOpt) {
		case 'b':
			Minesweeper(10, 10, 10);
		case 'i':
			Minesweeper(16, 16, 40);
		case 'a':
			Minesweeper(16, 30, 100);
		case 'e':
			return 1;
		default:
			Minesweeper(10, 10, 10);
		}
		
		cout << "Play again [y/n]? ";
		cin >> reset;
	} while (reset == 'y' || reset == 'Y');

	return 0;
}