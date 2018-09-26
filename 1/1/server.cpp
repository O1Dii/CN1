#include <winsock2.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

long Nod(long a, long b)
{
	while (a && b)
		if (a >= b)
			a -= b;
		else
			b -= a;
	return a | b;
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(2, 2);
	WSAStartup(wVersionRequested, &wsaData);
	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_port = htons(1717);
	local.sin_addr.s_addr = htonl(INADDR_ANY);
	int c = bind(s, (struct sockaddr*) &local, sizeof(local)), r = listen(s, 5);
	char res[100], b[255], *Res;
	sockaddr_in remote_addr;
	int size = sizeof(remote_addr);
	int i, num, num1, num2;
	while (true) {
		SOCKET s2 = accept(s, (struct sockaddr*) &remote_addr, &size);
		while (recv(s2, b, sizeof(b), 0) != 0) {
			num = num2 = num1 = 0;
			for (i = 0; b[i] != '+'; i++) {
				num1 *= 10;
				num1 += (int)b[i] - 48;
			}
			i++;
			while (b[i] != '\0') {
				num2 *= 10;
				num2 += (int)b[i] - 48;
				i++;
			}
			num = Nod(num1, num2);
			_itoa_s(num, res, 10);
			int n = strlen(res) + 1;
			Res = new char[n];
			strcpy_s(Res, n, res);
			n = sizeof(res);
			send(s2, Res, n, 0);
			if (recv(s2, b, sizeof(b), 0) != 0) continue;
		}
		closesocket(s2);
	}
	WSACleanup();
	return 0;
}