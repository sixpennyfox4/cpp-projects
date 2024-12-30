#include <iostream>
#include <Windows.h>
#include <string>

using namespace std;

int main() {
	string windowName{};
	LPVOID addr{};
	int newV{};
	char option{};
	
	cout << "Read(r)/Write(w): ";
	cin >> option;

	if (option != 'r' && option != 'w') {
		cout << "Option not found!";

		Sleep(3000);
		exit(-1);
	}

	cout << "Window name: ";
	getline(cin >> ws, windowName);

	HWND hwnd{ FindWindowA(NULL, (LPCSTR)windowName.c_str()) };

	if (hwnd == NULL) {
		cout << "Window not found!";

		Sleep(3000);
		exit(-1);
	}
	else {
		cout << "Address: ";
		cin >> addr;

		if (option == 'w') {
			cout << "New value: ";
			cin >> newV;
		}

		DWORD procID{};
		GetWindowThreadProcessId(hwnd, &procID);

		HANDLE handle{ OpenProcess(PROCESS_ALL_ACCESS, false, procID) };

		if (procID == NULL) {
			cout << "Could not find process!";

			Sleep(3000);
			exit(-1);
		}
		else {
			if (option == 'w') {
				WriteProcessMemory(handle, addr, &newV, sizeof(newV), 0);
				cout << "Memory has been written!";

				Sleep(10000);
			}
			else if (option == 'r') {
				int readedVal{};
				ReadProcessMemory(handle, (PBYTE*)addr, &readedVal, sizeof(readedVal), 0);

				cout << "Readed value: " << readedVal;
				Sleep(10000);
			}
			else {
				cout << "Option not found!";

				Sleep(3000);
				exit(-1);
			}
		}
	}

	return 0;
}
