#include "ops.h"

char document[DOCSIZE];
uint32_t revision = 0;

static operation
t_ii(operation a, operation b, int pa, int pb)
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
                else if (pa > pb) {
                        a.pos++;
                }
        }

        return a;
}

static operation
t_ir(operation a, operation b)
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

static operation
t_ri(operation a, operation b)
{
        if (a.pos < b.pos) {
        }
        else {
                a.pos++;
        }

        return a;
}

static operation
t_rr(operation a, operation b)
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

operation
op_transform(operation a, operation b, int pa, int pb)
{
        if (INSERT == a.type && INSERT == b.type)
                return t_ii(a, b, pa, pb);
        if (INSERT == a.type && REMOVE == b.type)
                return t_ir(a, b);
        if (REMOVE == a.type && INSERT == b.type)
                return t_ri(a, b);
        if (REMOVE == a.type && REMOVE == b.type)
                return t_rr(a, b);

        return a;
}

void
print_document(FILE *f)
{
        document[DOCSIZE] = '\0';
        fprintf(f, "%u---%s\n", revision, document);
}

void
op_perform(operation o)
{
        int i;

        if (o.pos >= DOCSIZE)
                return;

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
}
