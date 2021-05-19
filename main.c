#include <stdio.h>
#include <stdlib.h>
#include "memory.h"
#include "memory_dump.h"
#include "../utils/file_manip.h"
#include "registers.h"
#include "register_dump.h"
#include "display.h"
#include <windows.h>
#include <wchar.h>

int main(int argc, char *argv[])
{
    HANDLE stdout_h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleMode(stdout_h, 0x0007 | 0x0008 | 0x0004);

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

    init_registers();
    init_display(&stdout_h);
    FILE *f;
    if (open_file(&f, "../Animal Race [Brian Astle].ch8", "rb")) {
        perror("file");
        return 1;
    }
    load_file_to_mem(&f, CHIP8_PROGRAM_START);
    set_PC(CHIP8_PROGRAM_START);
    fclose(f);
    free_registers_resources();
    int i;
    for (i = 0; i < 500; ++i) {
        SetConsoleCursorPosition(stdout_h, (COORD){1, 1});
        SPRITE sprite = { i + 20, 10, hex_digits[15], NULL };
        SPRITE sprite2 = { i + 12, 15, hex_digits[7], NULL };
        SPRITE sprite3 = { i + 2, 3, hex_digits[3], NULL };
        draw_sprites(&sprite);
        draw_sprites(&sprite2);
        draw_sprites(&sprite3);
        print();
        Sleep(33);
        clear_display();
    }

    wprintf(L"\x1b[31mThis text has a red foreground using SGR.31.\r\n");
    wprintf(L"\x1b[mThis text has returned to default colors using SGR.0 implicitly.\r\n");
    wprintf(L"\x1b[31;32;33;34;35;36;101;102;103;104;105;106;107mThis text attempts to apply many colors in the same command. Note the colors are applied from left to right so only the right-most option of foreground cyan (SGR.36) and background bright white (SGR.107) is effective.\r\n");
    wprintf(L"\x1b[39mThis text has restored the foreground color only.\r\n");
    wprintf(L"\x1b[49mThis text has restored the background color only.\r\n");

    wprintf(L"\x1b[1;1H");

    return 0;
}
