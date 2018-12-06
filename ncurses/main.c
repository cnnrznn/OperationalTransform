#include <ncurses.h>

#include "net.h"
#include "user-input.h"

#define FNSIZE 128

int main()
{
        char docfn[FNSIZE] = { 0 };

        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);

        net_init();

        get_document_name(stdscr, docfn, FNSIZE);

        endwin();

        return 0;
}
