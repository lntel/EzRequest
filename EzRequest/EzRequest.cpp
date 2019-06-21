#include "pch.h"
#include <iostream>
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

	req.postBody("http://localhost/v2/user/login.php", data);
}
