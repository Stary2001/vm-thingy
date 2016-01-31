#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "cpu.h"

#define MEMSZ 128 * 1024 * 1024

int main(int argc, char **argv)
{

	if(argc < 2)
	{
		fprintf(stderr, "Usage: %s [mem file]\n", argv[0]);
		exit(1);
	}

	cpu_t c = {0};
	c.mem = malloc(MEMSZ);

	int f = open(argv[1], O_RDONLY);
	if(f == -1)
	{
		fprintf(stderr, "Failed to open mem file!\n");
		exit(1);
	}

	read(f, c.mem, MEMSZ);
	close(f);

	cpu_run(&c);
}
