#include <iostream>
#include <Windows.h>
#include <algorithm>
#include <vector>

void notify(const std::wstring& title, const std::wstring& message, const int time) {
	NOTIFYICONDATA nid = {};
	nid.cbSize = sizeof(nid);
	nid.uID = 1;
	nid.uFlags = NIF_INFO;
	nid.hWnd = GetConsoleWindow();
	nid.uCallbackMessage = WM_USER + 1;
	lstrcpy(nid.szInfoTitle, title.c_str());
	lstrcpy(nid.szInfo, message.c_str());
	nid.dwInfoFlags = NIIF_INFO;

	Shell_NotifyIcon(NIM_ADD, &nid);

	Sleep(time * 1000);

	Shell_NotifyIcon(NIM_DELETE, &nid);
}

int main() {
	FreeConsole();
	notify(L"How to turn off", L"To turn off window pinner you need to press f6.", 10);

	std::vector<HWND> wins{};

	while (true) {
		Sleep(30);

		if ((GetAsyncKeyState(VK_LCONTROL) & 0x8000) && (GetAsyncKeyState(VK_LSHIFT) & 0x8000) && (GetAsyncKeyState(VK_LBUTTON) & 0x8000)) {
			HWND topWindow{ GetForegroundWindow() };

			// Checks if the window is already in the windows vector.
			auto it{ std::find(wins.begin(), wins.end(), topWindow) };
			if (it != wins.end()) {
				SetWindowPos(topWindow, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
				wins.erase(it);

				notify(L"Unpinned", L"Unpinned window.", 2);
				Sleep(1000);
				//std::cout << "Removed window\n";
			}
			else {
				SetWindowPos(topWindow, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW);
				wins.push_back(topWindow);

				notify(L"Pinned", L"Pinned window.", 2);
				Sleep(1000);
				//std::cout << "Added window\n";
			}
		}
		else if (GetAsyncKeyState(VK_F6) & 0x8000) {
			notify(L"Turned off", L"Window pinner has been turned off.", 3);
			break;
		}
	}

	return 0;
}
