#include <Windows.h>

int main() {

	while (true) {
		Sleep(30);

		if (GetAsyncKeyState(VK_LMENU) & 0x8000 && GetAsyncKeyState(VK_F5)) {
			HWND focusedWindow{ GetForegroundWindow() };

			DWORD PID;
			GetWindowThreadProcessId(focusedWindow, &PID);

			HANDLE hProc{ OpenProcess(PROCESS_TERMINATE, FALSE, PID) };

			TerminateProcess(hProc, 0);
			CloseHandle(hProc);

			Sleep(1000);
		}
	}

	return 0;
}
