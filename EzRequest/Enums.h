#pragma once

enum STATE {
	WSA_EXCEPTION = 1,
	REQUEST_EXCEPTION = 1,
	HTTP_RESPONSE_OK = 200,
	HTTP_RESPONSE_FORBIDDEN = 403,
	HTTP_RESPONSE_UNAUTHORISED = 401
};

enum Verb {
	POST,
	GET
};