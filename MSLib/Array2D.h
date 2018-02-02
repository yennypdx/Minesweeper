#ifndef ARRAY2D_H
#define ARRAY2D_H

#include <iostream>
#include <wchar.h>
#include "stdafx.h"
#include "targetver.h"
#include "Array.h"
#include "Row.h"
#include "Exception.h"

using namespace std;

template <typename T>
class Array;

template <typename T>
class Row;

template <typename T>
class Array2D
{
public:
	Array2D();
	Array2D(int inRow, int inCol);
	Array2D(const Array2D & inCopy);
	~Array2D();
public:
	Array2D & operator=(const Array2D & inRhs);
	Row<T> operator[](int inIndex);
public:
	int getRow();
	void setRow(int inRow);
	int getColumn();
	void setColumn(int inCol);
	T & Select(int inRow, int inCol);

private:
	Array<T> m_array2d;
	int m_row;
	int m_col;
};

template<typename T>
Array2D<T>::Array2D()
{
	m_array2d = Array<T>();
	m_row = 0;
	m_col = 0;
}

template<typename T>
Array2D<T>::Array2D(int inRow, int inCol) : 
	m_row(inRow), m_col(inCol), m_array2d(inRow*inCol)
{
	if (inRow > 0 || inCol > 0) {
		for (int i = 0; i < m_row; i++) {
			m_array2d[i];
		}

		for (int i = 0; i < m_col; i++) {
			m_array2d[i];
		}
	}
	else if (inRow == 0 || inCol == 0) {
		throw Exception("Exception caught: Length must be greater than 0.");
	}
	else {
		throw Exception("Exception caught: Length must be greater than 0.");
	}
}

template<typename T>
Array2D<T>::Array2D(const Array2D & inCopy)
{
	m_row = inCopy.m_row;
	m_col = inCopy.m_col;
	m_array2d = inCopy.m_array2d;
}

template<typename T>
Array2D<T>::~Array2D()
{}

template<typename T>
Array2D<T> & Array2D<T>::operator=(const Array2D & inRhs)
{
	if (this != &inRhs) {
		m_col = inRhs.m_col;
		m_row = inRhs.m_row;
		m_array2d = inRhs.m_array2d;
	}
	return *this;
}

template<typename T>
Row<T> Array2D<T>::operator[](int inIndex)
{
	if (inIndex < 0) {
		throw Exception("Exception caught: Indexes must be greater than 0.");
	}
	else if (inIndex = 0) {
		throw Exception("Exception caught: Indexes must be greater than 0.");
	}
	else if (inIndex >= m_col - 1) {
		throw Exception("Exception caught: Index specified is larger than the column bound.");
	}
	return Row<T>(*this, inIndex);
}

template<typename T>
int Array2D<T>::getRow()
{
	return m_row;
}

template<typename T>
void Array2D<T>::setRow(int inRow)
{
	m_row = inRow;
}

template<typename T>
int Array2D<T>::getColumn()
{
	return m_col;
}

template<typename T>
void Array2D<T>::setColumn(int inCol)
{
	m_col = inCol;
}

template<typename T>
T& Array2D<T>::Select(int inRow, int inCol)
{
	return m_array2d[(inRow*m_col), inCol];
}

#endif