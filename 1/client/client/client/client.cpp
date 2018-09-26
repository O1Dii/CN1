#include <winsock2.h>
#include <Ws2tcpip.h>
#include <iostream> 
#include <stdlib.h>

using namespace std;

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(2, 2);
	WSAStartup(wVersionRequested, &wsaData);
	struct sockaddr_in peer;
	peer.sin_family = AF_INET;
	peer.sin_port = htons(1717);
	inet_pton(AF_INET, "127.0.0.1", &peer.sin_addr);
	SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	connect(s, (struct sockaddr*) &peer, sizeof(peer));
	char buf[255], b[255];
	{
		int j;
		bool flag, b_true = false;
		char a[7];
		cout << "Введите первое число" << endl;
		do {
			flag = false;
			cin.getline(a, _countof(a));
			for (int i = 0; a[i] != '\0' && flag == false; i++)
				if (a[i] < 48 || a[i] > 57) {
					cout << "Неправильно введено значение, повторите ввод" << endl;
					flag = true;
				}
			if (flag == false) {
				if (b_true == true) {
					for (int i = 0; i < a[i] != '\0'; i++, j++)
						buf[j] = a[i];
					buf[j] = '\0';
					flag = false;
				}
				else {
					cout << "Введите второе число" << endl;
					for (j = 0; j < (int)strlen(a); j++)
						buf[j] = a[j];
					buf[j] = '+';
					j++;
					b_true = true;
					flag = true;
				}
			}
		} while (flag == true);
	}
	send(s, buf, sizeof(buf), 0);
	if (recv(s, b, sizeof(b), 0) != 0) {
		b[strlen(b)] = '\0';
		cout << b << endl;
	}
	closesocket(s);
	WSACleanup();
	system("PAUSE");
}