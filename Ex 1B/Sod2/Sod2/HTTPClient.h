#include "stdafx.h"
#include "windows.h"
#include "winhttp.h"
#include "HTTPAutoHandle.h"

class HTTPClient
{
public:
	HTTPClient(LPCWSTR pswzServerName, INTERNET_PORT nServerPort);
	~HTTPClient();
	char* sendGet();
	char* sendPost();

private:
	DWORD dwSize = 0;
	DWORD dwDownloaded = 0;
	LPSTR pszOutBuffer;
	BOOL bResults = FALSE;
	HINTERNET  hSession = NULL,
		hConnect = NULL,
		hRequest = NULL;
};
