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
			if (url.substr(0, 7) == "http://") url.erase(0, 7);
			if (url.substr(0, 8) == "https://") url.erase(0, 8);
		}

	public:

	};

}