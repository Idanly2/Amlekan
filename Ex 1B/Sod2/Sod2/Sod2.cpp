// Sod2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "windows.h"
#include "winhttp.h"
#include "HTTPAutoHandle.h"


int main()
{	
	DWORD dwSize = 0;
	DWORD dwDownloaded = 0;
	LPSTR pszOutBuffer;
	BOOL bResults = FALSE;
	HINTERNET  hSession = NULL,
		hConnect = NULL,
		hRequest = NULL;

	// Use WinHttpOpen to obtain a session handle.
	hSession = WinHttpOpen(L"WinHTTP Example/1.0",
		WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
		WINHTTP_NO_PROXY_NAME,
		WINHTTP_NO_PROXY_BYPASS, 0);
	HTTPAutoHandle sessionHandle = HTTPAutoHandle(hSession);

	// Specify an HTTP server.
	if (hSession)
	{
		hConnect = WinHttpConnect(hSession, L"localhost",
			INTERNET_DEFAULT_HTTP_PORT, 0);
	}
	HTTPAutoHandle connectHandle = HTTPAutoHandle(hConnect);


	// Create an HTTP request handle.
	if (hConnect)
	{
		hRequest = WinHttpOpenRequest(hConnect, L"GET", NULL,
			NULL, WINHTTP_NO_REFERER,
			WINHTTP_DEFAULT_ACCEPT_TYPES,
			WINHTTP_FLAG_REFRESH);

	}
	HTTPAutoHandle requestHandle = HTTPAutoHandle(hRequest);

	// Send a request.
	if (hRequest)
	{
		bResults = WinHttpSendRequest(hRequest,
			WINHTTP_NO_ADDITIONAL_HEADERS, 0,
			WINHTTP_NO_REQUEST_DATA, 0,
			0, 0);
	}

	// End the request.
	if (bResults)
		bResults = WinHttpReceiveResponse(hRequest, NULL);

	// Keep checking for data until there is nothing left.
	if (bResults)
	{
		do
		{
			// Check for available data.
			dwSize = 0;
			if (!WinHttpQueryDataAvailable(hRequest, &dwSize))
				printf("Error %u in WinHttpQueryDataAvailable.\n",
					GetLastError());

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
					dwSize, &dwDownloaded))
					printf("Error %u in WinHttpReadData.\n", GetLastError());
				else
					printf("%s", pszOutBuffer);

				// Free the memory allocated to the buffer.
				delete[] pszOutBuffer;
			}
		} while (dwSize > 0);
	}


	// Report any errors.
	if (!bResults)
	{
		printf("No results :(\n");
		printf("Error %d has occurred.\n", GetLastError());
	}

	// No need because we made an AutoHandle!
	/*
	// Close any open handles.
	if (hRequest) WinHttpCloseHandle(hRequest);
	if (hConnect) WinHttpCloseHandle(hConnect);
	if (hSession) WinHttpCloseHandle(hSession);
	*/

    return 0;
}

