#ifndef ARRAY2DP_H
#define ARRAY2DP_H

#include <iostream>
#include <wchar.h>
#include "stdafx.h"
#include "targetver.h"
#include "Row.h"
#include "Exception.h"

using namespace std;

template <typename T>
class Row;

template <typename T>
class Array2DP
{
public:
	Array2DP();
	Array2DP(int inRow, int inCol);
	Array2DP(const Array2DP & inCopy);
	~Array2DP();
public:
	Array2DP & operator=(const Array2DP & inRhs);
	Row<T> operator[](int inIndex);
public:
	int getRow() const;
	void downsizingRow(int inRow);
	void upsizingRow(int inRow);
	void setRow(int inRow);
	int getColumn() const;
	void downsizingColumn(int inCol);
	void upsizingColumn(int inCol);
	void setColumn(int inCol);
public:
	T & Select(int inRow, int inCol) const;
	T** newArray(int inRow, int inCol);
	T** deleteArray(T** &inArray, int inRow);
	void copyArray(T** &inArraySrc, T** &inArrayDest, int inRow, int inCol);

private:
	T * * m_array;
	int m_row;
	int m_col;
};

template<typename T>
inline Array2DP<T>::Array2DP()
{
	m_row = 0;
	m_col = 0;
	m_array = nullptr;
}

template<typename T>
inline Array2DP<T>::Array2DP(int inRow, int inCol) 
	: m_row(inRow), m_col(inCol)
{
	//takes in 1 based index values
	if (inRow > 0 && inCol > 0) {
		m_array = new T*[inRow];
		for (int i = 0; i < m_row; i++) {
			m_array[i] = new T[m_col]();
		}
	}
	else {
		throw Exception("Exception caught: Length must be greater than 0.");
	}
}

template<typename T>
inline Array2DP<T>::Array2DP(const Array2DP & inCopy)
{
	if (m_array != nullptr) {
		for (int i = 0; i < m_row; ++i) {
			delete[] m_array[i];
		}
		delete[] m_array;
	}

	this->setRow(inCopy.getRow());
	this->setColumn(inCopy.getColumn());
	m_array = new T*[m_col];
	for (int r = 0; r < m_row; r++) {
		m_array[r] = new T[m_col];
		for (int c = 0; c < m_col; c++) {
			m_array[r][c] = inCopy.m_array[r][c];
		}
	}
}

template<typename T>
inline Array2DP<T>::~Array2DP()
{
	if (m_array != nullptr) {
		for (int r = 0; r < m_row; r++) {
			delete[] m_array[r];
		}
		delete[] m_array;
		m_array = nullptr;
	}
}

template<typename T>
inline Array2DP<T> & Array2DP<T>::operator=(const Array2DP & inRhs)
{
	if (m_array != nullptr) {
		for (int r = 0; r < m_row; r++) {
			delete[] m_array[r];
		}
	}
	delete[] m_array;

	this->setRow(inRhs.getRow());
	this->setColumn(inRhs.getColumn());
	
	for (int r = 0; r < m_row; r++) {
		for (int c = 0; c < m_col; c++) {
			m_array[r][c] = inRhs.Select(r,c);
		}
	}
	return *this;
}

template<typename T>
inline Row<T> Array2DP<T>::operator[](int inIndex)
{
	//expects to receive a 0 based index
	if (inIndex < 0) {
		throw Exception("Exception caught: Indexes must be greater than 0.");
	}
	else if (inIndex >= m_col) {
		throw Exception("Exception caught: Index specified is larger than the column bound.");
	}
	return Row<T>(*this, inIndex);
}

template<typename T>
inline int Array2DP<T>::getRow() const
{
	return m_row;
}

template<typename T>
inline void Array2DP<T>::downsizingRow(int inRow)
{
	//copy mArray into a temporary Array.
	T** tempArray = newArray(m_row, m_col);
	copyArray(m_array, tempArray, m_row, m_col);
	m_array = deleteArray(m_array, m_row);

	//copy only the downsized values from temporary back to m_array
	m_array = newArray(inRow, m_col);
	copyArray(tempArray, m_array, inRow, m_col);
	tempArray = deleteArray(tempArray, m_col);

	m_row = inRow;
}

template<typename T>
inline void Array2DP<T>::upsizingRow(int inRow)
{
	//copy mArray into a temporary Array.
	T** tempArray = newArray(m_row, m_col);
	copyArray(m_array, tempArray, m_row, m_col);
	m_array = deleteArray(m_array, m_row);

	//copy only the upsized values from temporary back to m_array
	m_array = newArray(inRow, m_col);
	copyArray(tempArray, m_array, m_row, m_col);
	tempArray = deleteArray(tempArray, m_row);

	m_row = inRow;
}

template<typename T>
inline void Array2DP<T>::setRow(int inRow)
{
	if (inRow <= 0) {
		throw Exception("Length must be greater than 0.");
	}
	else if (inRow < m_row) {	//downsizing
		downsizingRow(inRow);
	}
	else if (inRow > m_row) {	//upsizing
		upsizingRow(inRow);
	}
}

template<typename T>
inline int Array2DP<T>::getColumn() const
{
	return m_col;
}

template<typename T>
inline T** Array2DP<T>::newArray(int inRow, int inCol)
{
	T ** outArray = new T*[inRow];
	for (int i = 0; i < inRow; i++) {
		outArray[i] = new T[inCol]();
	}
	return outArray;
}

template<typename T>
inline void Array2DP<T>::copyArray(T** &inArraySrc, T** &inArrayDest, int inRow, int inCol)
{
	for (int r = 0; r < inRow; r++) {
		for (int c = 0; c < inCol; c++) {
			inArrayDest[r][c] = inArraySrc[r][c];
		}
	}
}

template<typename T>
inline T** Array2DP<T>::deleteArray(T** &inArray, int inRow)
{
	for (int j = 0; j < inRow; j++) {
		delete[] inArray[j];
	}
	delete[] inArray;

	return nullptr;
}

template<typename T>
inline void Array2DP<T>::downsizingColumn(int inCol)
{
	//copy mArray into a temporary Array.
	T** tempArray = newArray(m_row, m_col);
	copyArray(m_array, tempArray, m_row, m_col);
	m_array = deleteArray(m_array, m_row);

	//copy only the subset of values
	m_array = newArray(m_row, inCol);
	copyArray(tempArray, m_array, m_row, inCol);
	tempArray = deleteArray(tempArray, m_row);

	m_col = inCol;
}

template<typename T>
inline void Array2DP<T>::upsizingColumn(int inCol)
{
	//copy mArray into a temporary Array.
	T** tempArray = newArray(m_row, m_col);
	copyArray(m_array, tempArray, m_row, m_col);
	m_array = deleteArray(m_array, m_row);

	//copy only the upsized values from temporary back to m_array
	m_array = newArray(m_row, inCol);
	copyArray(tempArray, m_array, m_row, m_col);
	tempArray = deleteArray(tempArray, m_row);

	m_col = inCol;
}

template<typename T>
inline void Array2DP<T>::setColumn(int inCol)
{
	if (inCol <= 0) {
		throw Exception("Length must be greater than 0.");
	}
	else if (inCol < m_col) {	//downsizing
		downsizingColumn(inCol);
	}
	else if (inCol > m_col) {	//upsizing
		upsizingColumn(inCol);
	}
}

template<typename T>
inline T & Array2DP<T>::Select(int inRow, int inCol) const
{
	//Zero based index value.
	return m_array[inRow][inCol];
}

#endif