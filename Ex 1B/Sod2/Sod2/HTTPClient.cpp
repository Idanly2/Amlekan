#include "stdafx.h"
#include "HTTPClient.h"
#include "windows.h"
#include "winhttp.h"

HTTPClient::HTTPClient(LPCWSTR pswzServerName, INTERNET_PORT nServerPort)
{
	// Use WinHttpOpen to obtain a session handle.
	hSession = WinHttpOpen(L"WinHTTP Example/1.0",
		WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
		WINHTTP_NO_PROXY_NAME,
		WINHTTP_NO_PROXY_BYPASS, 0);
	 sessionHandle = new HTTPAutoHandle(hSession);

	
	// Specify an HTTP server.
	if (!hSession)
	{
		throw Win32Exception(GetLastError());
	} 

	hConnect = WinHttpConnect(hSession, pswzServerName,
		nServerPort, 0);
	connectHandle = new HTTPAutoHandle(hConnect);

	if (!hConnect)
	{
		throw Win32Exception(GetLastError());
	}
}


HTTPClient::~HTTPClient()
{
	delete connectHandle, sessionHandle;
}

std::string HTTPClient::sendGet()
{
	return sendRequest(L"GET");
}

std::string HTTPClient::sendPost()
{
	return sendRequest(L"POST");
}

std::string HTTPClient::sendRequest(LPCWSTR method)
{
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
		hRequest = WinHttpOpenRequest(hConnect, method, NULL,
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

