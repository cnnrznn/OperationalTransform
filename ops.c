#include "ops.h"

// TODO maintain data object for operations
char document[DOCSIZE];

static op
t_ii(op a, op b, int pa, int pb)
{
        if (a.pos < b.pos) {
        }
        else if (a.pos > b.pos) {
                a.pos++;
        }
        else {
                if (a.c == b.c) {
                        a.type = NULLOP;
                }
                else {
                        if (pa > pb)
                                a.pos++;
                }
        }

        return a;
}

static op
t_ir(op a, op b, int pa, int pb)
{
        if (a.pos < b.pos) {
        }
        else if (a.pos > b.pos) {
                a.pos--;
        }
        else {
        }

        return a;
}

static op
t_ri(op a, op b, int pa, int pb)
{
        if (a.pos < b.pos) {
        }
        else {
                a.pos++;
        }

        return a;
}

static op
t_rr(op a, op b, int pa, int pb)
{
        if (a.pos < b.pos) {
        }
        else if (a.pos > b.pos) {
                a.pos--;
        }
        else {
                a.type = NULLOP;
        }
}

op
op_transform(op a, op b, int pa, int pb)
{
        if (INSERT == a.type && INSERT == b.type)
                return t_ii(a, b, pa, pb);
        if (INSERT == a.type && REMOVE == b.type)
                return t_ir(a, b, pa, pb);
        if (REMOVE == a.type && INSERT == b.type)
                return t_ri(a, b, pa, pb);
        if (REMOVE == a.type && REMOVE == b.type)
                return t_rr(a, b, pa, pb);
}

char
comp_operation(void *a, void *b)
{
        int i;
        char ret = 0;

        operation *x = (operation *)a;
        operation *y = (operation *)b;

        for (i=0; i<COLLAB_MAX; i++) {
                if (x->s[i] > y->s[i])
                        return -1;       // one component of x is greater, therefore x is greater
                if (x->s[i] < y->s[i])
                        ret = 1;
        }

        return ret;
}

void
op_perform(op o)
{
        int i;

        switch (o.type) {
        case INSERT:
                for (i=o.pos; i<DOCSIZE-1; i++)
                        document[i+1] = document[i];
                document[o.pos] = o.c;
                break;
        case REMOVE:
                for (i=o.pos; i<DOCSIZE-1; i++)
                        document[i] = document[i+1];
                document[DOCSIZE-1] = '\0';
                break;
        }
}
