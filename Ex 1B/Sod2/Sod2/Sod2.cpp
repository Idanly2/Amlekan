// Sod2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "HTTPClient.h"
#include <string>
#include <iostream>


int main()
{	
	try {
		HTTPClient httpClient(L"localhost", 80);

		std::cout << httpClient.sendPost() << std::endl;
	}
	catch (Win32Exception e) {
		std::cout << e.what() << std::endl;
	}
	
    return 0;
}

