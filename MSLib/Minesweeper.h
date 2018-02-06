#include "stdafx.h"
#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <iostream>
#include <time.h>
#include <string>
#include <cstdlib>
#include "Array2DP.h"
#include "Cell.h"

using namespace std;

class Minesweeper
{
public:
	Minesweeper();
	Minesweeper(int dimX, int dimY, int minesNum, bool inCheat = false);
	~Minesweeper();
public:
	void startGame();
	void initGame();
public:
	void addMines();
	int countSuroundingMines(int inRow, int inCol);
	int countFlaggedMines();
public:
	void revealCell(int inRow, int inCol);
	void flagCell(int inRow, int inCol);
	void unFlagCell(int inRow, int inCol);
public:
	void displayProgress();
	void setCellNumbers();
public:
	bool isValidCoord(int inRow, int inCol);
	bool isMine(int inRow, int inCol);
	bool isFlagged(int inRow, int inCol);
	bool isCovered(int inRow, int inCol);
	void uncoverCell(int inRow, int inCol);
public:
	void checkGameStatus();
	bool checkWin();

private:
	int m_column;
	int m_row;
	int m_minesNum;
	bool m_validGame;
	bool m_cheat;
	Array2DP<Cell> m_realBoardLayout;
};

const char COVERED = '?';
const char FLAGGED = 'P';
const char MINE = 'X';
const char BLANK = '0';

Minesweeper::Minesweeper()
{
	m_row = 1;
	m_column = 1;
	m_minesNum = 0;
	m_realBoardLayout = Array2DP<Cell>();
	m_validGame = true;
	m_cheat = false;
	initGame();
}

Minesweeper::Minesweeper(int inRow, int inCol, int minesNum, bool inCheat):
	m_row(inRow), m_column(inCol), m_minesNum(minesNum), m_cheat(inCheat)
{	
	//using 1 based index
	m_realBoardLayout = Array2DP<Cell>(m_row, m_column);
	m_validGame = true;
	initGame();
	startGame();
}

Minesweeper::~Minesweeper()
{}

void Minesweeper::startGame()
{
	int userRow = 0;
	int userCol = 0;
	char userOps;
	char ansCheat;

	while (m_validGame == true) {
		cout << "[r]eveal [f]lag [u]nflag [c]heat" << endl;
		cout << ":: Operator: ";
		cin >> userOps;
		
		switch (userOps) {
		case 'r':
			cout << ":: Choose ROW number: ";
			cin >> userRow;
			cout << ":: Choose COLUMN number: ";
			cin >> userCol;
			revealCell(userRow - 1, userCol - 1);
			break;
		case 'f':
			cout << ":: Choose ROW number: ";
			cin >> userRow;
			cout << ":: Choose COLUMN number: ";
			cin >> userCol;
			flagCell(userRow - 1, userCol - 1);
			break;
		case 'u':
			cout << ":: Choose ROW number: ";
			cin >> userRow;
			cout << ":: Choose COLUMN number: ";
			cin >> userCol;
			unFlagCell(userRow - 1, userCol - 1);
			break;
		case 'c':
			cout << ":: Are you sure [y/n]? ";
			cin >> ansCheat;
			if (ansCheat == 'y') {
				m_cheat = true;
				m_validGame = false;
			}
			break;
		}
		cout << endl;
		displayProgress();
		checkGameStatus();
		cout << endl;
	}
}

void Minesweeper::initGame()
{
	addMines();
	displayProgress();
	setCellNumbers();
}

void Minesweeper::addMines()
{
	//using 0 based indexes for Setting Mine Cells
	srand((unsigned)time(NULL));
	for (int i = 0; i < m_minesNum; i++) {
		bool placed = false;
		while (placed == false) {
			int x = rand() % m_row;
			int y = rand() % m_column;
			if (m_realBoardLayout[x][y].getMineCell() == false) 
			{
				m_realBoardLayout[x][y].setMineCell(true);
				placed = true;
			}
		}
	}
}

int Minesweeper::countSuroundingMines(int inRow, int inCol)
{
	int mine_count = 0;
		
	if (isMine(inRow - 1, inCol - 1)) { 
		mine_count++;
	}
		if (isMine(inRow - 1, inCol)) { 
			mine_count++;
		}
	if (isMine(inRow - 1, inCol + 1)) { 
		mine_count++;
	}
		if (isMine(inRow, inCol + 1)) { 
			mine_count++;
		}
	if (isMine(inRow + 1, inCol + 1)) { 
		mine_count++;
	}
		if (isMine(inRow + 1, inCol)) { 
			mine_count++;
		}
	if (isMine(inRow + 1, inCol - 1)) {
		mine_count++;
	}
		if (isMine(inRow, inCol - 1)) {
			mine_count++;
		}
	return mine_count;
}

int Minesweeper::countFlaggedMines()
{
	int numFlagged = 0;
	for (int r = 0; r < m_row; r++) {
		for (int c = 0; c < m_column; c++) {
			if (m_realBoardLayout[r][c].getFlaggedCell() == true) {
				numFlagged++;
			}
		}
	}
	return numFlagged;
}

void Minesweeper::revealCell(int inRow, int inCol)
{
	if (isValidCoord(inRow, inCol)) {
		if (isMine(inRow, inCol)) {
			m_validGame = false;
		}

		if (isCovered(inRow, inCol) == true) {
			uncoverCell(inRow, inCol);	//Selected Cell
			uncoverCell(inRow - 1, inCol - 1);	//Top-Left Cell
			uncoverCell(inRow - 1, inCol);	//Top Cell
			uncoverCell(inRow - 1, inCol + 1);	//Top-Right Cell
			uncoverCell(inRow, inCol + 1);	//Right Cell
			uncoverCell(inRow + 1, inCol + 1);	//Bottom-Right Cell
			uncoverCell(inRow + 1, inCol);	//Bottom Cell
			uncoverCell(inRow + 1, inCol - 1);	//Bottom-Left Cell
			uncoverCell(inRow, inCol - 1);	//Left Cell
		}
		else {
			cout << "Cell is already uncovered" << endl;
		}
	}
	else {
		cout << "Input is out of range. Try again." << endl;
	}
}

