#include <Windows.h>

int main() {
    while (true)
        CreateMutex(0, 1, L"ROBLOX_singletonEvent");

    return 0;
}
