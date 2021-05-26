#include "keyboard.h"
#include <windows.h>
#include "../TMKev/tmkev.h"

LRESULT CALLBACK term_proc(HANDLE, UINT, WPARAM, LPARAM);
static TermClass _tc;

static char keyboard_layout[16][1] = {
    {"0"}, {"1"}, {"2"}, {"3"},
    {"4"}, {"5"}, {"6"}, {"7"},
    {"8"}, {"9"}, {"A"}, {"B"},
    {"C"}, {"D"}, {"E"}, {"F"}
};

void init_keyboard(void)
{
    _tc.cbSize = sizeof(_tc);
    _tc.lpfnTermProc = term_proc;

    init_event_handler(TMKEV_BLOCKING_MODE);
    register_term_class(&_tc);
}

int get_key_pressed_block(unsigned char *key)
{
    return get_key_pressed(key, TMKEV_BLOCKING_MODE);
}

int get_key_pressed_non_block(unsigned char *key)
{
    return get_key_pressed(key, TMKEV_NON_BLOCKING_MODE);
}

LRESULT CALLBACK term_proc(HANDLE h, UINT e, WPARAM w, LPARAM l)
{
    if (TMKEV_GET_EVENT_TYPE(e) == KEY_EVENT) {
        if (TMKEV_KEYB_EVENT_IS_KEY_PRESSED(e)) {
            return TMKEV_KEYB_GET_KEY_AS_ASCII(l);
            /* switch (TMKEV_KEYB_GET_KEY_AS_ASCII(l)) {
            case VK_KEY_0:
                printf("%s", "0");
                break;
            case VK_KEY_1:
                printf("%s", "1");
                break;
            case VK_KEY_2:
                printf("%s", "2");
                break;
            case VK_KEY_3:
                // printf("%s", "3");
                return 3;
            case VK_KEY_4:
                printf("%s", "4");
                break;
            case VK_KEY_5:
                printf("%s", "5");
                break;
            case VK_KEY_6:
                printf("%s", "6");
                break;
            case VK_KEY_7:
                printf("%s", "7");
                break;
            case VK_KEY_8:
                printf("%s", "8");
                break;
            case VK_KEY_9:
                printf("%s", "9");
                break;
            case VK_ESCAPE:
                stop_event_handler();
                break;
            case VK_KEY_W_LOW:
                printf("%s", "w");
                break;
            default:
                ;
            }*/
        }
    }
    else {

    }
    return 0;
}
