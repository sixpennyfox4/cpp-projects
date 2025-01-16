#include <iostream>
#include <Windows.h>
#include <string>

void injectDLL(const DWORD PID, const std::string& dllPath) {
	HANDLE hProcess{ OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID) };
	void* allocateMemory{ VirtualAllocEx(hProcess, nullptr, dllPath.size() + 1, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE) };

	WriteProcessMemory(hProcess, allocateMemory, dllPath.c_str(), dllPath.size() + 1, nullptr);

	FARPROC lLA{ GetProcAddress(GetModuleHandleA("kernel32.dll"), "LoadLibraryA") };
	HANDLE hThread{ CreateRemoteThread(hProcess, nullptr, 0, (LPTHREAD_START_ROUTINE)lLA, allocateMemory, 0, nullptr) };

	WaitForSingleObject(hThread, INFINITE);

	CloseHandle(hThread);
	VirtualFreeEx(hProcess, allocateMemory, 0, MEM_RELEASE);

	CloseHandle(hProcess);
}

int main() {

	std::cout << "PID: ";
	DWORD PID;

	std::cin >> PID;

	std::cout << "Dll path: ";
	std::string dllPath;

	std::cin >> dllPath;

	injectDLL(PID, dllPath);

	return 0;
}
