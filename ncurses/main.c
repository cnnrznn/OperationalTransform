#include <ncurses.h>

#include "net.h"
#include "user-input.h"

#define FNSIZE 128
#define PORT "3333"

int main()
{
        char docfn[FNSIZE] = { 0 };

        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);

        net_init(PORT);

        get_document_name(stdscr, docfn, FNSIZE);

        net_fini();

        endwin();

        return 0;
}
