# EzRequest

## Description

EzRequest is a C++ WinSock2 wrapper which allows you to make HTTP requests using all of the common HTTP verbs (POST, GET). The intended purpose of EzRequest is that it is used for API's. I created this library as I was sick of using libcurl wrappers, therefore, I took a more primitive approach to processing HTTP requests using a library that all Windows machines already have.

## Usage

### Includes

Firstly, you have to include the `Request.h` header file.
```cpp
#include <Request.h>
```
(Optional) If you want to use JSON within your POST body, you will also require the `json.h` and `map` dependency as demonstrated below.
```cpp
#include <Json.h>
#include <map>
```

### Request

The request class must be instantiated in-order to use all the methods, there are no constructor parameters.
```cpp
Request req;
```

### Json Serialization

If you want to use JSON in your POST body, you must first create a map and then pass it as a parameter within the `serialize` method. The Json class requires instantiation as demonstrated below.
```cpp
Json json;

std::string data = json.serialize(std::map<string, string>({
	{
		"username", "test"
	},
	{
		"password", "testing"
	}
}));
```

Within the figure above, `username` is the key and `test` will be the value. You can use as many pairs as you wish and you make a new object by using the curly braces(`{ "key", "value" }`);

### POST Request

There are two types of POST request methods within this library. The first one is `PostJson`, this allows you to POST using a JSON body. The other type of POST allows you to simply use normal POST parameters.

#### PostJson

## Enums

We use enums for returning specific errors and to return the HTTP response code of the HTTP request.
```cpp
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
```
