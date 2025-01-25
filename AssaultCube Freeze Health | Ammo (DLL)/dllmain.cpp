// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include <Windows.h>
#include <iostream>
#include <vector>

namespace Memory {
    DWORD addrAmmo{ 0x00183828 };
    std::vector<DWORD> offsetsAmmo{ 0x8, 0xA44, 0x30, 0x30, 0x1B8 };

    DWORD addrHealth{ 0x0017D848 };
    std::vector<DWORD> offsetsHealth{ 0x64, 0x58, 0x1E0, 0x8, 0xEC };
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
    char choice{};
    int chosenAmmo{};
    int chosenHealth{};

    AllocConsole();

    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    freopen_s(&f, "CONIN$", "r", stdin);
    std::cout << "Injected!\n";

    Sleep(3000);
    system("cls");

    while (true) {
        std::cout << "Health(h)/Ammo(a): " << std::flush;
        std::cin >> choice;

        system("cls");
        if (choice == 'h') {
            system("cls");

            std::cout << "Health: ";
            std::cin >> chosenHealth;

            break;
        }
        else if (choice == 'a') {
            system("cls");

            std::cout << "Ammo: ";
            std::cin >> chosenAmmo;

            break;
        }
        else {
            continue;
        }
    }

    system("cls");
    std::cout << "Click f6 to stop!";

    FreeConsole();

    DWORD moduleBase{ (DWORD)GetModuleHandle(L"ac_client.exe") };

    if (choice == 'h') {
        while (!GetAsyncKeyState(VK_F6)) {
            Sleep(30);

            int* health{ (int*)getPointerAddress(moduleBase + Memory::addrHealth, Memory::offsetsHealth) };
            *health = chosenHealth;
        }
    }
    else if (choice == 'a') {
        while (!GetAsyncKeyState(VK_F6)) {
            Sleep(30);

            int* ammo{ (int*)getPointerAddress(moduleBase + Memory::addrAmmo, Memory::offsetsAmmo) };
            *ammo = chosenAmmo;
        }
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
