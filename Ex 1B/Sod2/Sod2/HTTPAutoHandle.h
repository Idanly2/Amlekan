#pragma once

#include "windows.h"
#include "winhttp.h"

class HTTPAutoHandle
{
private:
	HINTERNET h;
public:
	HTTPAutoHandle(HINTERNET h);
	~HTTPAutoHandle();
};

