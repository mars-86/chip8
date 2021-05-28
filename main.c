#include "chip8.h"
#include <windows.h>

int main(int argc, char *argv[])
{
    HANDLE stdout_h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleOutputCP(CP_UTF8);
    // SetConsoleMode(stdout_h, 0x0007 | 0x0008 | 0x0004);

    DWORD dwMode = 0;
    if (!GetConsoleMode(stdout_h, &dwMode))
    {
        return GetLastError();
    }

    dwMode |= 0x0007;
    if (!SetConsoleMode(stdout_h, dwMode))
    {
        return GetLastError();
    }

    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = 0;
    lpCursor.dwSize = 30;
    SetConsoleCursorInfo(stdout_h, &lpCursor);

    init_device();
    load_rom("../Astro Dodge [Revival Studios, 2008].ch8");
    main_loop();
    release_resources();

    return 0;
}
