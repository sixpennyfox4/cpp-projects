// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <Windows.h>
#include <iostream>
#include <vector>

namespace Memory{
    DWORD addr{ 0x00183828 };
    std::vector<DWORD> offsets{ 0x8, 0xA44, 0x30, 0x30, 0x1B8 };
}

DWORD getPointerAddress(DWORD ptr, std::vector<DWORD> offsets) {
    DWORD addr{ ptr };
    for (int i{ 0 }; i < offsets.size(); ++i) {
        addr = *(DWORD*)addr;
        addr += offsets[i];
    }

    return addr;
}

DWORD WINAPI MainThread(HMODULE hModule) {
    int chosenAmmo{};

    AllocConsole();

    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    freopen_s(&f, "CONIN$", "r", stdin);
    std::cout << "Injected!\n";
    
    std::cout << "Ammo: ";
    std::cin >> chosenAmmo;

    FreeConsole();

    DWORD moduleBase{ (DWORD)GetModuleHandle(L"ac_client.exe") };

    while (!GetAsyncKeyState(VK_F6)) {
        Sleep(30);

        int* ammo{ (int*)getPointerAddress(moduleBase + Memory::addr, Memory::offsets) };
        *ammo = chosenAmmo;
    }

    fclose(f);
    FreeLibraryAndExitThread(hModule, 0);
    return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, nullptr));
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
