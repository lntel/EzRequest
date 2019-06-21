#pragma once
#include "pch.h"

using namespace std;

namespace EzRequest {

	class Json {
	public:

		string serialize(map<string, string> data)
		{
			string _d;

			_d = "{";

			map<string, string>::iterator it;

			for (it = data.begin(); it != data.end(); ++it)
			{
				if (it == prev(data.end()))
				{
					_d += "\"" + it->first + "\": \"" + it->second + "\"}";
					break;
				}

				_d += "\"" + it->first + "\": \"" + it->second + "\", ";
			}

			return _d;
		}

	};

}