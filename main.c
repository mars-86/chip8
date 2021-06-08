#include "chip8.h"
#include <windows.h>
#include "instruction_dump.h"

void parse_instruction(char *dest[], char *src, const char *delim)
{
    char src_t[128];
    char *dest_p = dest;
    sprintf(src_t, "%s", src);
    char *token = strtok(src_t, delim);

    /* walk through other tokens */
    while( token != NULL ) {
        printf( " %s\n", token );
        sprintf(dest_p++, "%s", token);
        // dest_p++;

        token = strtok(NULL, delim);
    }
}

int main(int argc, char *argv[])
{
    getchar();
    HANDLE stdout_h = GetStdHandle(STD_OUTPUT_HANDLE);
    // SetConsoleOutputCP(CP_UTF8);
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

    char parsed_i[5][10];
    parse_instruction((char **)parsed_i, "This is - www.tutorialspoint.com - website", "-");
    int i;
    for (i = 0; i < 3; ++i)
        printf("%s\n", parsed_i[i]);
    return 0;
    init_device();
    load_rom("../Airplane.ch8");
    main_loop();
    release_resources();

    return 0;
}
