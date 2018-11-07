#ifndef _OPS_H
#define _OPS_H

#include <stdint.h>
#include <stdio.h>

#define DOCSIZE 8192

#define INSERT  1
#define REMOVE  2
#define NULLOP  3

extern char document[];
extern uint32_t revision;

typedef struct {
        int type;
        char c;
        uint32_t pos;
} operation;

typedef struct {
        uint32_t pid;
        uint32_t rev;
        op o;
} message;

op
op_transform(operation a, operation b);

void
op_perform(operation o);

void
print_document(FILE *);

#endif /* _OPS_H */
