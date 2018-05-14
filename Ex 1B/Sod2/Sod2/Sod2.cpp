// Sod2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include "winhttp.h"
#include "HTTPAutoHandle.h"
#include <string>
#include <iostream>

std::string getRequest() {
	//
	// Should be handled by class
	//

	HINTERNET  hSession = NULL,
		hConnect = NULL;

	// Use WinHttpOpen to obtain a session handle.
	hSession = WinHttpOpen(L"WinHTTP Example/1.0",
		WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
		WINHTTP_NO_PROXY_NAME,
		WINHTTP_NO_PROXY_BYPASS, 0);


	// Specify an HTTP server.
	if (hSession)
	{
		hConnect = WinHttpConnect(hSession, L"localhost",
			INTERNET_DEFAULT_HTTP_PORT, 0);
	}

	HTTPAutoHandle sessionHandle = HTTPAutoHandle(hSession);

	//
	// The actual request starts here
	//

	LPSTR pszOutBuffer;
	BOOL bResults = FALSE;
	DWORD dwDownloaded = 0;
	HINTERNET hRequest = NULL;
	DWORD dwSize = 0;
	std::string results = "";

	// Create an HTTP request handle.
	if (hConnect)
	{
		hRequest = WinHttpOpenRequest(hConnect, L"GET", NULL,
			NULL, WINHTTP_NO_REFERER,
			WINHTTP_DEFAULT_ACCEPT_TYPES,
			WINHTTP_FLAG_REFRESH);

	}
	HTTPAutoHandle connectHandle = HTTPAutoHandle(hConnect);


	// Send a request.
	if (hRequest)
	{
		bResults = WinHttpSendRequest(hRequest,
			WINHTTP_NO_ADDITIONAL_HEADERS, 0,
			WINHTTP_NO_REQUEST_DATA, 0,
			0, 0);
	}
	HTTPAutoHandle requestHandle = HTTPAutoHandle(hRequest);

	// End the request.
	if (bResults) {
		bResults = WinHttpReceiveResponse(hRequest, NULL);
	}

	// Keep checking for data until there is nothing left.
	if (bResults)
	{
		do
		{
			// Check for available data.
			dwSize = 0;
			if (!WinHttpQueryDataAvailable(hRequest, &dwSize)) {
				//TODO create win32error ("Error %u in WinHttpQueryDataAvailable.\n", GetLastError());
			}

			// Allocate space for the buffer.
			pszOutBuffer = new char[dwSize + 1];
			if (!pszOutBuffer)
			{
				printf("Out of memory\n");
				dwSize = 0;
			}
			else
			{
				// Read the data.
				ZeroMemory(pszOutBuffer, dwSize + 1);

				if (!WinHttpReadData(hRequest, (LPVOID)pszOutBuffer,
					dwSize, &dwDownloaded)) {
					//TODO create win32error ("Error %u in WinHttpReadData.\n", GetLastError())
				}
				else {
					// the buffer was filled with data
					results = results + std::string(pszOutBuffer);
					//results = results + std::string(pszOutBuffer);
				}

				// Free the memory allocated to the buffer.
				delete[] pszOutBuffer;
			}
		} while (dwSize > 0);
	}

	// Report any errors.
	if (!bResults)
	{
		// no results
		//TODO win32error ("Error %d has occurred.\n", GetLastError())

	}
	return results;
}

int main()
{	
	std::cout << getRequest() << std::endl;

    return 0;
}

