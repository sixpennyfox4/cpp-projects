#include <iostream>
#include <Windows.h>

void desktopNotify(const std::wstring& title, const std::wstring& message, const int time) {
	NOTIFYICONDATA nid{};
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
	desktopNotify(L"Running!", L"Running in the background. To stop press F6!", 5);

	POINT lMousePos;
	bool toggle{ false };

	GetCursorPos(&lMousePos);
	while (true) {
		Sleep(10);

		HWND robloxWin{ FindWindow(NULL, L"Roblox") };
		HWND focusedWin{ GetForegroundWindow() };

		if (GetAsyncKeyState(VK_F6)) break;
		if (!robloxWin) continue;

		if (GetAsyncKeyState(VK_RBUTTON) && focusedWin == robloxWin)
			toggle = true;
		else
			toggle = false;

		if (toggle) {
			SetCursorPos(lMousePos.x, lMousePos.y);
		}
		else {
			GetCursorPos(&lMousePos);
		}
	}

	desktopNotify(L"Exiting!", L"Exiting the program.", 4);
	return 0;
}
