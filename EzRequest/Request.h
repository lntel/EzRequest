#pragma once
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <map>
#include <stdlib.h>
#include "Enums.h"
#include "Structs.h"

#pragma comment(lib, "Ws2_32.lib")

namespace EzRequest {
	class Request {
	private:

		int iResult;
		string sendBuffer;

		WSADATA wsaData;
		SOCKET client = INVALID_SOCKET;
		struct addrinfo *result = NULL,
						*ptr = NULL,
						hints;

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

		int createRequest(ParsedHost ph, Verb verb, string contentType, string data)
		{
			if (verb == POST)
			{
				sendBuffer += "POST " + ph.uri + " HTTP/1.1\r\n";
				sendBuffer += "Host: " + ph.host + "\r\n";
				sendBuffer += "Content-Type: " + contentType + "\r\n";
				sendBuffer += "Content-Length: " + to_string(sizeof(data)) + "\r\n";
				sendBuffer += "Connection: close\r\n";
				sendBuffer += "\r\n";
				sendBuffer += data;

				return 0;
			}
		}

		int initialize()
		{
			iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);

			return iResult;
		}

		unsigned int getResponseCode()
		{
			string response = readBuffer;

			int n = response.find(' ');

			unsigned int x = atoi(response.substr(n + 1, 3).c_str());

			return x;
		}

	public:

		char readBuffer[4096];
		int status;

		int postBody(string url, string json)
		{
			ParsedHost ph;

			ph = parseUrl(url);

			if (initialize() != 0)
			{
				printf("WSAStartup error occured");
				return WSA_EXCEPTION;
			}

			hints.ai_family = AF_INET;
			hints.ai_socktype = SOCK_STREAM;
			hints.ai_protocol = IPPROTO_TCP;

			iResult = getaddrinfo(ph.host.c_str(), "80", &hints, &result);
			if (iResult != 0)
			{
				printf("Unable to resolve hostname");
				WSACleanup();
				return -1;
			}

			ptr = result;

			client = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
			if (client == INVALID_SOCKET)
			{
				printf("Socket creation error: %d", WSAGetLastError());
				WSACleanup();
				return -1;
			}

			if (createRequest(ph, POST, "application/json", json) == -1)
			{
				printf("Unable to create the HTTP request!");
				closesocket(client);
				WSACleanup();
				return -1;
			}

			iResult = connect(client, ptr->ai_addr, ptr->ai_addrlen);
			if (iResult == SOCKET_ERROR)
			{
				printf("Connection could not be established: %d", WSAGetLastError());
				closesocket(client);
				WSACleanup();
				return -1;
			}

			iResult = send(client, sendBuffer.c_str(), (int)strlen(sendBuffer.c_str()), 0);
			if (iResult == SOCKET_ERROR)
			{
				printf("Socket unable to send data: %d", WSAGetLastError());
				closesocket(client);
				WSACleanup();
				return -1;
			}

			iResult = recv(client, readBuffer, sizeof(readBuffer), 0);
			if (iResult == SOCKET_ERROR)
			{
				printf("Socket was unable to recieve data: %d", WSAGetLastError());
				closesocket(client);
				WSACleanup();
				return -1;
			}

			if (iResult > 0)
			{
				status = getResponseCode();
			}

			return 0;
		}

		string getResponse()
		{
			string temp = readBuffer;

			int n = temp.find('{');

			return temp.substr(n);
		}

	};

}