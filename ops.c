#include "ops.h"

char document[DOCSIZE];
uint32_t revision = 0;

static op
t_ii(op a, op b)
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
        }

        return a;
}

static op
t_ir(op a, op b)
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
t_ri(op a, op b)
{
        if (a.pos < b.pos) {
        }
        else {
                a.pos++;
        }

        return a;
}

static op
t_rr(op a, op b)
{
        if (a.pos < b.pos) {
        }
        else if (a.pos > b.pos) {
                a.pos--;
        }
        else {
                a.type = NULLOP;
        }

        return a;
}

op
op_transform(op a, op b)
{
        if (INSERT == a.type && INSERT == b.type)
                return t_ii(a, b);
        if (INSERT == a.type && REMOVE == b.type)
                return t_ir(a, b);
        if (REMOVE == a.type && INSERT == b.type)
                return t_ri(a, b);
        if (REMOVE == a.type && REMOVE == b.type)
                return t_rr(a, b);
}

void
print_document(FILE *f)
{
        document[DOCSIZE-1] = '\0';
        fprintf(f, "%s\n", document);
}

void
op_perform(op o)
{
        int i;

        switch (o.type) {
        case INSERT:
                for (i=DOCSIZE-1; i>o.pos; i--)
                        document[i] = document[i-1];
                document[o.pos] = o.c;
                break;
        case REMOVE:
                for (i=o.pos; i<DOCSIZE-1; i++)
                        document[i] = document[i+1];
                document[DOCSIZE-1] = '\0';
                break;
        }

        revision++;
}
