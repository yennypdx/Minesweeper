#pragma once
#ifndef ARRAY_H
#define ARRAY_H

#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdlib.h>
#include "Exception.h"

using namespace std;

template <typename T>
class Array
{
public:
	Array();
	Array(int inLength, int inStartIdx = 0);
	Array(const Array & inCopy);
	~Array();
public:
	Array & operator=(const Array & inRhs);
	Array & operator<<(const Array & oStream);
	T & operator[](int inIndex);
public:
	int getStartIndex();
	int getStartIndex() const;
	void setStartIndex(int inStartIndex);
	int getLength();
	int getLength() const;
	void downsizing(int inVal);
	void upsizing(int inVal);
	void setLength(int inLength);

private:
	T * m_array;
	int m_length;
	int m_startIndex;
};

template<typename T>
inline Array<T>::Array()
{
	m_array = NULL;
	m_length = 0;
	m_startIndex = 0;
}

template<typename T>
inline Array<T>::Array(int inLength, int inStartIndex)
	:m_length(inLength), m_startIndex(inStartIndex)
{
	if (inLength > 0) {
		m_array = new T[inLength];
		for (int i = 0; i < inLength; i++) {
			m_array[i];
		}
	}
	else {
		throw Exception("Exception caught: Length must be greater than 0.");
	}
}

template<typename T>
inline Array<T>::Array(const Array & inCopy)
{
	m_length = inCopy.m_length;
	m_startIndex = inCopy.m_startIndex;
	m_array = new T[m_length];

	for (int i = 0; i < m_length; i++) {
		m_array[i] = inCopy.m_array[i];
	}
}

template<typename T>
inline Array<T>::~Array()
{
	delete[] m_array;
	m_array = nullptr;
}

template<typename T>
inline Array<T> & Array<T>::operator=(const Array<T> & inRhs)
{
	if (this != &inRhs) {
		delete[] m_array;
		m_length = inRhs.m_length;
		m_startIndex = inRhs.m_startIndex;
		m_array = new T[m_length];
		for (int i = 0; i < m_length; i++) {
			m_array[i] = inRhs.m_array[i];
		}
	}
	return *this;
}

template<typename T>
inline Array<T> & Array<T>::operator<<(const Array<T> & oStream)
{
	return oStream;
}

template<typename T>
inline T & Array<T>::operator [] (int inIndex)
{
	int updatedInIndex = inIndex;

	if (updatedInIndex < m_startIndex) {
		throw Exception("Exception caught: Index specified is smaller than the lower bound.");
	}
	else if (updatedInIndex > m_length - 1) {
		throw Exception("Exception caught: Index specified is larger than the upper bound.");
	}
	else if (updatedInIndex >= m_length - 1 && updatedInIndex <= m_startIndex) {
		updatedInIndex = inIndex - m_startIndex;
	}
	return m_array[updatedInIndex];
}

template<typename T>
inline int Array<T>::getStartIndex()
{
	return m_startIndex;
}

template<typename T>
inline int Array<T>::getStartIndex() const
{
	return m_startIndex;
}

template<typename T>
inline void Array<T>::setStartIndex(int inStartIndex)
{
	m_startIndex = inStartIndex;
}

template<typename T>
inline int Array<T>::getLength()
{
	return m_length;
}

template<typename T>
inline int Array<T>::getLength() const
{
	return m_length;
}

template<typename T>
inline void Array<T>::downsizing(int inVal)
{
	T * copyArray = new T[inVal];
	for (int i = 0; i < inVal; i++) {
		copyArray[i] = i;
	}

	for (int i = 0; i < inVal; i++)
	{
		copyArray[i] = m_array[i];
	}

	m_length = inVal;
	delete[] m_array;
	m_array = copyArray;
	copyArray = nullptr;
}

template<typename T>
inline void Array<T>::upsizing(int inVal)
{
	T * copyArray = new T[inVal];
	for (int i = 0; i < inVal; i++) {
		copyArray[i] = i;
	}

	for (int i = 0; i < m_length; i++)
	{
		copyArray[i] = m_array[i];
	}

	m_length = inVal;
	delete[] m_array;
	m_array = copyArray;
	copyArray = nullptr;
}

template<typename T>
inline void Array<T>::setLength(int inLength)
{
	if (inLength < m_length) {	//downsizing
		downsizing(inLength);
	}
	else if (inLength > m_length) {	//upsizing
		upsizing(inLength);
	}
	else if (inLength <= 0) {
		throw Exception("Exception caught: Length must be greater than 0.");
	}
}

#endif
