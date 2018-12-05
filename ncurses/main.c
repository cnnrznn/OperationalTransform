#include <ncurses.h>

#define FNSIZE 128

void
get_document_name(WINDOW *win, char *buf, size_t size)
{
        int index = 0;
        int ch;
        int y, x, ymax, xmax;

        getmaxyx(win, ymax, xmax);
        getyx(win, y, x);
        move(ymax-1, x);

        printw("document name: ");

        while (index < size-1) {
                ch = getch();
                if (10 == ch) { // ENTER key
                        return;
                }
                else if (KEY_BACKSPACE == ch) {
                        if (0 == index)
                                continue;

                        index--;
                        buf[index] = 0;

                        getyx(stdscr, y, x);
                        mvdelch(y, x-1);
                }
                else if (65 <= ch && ch <= 122) {
                        buf[index] = ch;
                        index++;

                        addch(ch);
                }

                refresh();
        }
}

int main()
{
        char docfn[FNSIZE] = { 0 };

        initscr();
        cbreak();
        noecho();
        keypad(stdscr, TRUE);

        get_document_name(stdscr, docfn, FNSIZE);

        endwin();

        return 0;
}
