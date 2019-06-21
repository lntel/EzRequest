#pragma once
#include <WinSock2.h>
#include <map>
#include "Structs.h"

#pragma comment(lib, "Ws2_32.lib")

namespace EzRequest {

	class Request {
	private:

		ParsedHost parseUrl(string url)
		{
			ParsedHost _ph;
			int n;

			if (url.substr(0, 7) == "http://") url.erase(0, 7);
			if (url.substr(0, 8) == "https://") url.erase(0, 8);

			n = url.find('/');

			_ph.host = url.substr(0, n);

			if (n != string::npos)
			{
				_ph.uri = url.substr(n, sizeof(url));
			}

			return _ph;
		}

	public:

		int postBody(string url, string json)
		{
			ParsedHost ph;

			ph = parseUrl(url);



			return 0;
		}

	};

}