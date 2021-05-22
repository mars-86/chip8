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

    init_event_handler();
    register_term_class(&_tc);
}

int process_keyboard_event(void)
{
    // read incomming events
    read_event_non_block();
    // dispatch events to handler
    dispatch_event();

}

LRESULT CALLBACK term_proc(HANDLE h, UINT e, WPARAM w, LPARAM l)
{
    if (TMKEV_GET_EVENT_TYPE(e) == KEY_EVENT) {
        if (TMKEV_KEYB_EVENT_IS_KEY_PRESSED(e)) {
            switch (TMKEV_KEYB_GET_KEY_AS_ASCII(l)) {
            case VK_ESCAPE:
                stop_event_handler();
                break;
            case VK_KEY_W_LOW:
                printf("%s", "w");
                break;
            default:
                ;
            }
        }
    }
    else {

    }
    return 0;
}
