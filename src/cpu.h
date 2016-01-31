
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

#define FLAGS_ZERO 1
#define FLAGS_GREATER (1 << 1)
#define FLAGS_EQUAL (1 << 2)
#define FLAGS_LESSER (1 << 3)

#define OPFLAGS_MODE_32 1
#define OPFLAGS_MODE_16 2
#define OPFLAGS_MODE_8 4
#define OPFLAGS_SIGNED 8
#define OPFLAGS_RELATIVE 16
#define OPFLAGS_INVERT 32