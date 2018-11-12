#ifndef _OPS_H
#define _OPS_H

#include <stdint.h>
#include <stdio.h>

#define DOCSIZE 128

#define INSERT  1
#define REMOVE  2
#define NULLOP  3

#define ACK     1
#define MSG     2

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
        operation op;
} message;

operation
op_transform(operation a, operation b, int, int);

void
op_perform(operation o);

void
print_document(FILE *);

#endif /* _OPS_H */
