#include "pch.h"
#include <iostream>
#include <chrono>
#include "Request.h"
#include "Json.h"

using namespace EzRequest;

int main()
{
	Json json;
	Request req;

	string data = json.serialize(map<string, string>({
		{
			"username", "test"
		},
		{
			"password", "testing"
		}
	}));

	if (req.postBody("http://91.188.223.109/v2/user/login.php", data) != REQUEST_EXCEPTION)
	{
		printf("%s", req.getResponse().c_str());
	}
}
