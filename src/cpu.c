#include <stdio.h>
#include <stdlib.h>

#include <stdint.h>
#include "cpu.h"

typedef void(*cpu_ptr)(cpu_t *c, uint32_t arg1, uint32_t arg2, uint32_t flags);

uint32_t get(cpu_t *c, uint32_t op)
{
	if(op <= 0xb)
	{
		return c->regs[op];
	}
	else if(op != 0xff)
	{
		return op - 0xc;
	}
	else
	{
		uint32_t tmp = *(uint32_t*)&c->mem[c->pc];
		c->pc += 4;
		return tmp;
	}
}

void set(cpu_t *c, uint32_t op, uint32_t v)
{
	if(op <= 0xb)
	{
		c->regs[op] = v;
	}
	else
	{
		printf("illegal opcode - setting 2 constants!\n");
		exit(0);
		// what?
	}
}

#define set(a, b) set(c, a, b)
#define get(a) get(c, a)

void op_add(cpu_t *c, uint32_t arg1, uint32_t arg2, uint32_t flags)
{
	set(arg1, get(arg1) + get(arg2));
}

void op_sub(cpu_t *c, uint32_t arg1, uint32_t arg2, uint32_t flags)
{
	set(arg1, get(arg1) - get(arg2));
}

void op_mul(cpu_t *c, uint32_t arg1, uint32_t arg2, uint32_t flags)
{
	set(arg1, get(arg1) * get(arg2));
}

void op_div(cpu_t *c, uint32_t arg1, uint32_t arg2, uint32_t flags)
{
	set(arg1, get(arg1) / get(arg2));
}

void op_and(cpu_t *c, uint32_t arg1, uint32_t arg2, uint32_t flags)
{
	set(arg1, get(arg1) & get(arg2));
}

void op_or(cpu_t *c, uint32_t arg1, uint32_t arg2, uint32_t flags)
{
	set(arg1, get(arg1) | get(arg2));
}

void op_shl(cpu_t *c, uint32_t arg1, uint32_t arg2, uint32_t flags)
{
	set(arg1, get(arg1) << get(arg2));
}

void op_shr(cpu_t *c, uint32_t arg1, uint32_t arg2, uint32_t flags)
{
	set(arg1, get(arg1) >> get(arg2));
}

void op_cmp(cpu_t *c, uint32_t arg1, uint32_t arg2, uint32_t flags)
{
	uint32_t a = get(arg1);
	uint32_t b = get(arg2);

	// clear all the flags...
	c->flags &= ~(FLAGS_LESSER | FLAGS_EQUAL | FLAGS_GREATER | FLAGS_ZERO);

	if(a == 0)
	{
		c->flags |= FLAGS_ZERO;
	}
	else if(a == b)
	{
		c->flags |= FLAGS_EQUAL;
	}
	else if(a > b)
	{
		c->flags |= FLAGS_GREATER;
	}
	else
	{
		c->flags |= FLAGS_LESSER;
	}
}

void jump(cpu_t *c, uint32_t arg, uint32_t flags)
{
	if(flags & OPFLAGS_RELATIVE)
	{
		if(flags & OPFLAGS_SIGNED)
		{
			c->pc += (int32_t)arg;
		}
		else
		{
			c->pc += arg;
		}
	}
	else
	{
		c->pc = arg;
	}
}

void op_jmp(cpu_t *c, uint32_t arg1, uint32_t arg2, uint32_t flags)
{
	jump(c, arg1, flags);
}

void op_je(cpu_t *c, uint32_t arg1, uint32_t arg2, uint32_t flags)
{
	// equal *or* jne is set

	if(((c->flags & FLAGS_EQUAL) ? 1 : 0) ^ ((flags & OPFLAGS_INVERT) ? 1 : 0))
	{
		jump(c, arg1, flags);
	}
}

void op_jz(cpu_t *c, uint32_t arg1, uint32_t arg2, uint32_t flags)
{
	// zero *or* jnz is set

	if(((c->flags & FLAGS_ZERO) ? 1 : 0) ^ ((flags & OPFLAGS_INVERT) ? 1 : 0))
	{
		jump(c, arg1, flags);
	}
}

void op_jl(cpu_t *c, uint32_t arg1, uint32_t arg2, uint32_t flags)
{
	// less *or* flag set and equal

	if(((c->flags & FLAGS_LESSER) ? 1 : 0) || ((flags & OPFLAGS_INVERT) && (c->flags & FLAGS_EQUAL)))
	{
		jump(c, arg1, flags);
	}
}

void op_jg(cpu_t *c, uint32_t arg1, uint32_t arg2, uint32_t flags)
{
	// less *or* flag set and equal

	if(((c->flags & FLAGS_EQUAL) ? 1 : 0) || ((flags & OPFLAGS_INVERT) && (c->flags & FLAGS_EQUAL)))
	{
		jump(c, arg1, flags);
	}
}

void op_call(cpu_t *c, uint32_t arg1, uint32_t arg2, uint32_t flags)
{
	// todo
}

void op_hlt(cpu_t *c, uint32_t arg1, uint32_t arg2, uint32_t flags)
{
}

void op_hcf(cpu_t *c, uint32_t arg1, uint32_t arg2, uint32_t flags)
{
	printf("unimplemented opcode %x\n", c->mem[c->pc] & 0xff);
	exit(0);
}

void cpu_run(cpu_t *c)
{
	uint32_t imm = 0;



	cpu_ptr ops[256];
	ops[0x01] = &op_add;
	ops[0x02] = &op_sub;
	ops[0x03] = &op_mul;
	ops[0x04] = &op_div;
	ops[0x05] = &op_and;
	ops[0x06] = &op_or;
	ops[0x07] = &op_shl;
	ops[0x08] = &op_shr;
	ops[0x09] = &op_cmp;

	ops[0x0a] = &op_hcf;
	ops[0x0b] = &op_hcf;

	ops[0x0c] = &op_jmp;
	ops[0x0d] = &op_je;
	ops[0x0e] = &op_jz;
	ops[0x0f] = &op_jg;
	ops[0x10] = &op_jl;
	ops[0x11] = &op_hcf; // call

	ops[0x12] = &op_hcf; // in
	ops[0x13] = &op_hcf; // out
	ops[0x14] = &op_hlt; // hlt.

	ops[0xff] = &op_hcf;

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