#pragma once

#ifndef EXCEPTION_H
#define EXCEPTION_H
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

class Exception
{
public:
	Exception();
	Exception(const char * inMsg);
	Exception(const Exception & inCopy);
	~Exception();
public:
	const char * getMessage();
	void setMessage(char *inMsg);
public:
	Exception & operator=(const Exception & inRhs);
	friend ostream & operator<<(ostream & inStream, const Exception & inExcept);

private:
	char * m_msg;
	size_t size;
};

inline Exception::Exception() {}

inline Exception::Exception(const char * inMsg)
{
	size = strlen(inMsg);
	m_msg = new char[size + 1];
	strcpy_s(m_msg, size + 1, inMsg);
}

inline Exception::Exception(const Exception & inCopy)
{
	size = inCopy.size;
	m_msg = new char[size + 1];
	strcpy_s(m_msg, size + 1, inCopy.m_msg);
}

inline Exception::~Exception()
{
	delete[] m_msg;
}

inline const char * Exception::getMessage()
{
	return m_msg;
}

inline void Exception::setMessage(char * inMsg)
{
	*m_msg = *inMsg;
}

inline Exception & Exception::operator=(const Exception & inRhs)
{
	return *this;
}

inline ostream & operator<<(ostream & inStream, Exception & inExcept)
{
	inStream << inExcept.getMessage();
	return inStream;
}

#endif