#include "HTTPClient.h"
#include "stdafx.h"
#include "windows.h"
#include "winhttp.h"
#include "HTTPAutoHandle.h"


HTTPClient::HTTPClient(LPCWSTR pswzServerName, INTERNET_PORT nServerPort)
{
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
		HTTPAutoHandle connectHandle = HTTPAutoHandle(hConnect);
	}
	
}


HTTPClient::~HTTPClient()
{
}

char* HTTPClient::sendGet()
{
	if (hConnect)
	{
		hRequest = WinHttpOpenRequest(hConnect, L"GET", NULL,
			NULL, WINHTTP_NO_REFERER,
			WINHTTP_DEFAULT_ACCEPT_TYPES,
			WINHTTP_FLAG_REFRESH);

	}
	HTTPAutoHandle requestHandle = HTTPAutoHandle(hRequest);
}

char* HTTPClient::sendPost()
{
	if (hConnect)
	{
		hRequest = WinHttpOpenRequest(hConnect, L"POST", NULL,
			NULL, WINHTTP_NO_REFERER,
			WINHTTP_DEFAULT_ACCEPT_TYPES,
			WINHTTP_FLAG_REFRESH);

	}
	HTTPAutoHandle requestHandle = HTTPAutoHandle(hRequest);
}

