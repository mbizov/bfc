#ifndef ASM_H
#define ASM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*
Basic 1-to-1 translation of brainfuck instructions to x86 assembler instructions

using EAX register as cell pointer

*/

/* add eax, 1 */
#define MOVR "\x83\xc0\x01" /* > move cell pointer to the right */

/* sub eax, 1 */
#define MOVL "\x83\xe8\x01" /* < move cell pointer to the left */

/* add byte [eax], 1 */
#define INCR "\x80\x00\x01" /* + increment current cell by 1 */

/* sub byte [eax], 1 */
#define DECR "\x80\x28\x01" /* - decrement current cell by 1 */

/* returns the size of the instruction written */
int asm_write(FILE *f, int ic);

/**/
int asm_asm(FILE *ifp, FILE *ofp);


#endif
