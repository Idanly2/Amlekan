#include "stdafx.h"
#include <string> 
#include "Win32Exception.h"


Win32Exception::Win32Exception(int errorCode): errorCode(errorCode)
{
}


Win32Exception::~Win32Exception()
{
}

const char * Win32Exception::what() const throw()
{
	char integer_string[32];
	sprintf(integer_string, "%d", errorCode);
	char other_string[64] = "Win32Exception with error code: ";
	return strcat(other_string, integer_string);
}

