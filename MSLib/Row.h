#ifndef ROW_H
#define ROW_H

#include <iostream>
using namespace std;

template<typename T>
class Array2D;

template <typename T>
class Row
{
public:
	Row(Array2D<T> & inArray, int inRow);
	T & operator[](int inColumn);

private:
	Array2D<T> & m_array2D;
	int m_row;
};

template<typename T>
Row<T>::Row(Array2D<T> & inArray, int inRow) : m_array2D(inArray), m_row(inRow) {}

template<typename T>
T & Row<T>::operator[](int inColumn)
{
	return m_array2D.Select(m_row, inColumn);
}

#endif