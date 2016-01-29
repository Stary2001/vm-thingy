# Instruction encoding

32 bit fixed width instructions
12 64 bit registers, doing it rite!
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
ff: next 32-bit (or 64 bit!) word is the imm

flag encoding:
bottom 2 bits are the instruction type
00 = 64 bit
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
| cmp  | 07

### load/store

yes, i ripped off arm here. shh.

| Name | Encoding
|------|--------------------------------
| load | 08
| stor | 09 

### flow control

the conditionals branch on condition.

| Name | Encoding
|------|--------------------------------
| jmp  | 0a
| je   | 0b
| jne  | 0c
| jz   | 0d
| jnz  | 0e
| jg   | 0f
| jge  | 10
| jl   | 11
| jle  | 12
| call | 13

# privileged instructions

| Name | Encoding
|------|--------------------------------
| in   | 13
| out  | 14
| hlt  | 15