void Minesweeper::flagCell(int inRow, int inCol)
{
	if (isValidCoord(inRow, inCol)) {
		if (m_realBoardLayout[inRow][inCol].getCoveredCell() == true) {
			m_realBoardLayout[inRow][inCol].setFlaggedCell(true);
		}
		else {
			cout << "Cell is already revealed. Try again." << endl;
		}
	}
	else {
		cout << "Input is out of range. Try again." << endl;
	}
}

void Minesweeper::unFlagCell(int inRow, int inCol)
{
	if (isValidCoord(inRow, inCol)) {
		if (m_realBoardLayout[inRow][inCol].getFlaggedCell() == true) {
			m_realBoardLayout[inRow][inCol].setFlaggedCell(false);
		}
		else {
			cout << "Cell is currently unflagged. Try again." << endl;
		}
	}
	else {
		cout << "Input is out of range. Try again." << endl;
	}
}

void Minesweeper::displayProgress()
{
	if (m_cheat == true) {
		cout << endl << "[Showing Answer Board Layout]" << endl;
	}
	//display column numbering
	cout << "    ";
	for (int horiztl = 1; horiztl <= m_column; horiztl++) {
		cout << horiztl << "  ";
	}
	cout << endl;

	for (int row = 1; row <= m_row; row++) {
		//display row numbering
		if (row < 10) {
			cout << row << " |";
		}
		else {
			cout << row << "|";
		}
		//display content in row
		for (int col = 1; col <= m_column; col++) { 
			char val = COVERED;	
			//check if cell is covered			
			if (isFlagged(row - 1, col - 1)) { 
				val = FLAGGED; 
			}
			else {
				if (isCovered(row - 1, col - 1) == false) {
					string number = to_string(m_realBoardLayout[row - 1][col - 1].getNumberCell());
					val = number[0];
				}

				if (m_cheat == true || m_validGame == false) {
					if (isMine(row - 1, col - 1)) {
						val = '*';
					}
					else {
						string number = to_string(m_realBoardLayout[row - 1][col - 1].getNumberCell());
						val = number[0];
					}
				}
			}

			if (col >= 10) {
				cout << "  " << val;
			}
			else {
				cout << " " << val;
			}
			cout << " ";
		}
		cout << endl;
	}
	cout << endl;
	if (m_cheat == true) {
		cout << "Too bad you cheat!" << endl;
	}
}

void Minesweeper::setCellNumbers()
{
	//getting num of mines around the non-Mine (empty) cells
	for (int c = 0; c < m_column; c++) {
		for (int r = 0; r < m_row; r++) {
			if (m_realBoardLayout[r][c].getMineCell() == false) 
			{
				int numMines = countSuroundingMines(r, c);
				m_realBoardLayout[r][c].setNumberCell(numMines);
			}
		}
	}
}

bool Minesweeper::isValidCoord(int inRow, int inCol)
{
	bool coordValidation = true;
	if ((inRow < 0) || (inRow > (m_row - 1))) {
		coordValidation = false;
	}

	if (inCol < 0 || inCol > (m_column - 1)) {
		coordValidation = false;
	}
	return coordValidation;
}

bool Minesweeper::isMine(int inRow, int inCol)
{
	bool isMine = false;
	if (isValidCoord(inRow, inCol)) {
		if (m_realBoardLayout[inRow][inCol].getMineCell() == true) {
			isMine = true;
		}
	}
	return isMine;
}

bool Minesweeper::isFlagged(int inRow, int inCol)
{
	bool isFlagged = false;
	if (isValidCoord(inRow, inCol)) {
		if (m_realBoardLayout[inRow][inCol].getFlaggedCell() == true) {
			isFlagged = true;
		}
	}
	return isFlagged;
}

bool Minesweeper::isCovered(int inRow, int inCol)
{
	bool isCovered = false;
	if (isValidCoord(inRow, inCol)) {
		if (m_realBoardLayout[inRow][inCol].getCoveredCell() == true) {
			isCovered = true;
		}
	}
	return isCovered;
}

void Minesweeper::uncoverCell(int inRow, int inCol)
{
	if (isValidCoord(inRow, inCol)) {
		if (m_realBoardLayout[inRow][inCol].getMineCell() == false) {
			m_realBoardLayout[inRow][inCol].setCoveredCell(false);
		}
	}
}

void Minesweeper::checkGameStatus()
{
	if (checkWin()) {
		cout << "Congratulations, YOU WIN!!!" << endl;
	}
	else if (m_validGame == false) {
		cout << "Sorry, YOU LOST!" << endl << endl;
	}
}

bool Minesweeper::checkWin()
{
	bool win = false;
	if (m_validGame == true) {
		if (countFlaggedMines() == m_minesNum) {
			int numBadFlags = 0;
			for (int row = 0; row < m_row - 1; row++) {
				for (int col = 0; col < m_column - 1; col++) {
					if (isFlagged(row, col) && (isMine(row, col) == false)) {
						numBadFlags++;
					}
				}
			}

			if (numBadFlags == 0) {
				win = true;
				m_validGame = false;
			}
		}
	}
	return win;
}

#endif