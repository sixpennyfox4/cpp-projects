#include <iostream>
#include <Windows.h>

int main() {
	while (true) {
		Sleep(50);

		if (GetAsyncKeyState(VK_F6)) {
			INPUT input = { 0 };
			input.type = INPUT_MOUSE;
			input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
			SendInput(1, &input, sizeof(input));

			ZeroMemory(&input, sizeof(input));

			input.type = INPUT_MOUSE;
			input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
			SendInput(1, &input, sizeof(input));
		}

		/* KEYBOARD AUTOCLICK (change 'd' to the key you want)
  		if (GetAsyncKeyState(VK_F7)) {
			INPUT input = { 0 };
			input.type = INPUT_KEYBOARD;
			input.ki.wVk = VkKeyScanA('d');
			SendInput(1, &input, sizeof(input));

			ZeroMemory(&input, sizeof(input));

			input.ki.dwFlags = KEYEVENTF_KEYUP;
			SendInput(1, &input, sizeof(input));
		}*/
	}

	return 0;
}
