
typedef struct
{
	uint32_t regs[12];
	uint32_t sp;
	uint32_t flags;
	uint32_t lr;
	uint32_t pc;

	char *mem;
} cpu_t;

extern void cpu_run(cpu_t *c);