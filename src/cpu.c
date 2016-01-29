#include <stdio.h>
#include <stdlib.h>

#include <stdint.h>
#include "cpu.h"

typedef void(*cpu_ptr)(cpu_t *c, uint32_t arg1, uint32_t arg2, uint32_t flags);


#define decode(cp, a, imm) a != 0xff ? (a > 0xb ? (imm=a - 0xb), &imm : &cp->regs[a]) : ((cp->pc+=4, imm = cp->mem[cp->pc]), &imm)

void op_add(cpu_t *c, uint32_t arg1, uint32_t arg2, uint32_t flags)
{
	uint32_t tmp;
	uint32_t *a = decode(c, arg1, tmp);
	uint32_t *b = decode(c, arg2, tmp);

	printf("adding %i + %i...\n", *a, *b);

	*a += *b;

	printf("it made %i", *a);
}

void op_jmp(cpu_t *c, uint32_t arg1, uint32_t arg2, uint32_t flags)
{
	uint32_t tmp;
	decode(c, arg1, tmp);

}

void op_hlt(cpu_t *c, uint32_t arg1, uint32_t arg2, uint32_t flags)
{
	exit(0);
}

void cpu_run(cpu_t *c)
{
	uint32_t imm = 0;

	cpu_ptr ops[256];
	ops[0x01] = &op_add;
	ops[0x0a] = &op_jmp;
	ops[0x15] = &op_hlt;

	while(1)
	{
		uint32_t instr = *(uint32_t*)&c->mem[c->pc]; // fuck strict aliasing :D

		uint32_t flags = (instr & 0xff000000) >> 24;
		uint32_t arg2 =  (instr & 0x00ff0000) >> 16;
		uint32_t arg1 =  (instr & 0x0000ff00) >> 8;
		uint32_t o =     instr &  0x000000ff;

		ops[o](c, arg1, arg2, flags);

		c->pc += 4;
	}
}