# Instruction encoding

32 bit fixed width instructions
12 32 bit registers, doing it rite!
as well as flags

rax / rbx / rcx / rdx / rsi / rdi / rbp / rsp
r8 / r9  / r10  / r11 / r12 / r13 / r14 / r15

rsp used for WELL THE STACK JEEZ
r14 used as flags
r15 is the return address register. lr.

rax = r1
rbx = r2
rcx = r3
rdx = r4
rsi = r5
rdi = r6
rbp = r7
r8  = r8
r9  = r9
r10 = r10
r11 = r11
r12 = r12

# Instruction encoding

0xaabbccdd
( actually ddccbbaa )

a = instr
b = op1
c = op2
d = flags

op encoding:
0-b: r1-r12
b-fe: immediate (+ b)
ff: next 32-bit word is the imm

flag encoding:
bottom 2 bits are the instruction type
01 = 32 bit
10 = 16 bit
11 = 8 bit

# Opcodes

0 is a nop.

## standard mode opcodes..
### arithmetic

| Name | Encoding
|------|---------------------------------
| add  | 01
| sub  | 02
| mul  | 03
| div  | 04
| and  | 05
| or   | 06
| shl  | 07
| shr  | 08
| cmp  | 09

### load/store

yes, i ripped off arm here. shh.

| Name | Encoding
|------|--------------------------------
| load | 0a
| stor | 0b 

### flow control

the conditionals branch on condition.

| Name | Encoding
|------|--------------------------------
| jmp  | 0c
| je   | 0d
| jne  | 0d, flags=32
| jz   | 0e
| jnz  | 0e, flags=32
| jg   | 0f
| jge  | 0f, flags=32
| jl   | 10
| jle  | 10, flags=32
| call | 11

# privileged instructions

| Name | Encoding
|------|--------------------------------
| in   | 12
| out  | 13
| hlt  | 14
