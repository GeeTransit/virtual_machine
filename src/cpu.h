#define U32 unsigned int
#define U8 char

#define NUM_REGISTERS 32

#define OPCODE_R          0x33
  #define ADDSUB          0x0
    #define ADD           0x00
    #define SUB           0x20
  #define SLL             0x1
  #define SLT             0x2
  #define SLTU            0x3
  #define XOR             0x4
  #define SR              0x5
    #define SRL           0x00
    #define SRA           0x20
  #define OR              0x6
  #define AND             0x7

#define OPCODE_I          0x13
  #define ADDI            0x0
  #define SLLI            0x1
  #define SLTI            0x2
  #define SLTUI           0x3
  #define XORI            0x4
  #define SRI             0x5
    #define SRLI          0x00
    #define SRAI          0x20
  #define ORI             0x6
  #define ANDI            0x7

#define OPCODE_L          0x3
  #define LB              0x0
  #define LH              0x1
  #define LW              0x2
  #define LBU             0x4
  #define LBH             0x5

#define OPCODE_S          0x23
  #define SB              0x0
  #define SH              0x1
  #define SW              0x2

#define OPCODE_B          0x63
  #define BEQ             0x0
  #define BNE             0x1
  #define BLT             0x4
  #define BGE             0x5
  #define BLTU            0x6
  #define BGEU            0x7

#define OPCODE_JAL        0x6F
#define OPCODE_JALR       0x67
#define OPCODE_ECALL      0x73
#define OPCODE_LUI        0x37
#define OPCODE_AUIPC      0x17

#ifndef CPU_H
#define CPU_H

typedef struct
{
  char *mem;
} DRAM;

typedef struct
{
  U32 reg[NUM_REGISTERS];
  U32 pc;
  DRAM dram;
} CPU;

#endif

CPU create_cpu(size_t memory_size);
DRAM create_dram(size_t memory_size);
void execute_instruction(CPU *cpu, U32 instruction);
