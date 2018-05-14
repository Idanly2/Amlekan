#include "stdafx.h"
#include "windows.h"
#include "winhttp.h"
#include <string>
#include "HTTPAutoHandle.h"
#include "Win32Exception.h"

class HTTPClient
{
public:
	HTTPClient(LPCWSTR pswzServerName, INTERNET_PORT nServerPort);
	~HTTPClient();
	std::string sendGet();
	std::string sendPost();

private:
	std::string sendRequest(LPCWSTR method);

	HINTERNET  hSession = NULL,
		hConnect = NULL;
	HTTPAutoHandle *connectHandle, *sessionHandle;
};
