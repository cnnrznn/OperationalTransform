#ifndef _OPS_H
#define _OPS_H

#include <stdint.h>

#define COLLAB_MAX 64
#define DOCSIZE 8192

#define INSERT  1
#define REMOVE  2
#define NULLOP  3

extern char document[];

typedef struct {
        int type;
        char c;
        uint32_t pos;
} op;

typedef struct {
        uint32_t pid;
        uint32_t rev;
        op o;
} operation;

op
op_transform(op a, op b);

char
comp_operation(void *, void *);

void
op_perform(op o);

#endif /* _OPS_H */
