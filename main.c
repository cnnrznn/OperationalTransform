#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "entity.h"
#include "heap.h"
#include "ops.h"

#define TESTSIZE 10000

int main(void)
{
        int i, j;
        operation op;
        operation *nextop;

        entity_init();
        srand(time(NULL));
        memset(op.s, 0, COLLAB_MAX*sizeof(uint32_t));

        for (i=0; i<TESTSIZE; i++) {
                op.pid = rand();
                //for (j=0; j<COLLAB_MAX; j++) {
                //        printf("%u, ", op.s[j]);
                //} printf("\n");
                receive_op(op);
                op.s[rand()%COLLAB_MAX]++;
        }

        printf("=============================================\n");

        for (i=0; i<TESTSIZE; i++) {
                nextop = heap_extract(&Queue);
                //for (j=0; j<COLLAB_MAX; j++) {
                //        printf("%u, ", nextop->s[j]);
                //} printf("\n");
        }

        return 0;
}
