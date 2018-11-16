#include <stdlib.h>
#include <string.h>

#include "ops.h"

char *document = NULL;
static size_t size = 0;
static size_t last = 0;
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

size_t
get_docsize()
{
        return size;
}

void
print_document(FILE *f)
{
        char tmp = document[size-1];
        document[size-1] = '\0';
        fprintf(f, "%u---%s\n", revision, document);
        document[size-1] = tmp;
}

void
op_init(size_t _size)
{
        size = _size;
        last = 0;
        document = realloc(document, size);
        memset(document, ' ', size);
}

void
op_perform(operation o)
{
        int i;

        switch (o.type) {
        case INSERT:
                last = (o.pos <= last) ? last+1 : o.pos;
                while (size <= last) {
                        size *= 2;
                        document = realloc(document, size);
                        memset(document+last+1, ' ', size-last-1);
                }

                for (i=size-1; i>o.pos; i--)
                        document[i] = document[i-1];
                document[o.pos] = o.c;
                break;
        case REMOVE:
                if (0 == last)
                        last = last;
                else if (o.pos <= last)
                        last--;

                for (i=o.pos; i<size-1; i++)
                        document[i] = document[i+1];
                document[size-1] = ' ';
                break;
        }
}
