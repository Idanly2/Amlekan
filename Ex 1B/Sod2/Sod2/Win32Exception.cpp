#include "stdafx.h"
#include <string> 
#include "Win32Exception.h"
#include <sstream>

Win32Exception::Win32Exception(int errorCode): errorCode(errorCode)
{
}


Win32Exception::~Win32Exception()
{
}

const char * Win32Exception::what() const throw()
{
	std::ostringstream stringStream;
	stringStream << "Win32Exception with error code: ";
	stringStream << errorCode;
	std::string str = stringStream.str();
	return str.c_str();
}

