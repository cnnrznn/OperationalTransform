#ifndef _OPS_H
#define _OPS_H

#include <stdint.h>
#include <stdio.h>

#define INSERT  1
#define REMOVE  2
#define NULLOP  3

extern uint32_t revision;

typedef struct {
        int type;
        int c;
        uint32_t pos;
} operation;

typedef struct {
        int pid;
        uint32_t rev;
        operation op;
} message;

operation
op_transform(operation a, operation b, int, int);

#endif /* _OPS_H */
