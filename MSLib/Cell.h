#ifndef CELL_H
#define CELL_H

#include <iostream>
using namespace std;

class Cell
{
public:
	Cell();
	~Cell();
	Cell & operator=(Cell & rhs);
public:
	void setMineCell(bool inVal);
	bool getMineCell();
	void setFlaggedCell(bool inVal);
	bool getFlaggedCell();
	void setCoveredCell(bool inVal);
	bool getCoveredCell();
	void setNumberCell(int inVal);
	int getNumberCell();

private:
	bool m_minecell;
	bool m_flaggedcell;
	bool m_coveredcell;
	int m_numbercell;
};

Cell::Cell()
{
	m_minecell = false;
	m_flaggedcell = false;
	m_coveredcell = true;
	m_numbercell = 0;
}

Cell::~Cell()
{}

Cell & Cell::operator=(Cell & inRhs) {
	if (this != &inRhs) {
		m_minecell = inRhs.getMineCell();
		m_flaggedcell = inRhs.getFlaggedCell();
		m_coveredcell = inRhs.getCoveredCell();
		m_numbercell = inRhs.getNumberCell();
	}
	return *this;
}

void Cell::setMineCell(bool inVal) {
	m_minecell = inVal;
}

bool Cell::getMineCell() {
	return m_minecell;
}

void Cell::setFlaggedCell(bool inVal) {
	m_flaggedcell = inVal;
}

bool Cell::getFlaggedCell() {
	return m_flaggedcell;
}

void Cell::setCoveredCell(bool inVal) {
	m_coveredcell = inVal;
}

bool Cell::getCoveredCell() {
	return m_coveredcell;
}

void Cell::setNumberCell(int inVal) {
	m_numbercell = inVal;
}

int Cell::getNumberCell() {
	return m_numbercell;
}

#endif
