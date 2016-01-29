#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "cpu.h"

int main(int argc, char **argv)
{
	cpu_t c = {0};
	c.mem = malloc(128 * 1024 * 1024);

	c.mem[0] = 0x01;
	c.mem[1] = 0x0d;
	c.mem[2] = 0x0d;
	c.mem[3] = 0x00;
	
	c.mem[4] = 0x15;
	c.mem[5] = 0;
	c.mem[6] = 0;
	c.mem[7] = 0;

	cpu_run(&c);
}
