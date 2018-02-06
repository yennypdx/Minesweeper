#ifndef ROW_H
#define ROW_H

#include <iostream>
using namespace std;

template<typename T>
class Array2DP;

template <typename T>
class Row
{
public:
	Row(Array2DP<T> & inArray, int inRow);
	T & operator[](int inColumn);

private:
	Array2DP<T> & m_array2DP;
	int m_row;
};

template<typename T>
Row<T>::Row(Array2DP<T> & inArray, int inRow) : m_array2DP(inArray), m_row(inRow) {}

template<typename T>
T & Row<T>::operator[](int inColumn)
{
	//takes in 0 based index
	return m_array2DP.Select(m_row, inColumn);
}

#endif