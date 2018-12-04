#include <stdlib.h>
#include <string.h>

#include "ops.h"

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
