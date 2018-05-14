#include "stdafx.h"
#include "HTTPAutoHandle.h"

HTTPAutoHandle::HTTPAutoHandle(HINTERNET h): h(h) 
{
	OutputDebugString(L"Constructing an HINTERNET\n");
}

HTTPAutoHandle::~HTTPAutoHandle()
{
	OutputDebugString(L"Destructing an HINTERNET\n");
	if (!h || !WinHttpCloseHandle(h))
	{
		printf("Error %d has occurred in AutoHandle destructor.\n", GetLastError());
	}
}
