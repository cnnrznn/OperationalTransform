#include <ncurses.h>

#include "net.h"
#include "ot-client.h"
#include "user-input.h"

#define FNSIZE 128
#define PORT "3333"

static char *ip=NULL, *port=NULL;

void
loop(char *fn, size_t fnsize)
{
        // 1. if not connected (ip==NULL), query MASTER for document leader
        //      - get ip, port of leader
        //      - establish tcp connection with leader
        //      - set pid for ot-engine
        // 2. collect user input
        // 3. listen for incoming messages
        // 4. exchange messages with ot-client
}

int main()
{
        char docfn[FNSIZE] = { 0 };

        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);

        net_init(PORT);
        ot_client_init();

        get_document_name(stdscr, docfn, FNSIZE);

        // loop
        loop(docfn, FNSIZE);

        ot_client_free();
        net_fini();

        endwin();

        return 0;
}
