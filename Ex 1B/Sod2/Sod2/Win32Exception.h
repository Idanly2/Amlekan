#pragma once
#include <exception>

class Win32Exception : std::exception
{
public:
	Win32Exception(int errorCode);
	~Win32Exception();

	virtual const char* what() const throw();

private:
	int errorCode;
};

