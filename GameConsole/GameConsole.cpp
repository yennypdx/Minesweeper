#include "stdafx.h"
#include <iostream>
#include "Minesweeper.h"

using namespace std;

int main()
{
	char reset;
	char levelOpt;
	
	do {
		cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-" << endl;
		cout << "Minesweeper Game ASCII style!!" << endl;
		cout << "*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-" << endl << endl;
		cout << "[b]eginner 10X10" << "	[i]ntermediate 16X16" << endl;
		cout << "[a]dvance 16X30" << "		[e]xit game" << endl;
		cout << ":: Select level or cancel game: ";
		cin >> levelOpt;
		cout << endl;

		switch (levelOpt) {
		case 'b':
			//using 1 based indexes
			Minesweeper(10, 10, 10);
			break;
		case 'i':
			Minesweeper(16, 16, 40);
			break;
		case 'a':
			Minesweeper(16, 30, 100);
			break;
		case 'e':
			return 1;
		default:
			Minesweeper(10, 10, 10);
			break;
		}
		
		cout << "Play again [y/n]? ";
		cin >> reset;
	} while (reset == 'y' || reset == 'Y');

	system("pause");
	return 0;
}