#include <string.h>
#include <stdlib.h>
#include "cpu.h"

CPU create_cpu(size_t memory_size)
{
  return (CPU){.dram = create_dram(memory_size)};
}

DRAM create_dram(size_t memory_size)
{
  return (DRAM){.mem = memset(malloc(memory_size), 0, memory_size)};
}

void exec_addsub(CPU *cpu, U32 instruction)
{
  U8 func7 = (instruction >> 25) & 0x7F;
  U8 rs1 = (instruction >> 15) & 0x1F;
  U8 rs2 = (instruction >> 20) & 0x1F;
  U8 rd = (instruction >> 7) & 0x1F;
  
  switch(func7)
  {
    case ADD:
    {
      cpu->reg[rd] = cpu->reg[rs1] + cpu->reg[rs2];
    } break;

    case SUB:
    {
      cpu->reg[rd] = cpu->reg[rs1] - cpu->reg[rs2];
    } break;
  }
}

void exec_sll(CPU *cpu, U32 instruction)
{
  U8 rs1 = (instruction >> 15) & 0x1F;
  U8 rs2 = (instruction >> 20) & 0x1F;
  U8 rd = (instruction >> 7) & 0x1F;
  cpu->reg[rd] = cpu->reg[rs1] << cpu->reg[rs2];
}

void exec_slt(CPU *cpu, U32 instruction)
{
  U8 rs1 = (instruction >> 15) & 0x1F;
  U8 rs2 = (instruction >> 20) & 0x1F;
  U8 rd = (instruction >> 7) & 0x1F;
  cpu->reg[rd] = ((char)cpu->reg[rs1] < (char)cpu->reg[rs2]) ? 1 : 0;
}

void exec_sltu(CPU *cpu, U32 instruction)
{
  U8 rs1 = (instruction >> 15) & 0x1F;
  U8 rs2 = (instruction >> 20) & 0x1F;
  U8 rd = (instruction >> 7) & 0x1F;
  cpu->reg[rd] = ((U8)cpu->reg[rs1] < (U8)cpu->reg[rs2]) ? 1 : 0;
}

void exec_xor(CPU *cpu, U32 instruction)
{
  U8 rs1 = (instruction >> 15) & 0x1F;
  U8 rs2 = (instruction >> 20) & 0x1F;
  U8 rd = (instruction >> 7) & 0x1F;
  cpu->reg[rd] = cpu->reg[rs1] ^ cpu->reg[rs2];
}

void exec_sr(CPU *cpu, U32 instruction)
{
  U8 func7 = (instruction >> 25) & 0x7F;
  U8 rs1 = (instruction >> 15) & 0x1F;
  U8 rs2 = (instruction >> 20) & 0x1F;
  U8 rd = (instruction >> 7) & 0x1F;

  switch(func7)
  {
    case SRL:
    {
      cpu->reg[rd] = (U8)cpu->reg[rs1] >> (U8)cpu->reg[rs2];
    } break;

    case SRA:
    {
      cpu->reg[rd] = (char)cpu->reg[rs1] >> (char)cpu->reg[rs2];
    } break;
  }
}

void exec_or(CPU *cpu, U32 instruction)
{
  U8 rs1 = (instruction >> 15) & 0x1F;
  U8 rs2 = (instruction >> 20) & 0x1F;
  U8 rd = (instruction >> 7) & 0x1F;
  cpu->reg[rd] = cpu->reg[rs1] | cpu->reg[rs2];
}

void exec_and(CPU *cpu, U32 instruction)
{
  U8 rs1 = (instruction >> 15) & 0x1F;
  U8 rs2 = (instruction >> 20) & 0x1F;
  U8 rd = (instruction >> 7) & 0x1F;
  cpu->reg[rd] = cpu->reg[rs1] & cpu->reg[rs2];
}

void opcode_r(CPU *cpu, U32 instruction)
{
  U8 func3 = (instruction >> 12) & 0x7;
  switch(func3)
  {
    case ADDSUB:
    {exec_addsub(cpu, instruction);} break;

    case SLL:
    {exec_sll(cpu, instruction);} break;

    case SLT:
    {exec_slt(cpu, instruction);} break;

    case SLTU:
    {exec_sltu(cpu, instruction);} break;

    case XOR:
    {exec_xor(cpu, instruction);} break;

    case SR:
    {exec_sr(cpu, instruction);} break;

    case OR:
    {exec_or(cpu, instruction);} break;

    case AND:
    {exec_and(cpu, instruction);} break;
  }
}

void exec_addi(CPU *cpu, U32 instruction)
{
  U8 rs1 = (instruction >> 15) & 0x1F;
  U8 imm = (instruction >> 20);
  U8 rd = (instruction >> 7) & 0x1F;
  cpu->reg[rd] = cpu->reg[rs1] + imm;
}

void exec_slli(CPU *cpu, U32 instruction)
{
  U8 rs1 = (instruction >> 15) & 0x1F;
  U8 imm = (instruction >> 20) & 0xFFF;
  U8 rd = (instruction >> 7) & 0x1F;
  cpu->reg[rd] = cpu->reg[rs1] << imm;
}

void exec_slti(CPU *cpu, U32 instruction)
{
  U8 rs1 = (instruction >> 15) & 0x1F;
  U8 imm = (instruction >> 20) & 0xFFF;
  U8 rd = (instruction >> 7) & 0x1F;
  cpu->reg[rd] = ((char)cpu->reg[rs1] < (char)imm) ? 1 : 0;
}

void exec_sltiu(CPU *cpu, U32 instruction)
{
  U8 rs1 = (instruction >> 15) & 0x1F;
  U8 imm = (instruction >> 20) & 0xFFF;
  U8 rd = (instruction >> 7) & 0x1F;
  cpu->reg[rd] = ((U8)cpu->reg[rs1] < (U8)imm) ? 1 : 0;
}

void exec_xori(CPU *cpu, U32 instruction)
{
  U8 rs1 = (instruction >> 15) & 0x1F;
  U8 imm = (instruction >> 20) & 0xFFF;
  U8 rd = (instruction >> 7) & 0x1F;
  cpu->reg[rd] = cpu->reg[rs1] ^ imm;
}

void exec_sri(CPU *cpu, U32 instruction)
{
  U8 func7 = (instruction >> 25) & 0x7F;
  U8 rs1 = (instruction >> 15) & 0x1F;
  U8 imm = (instruction >> 20) & 0xFFF;
  U8 rd = (instruction >> 7) & 0x1F;

  switch(func7)
  {
    case SRLI:
    {
      cpu->reg[rd] = (U8)cpu->reg[rs1] >> (U8)imm;
    } break;

    case SRAI:
    {
      cpu->reg[rd] = (char)cpu->reg[rs1] >> (char)imm;
    } break;
  }
}

void exec_ori(CPU *cpu, U32 instruction)
{
  U8 rs1 = (instruction >> 15) & 0x1F;
  U8 imm = (instruction >> 20) & 0xFFF;
  U8 rd = (instruction >> 7) & 0x1F;
  cpu->reg[rd] = cpu->reg[rs1] | imm;
}

void exec_andi(CPU *cpu, U32 instruction)
{
  U8 rs1 = (instruction >> 15) & 0x1F;
  U8 imm = (instruction >> 20) & 0xFFF;
  U8 rd = (instruction >> 7) & 0x1F;
  cpu->reg[rd] = cpu->reg[rs1] & imm;
}

void opcode_i(CPU *cpu, U32 instruction)
{
  U8 func3 = (instruction >> 12) & 0x7;
  switch(func3)
  {
    case ADDI:
    {exec_addi(cpu, instruction);} break;

    case SLLI:
    {exec_slli(cpu, instruction);} break;

    case SLTI:
    {exec_slti(cpu, instruction);} break;

    case SLTUI:
    {exec_sltiu(cpu, instruction);} break;

    case XORI:
    {exec_xori(cpu, instruction);} break;

    case SRI:
    {exec_sri(cpu, instruction);} break;

    case ORI:
    {exec_ori(cpu, instruction);} break;

    case ANDI:
    {exec_andi(cpu, instruction);} break;
  }
}

void exec_lb(CPU *cpu, U32 instruction)
{
  U8 rs1 = (instruction >> 15) & 0x1F;
  U8 imm = (instruction >> 20) & 0xFFF;
  U8 rd = (instruction >> 7) & 0x1F;
  U8 addr = cpu->reg[rs1] + imm;
  cpu->reg[rd] = cpu->dram.mem[addr];
}

void exec_lh(CPU *cpu, U32 instruction)
{
  U8 rs1 = (instruction >> 15) & 0x1F;
  U8 imm = (instruction >> 20) & 0xFFF;
  U8 rd = (instruction >> 7) & 0x1F;
  U8 addr = cpu->reg[rs1] + imm;
  cpu->reg[rd] = cpu->dram.mem[addr] | cpu->dram.mem[addr + 1] << 8;
}

void exec_lw(CPU *cpu, U32 instruction)
{
  U8 rs1 = (instruction >> 15) & 0x1F;
  U8 imm = (instruction >> 20) & 0xFFF;
  U8 rd = (instruction >> 7) & 0x1F;
  U8 addr = cpu->reg[rs1] + imm;
  cpu->reg[rd] = cpu->dram.mem[addr]
    | cpu->dram.mem[addr + 1] << 8
    | cpu->dram.mem[addr + 2] << 16
    | cpu->dram.mem[addr + 3] << 24;
}

void opcode_l(CPU *cpu, U32 instruction)
{
  U8 func3 = (instruction >> 12) & 0x7;
  switch(func3)
  {
    case LB:
    {exec_lb(cpu, instruction);} break;

    case LH:
    {exec_lh(cpu, instruction);} break;

    case LW:
    {exec_lw(cpu, instruction);} break;

    case LBU:
    {exec_lb(cpu, instruction);} break;

    case LBH:
    {exec_lw(cpu, instruction);} break;
  }
}

void exec_sb(CPU *cpu, U32 instruction)
{
  U8 rs1 = (instruction >> 15) & 0x1F;
  U8 rs2 = (instruction >> 20) & 0x1F;
  U8 imm = ((instruction & 0xFE000000) >> 20) | ((instruction >> 7) & 0x1F);
  U8 addr = cpu->reg[rs1] + imm;
  cpu->dram.mem[addr] = cpu->reg[rs2] & 0xFF;
}

void exec_sh(CPU *cpu, U32 instruction)
{
  U8 rs1 = (instruction >> 15) & 0x1F;
  U8 rs2 = (instruction >> 20) & 0x1F;
  U8 imm = ((instruction & 0xFE000000) >> 20) | ((instruction >> 7) & 0x1F);
  U8 addr = cpu->reg[rs1] + imm;
  cpu->dram.mem[addr] = cpu->reg[rs2] & 0xFF;
  cpu->dram.mem[addr + 1] = (cpu->reg[rs2] >> 8) & 0xFF;
}

void exec_sw(CPU *cpu, U32 instruction)
{
  U8 rs1 = (instruction >> 15) & 0x1F;
  U8 rs2 = (instruction >> 20) & 0x1F;
  U8 imm = ((instruction & 0xFE000000) >> 20) | ((instruction >> 7) & 0x1F);
  U8 addr = cpu->reg[rs1] + imm;
  cpu->dram.mem[addr] = cpu->reg[rs2] & 0xFF;
  cpu->dram.mem[addr + 1] = (cpu->reg[rs2] >> 8) & 0xFF;
  cpu->dram.mem[addr + 2] = (cpu->reg[rs2] >> 16) & 0xFF;
  cpu->dram.mem[addr + 3] = (cpu->reg[rs2] >> 24) & 0xFF;
}

void opcode_s(CPU *cpu, U32 instruction)
{
  U8 func3 = (instruction >> 12) & 0x7;

  switch(func3)
  {
    case SB:
    {exec_sb(cpu, instruction);} break;

    case SH:
    {exec_sh(cpu, instruction);} break;

    case SW:
    {exec_sw(cpu, instruction);} break;
  }
}

void exec_beq(CPU *cpu, U8 rs1, U8 rs2, U8 imm)
{
  if(cpu->reg[rs1] == cpu->reg[rs2])
  {
    cpu->pc += imm;
  }
}

void exec_bne(CPU *cpu, U8 rs1, U8 rs2, U8 imm)
{
  if(cpu->reg[rs1] != cpu->reg[rs2])
  {
    cpu->pc += imm;
  }
}

void exec_blt(CPU *cpu, U8 rs1, U8 rs2, U8 imm)
{
  if(cpu->reg[rs1] < cpu->reg[rs2])
  {
    cpu->pc += imm;
  }
}

void exec_bge(CPU *cpu, U8 rs1, U8 rs2, U8 imm)
{
  if(cpu->reg[rs1] >= cpu->reg[rs2])
  {
    cpu->pc += imm;
  }
}

void opcode_b(CPU *cpu, U32 instruction)
{
  U8 func3 = (instruction >> 12) & 0x7;
  U8 rs1 = (instruction >> 15) & 0x1F;
  U8 rs2 = (instruction >> 20) & 0x1F;
  
  U8 imm = ((instruction & 0x80000000) >> 19)
    | ((instruction & 0x80) << 4)
    | ((instruction >> 20) & 0x7E0)
    | ((instruction >> 7) & 0x1E);
  
  switch(func3)
  {
    case BEQ:
    {exec_beq(cpu, rs1, rs2, imm);} break;

    case BNE:
    {exec_bne(cpu, rs1, rs2, imm);} break;

    case BLT:
    {exec_blt(cpu, rs1, rs2, imm);} break;

    case BGE:
    {exec_bge(cpu, rs1, rs2, imm);} break;

    case BLTU:
    {exec_blt(cpu, rs1, rs2, imm);} break;

    case BGEU:
    {exec_bge(cpu, rs1, rs2, imm);} break;
  }
}

void opcode_jal(CPU *cpu, U32 instruction)
{
  U8 imm = instruction >> 12;
  U8 rd = (instruction >> 7) & 0x1F;
  cpu->reg[rd] = cpu->pc + 4;
  cpu->pc += imm;
}

void opcode_jalr(CPU *cpu, U32 instruction)
{
  U8 rs1 = (instruction >> 15) & 0x1F;
  U8 imm = ((instruction & 0x80000000) >> 1)
    | (instruction & 0xff000)
    | ((instruction >> 9) & 0x800)
    | ((instruction >> 20) & 0x7FE);
  U8 rd = (instruction >> 7) & 0x1F;
  cpu->reg[rd] = cpu->pc + 4;
  cpu->pc += cpu->reg[rs1] + imm;
}

void opcode_lui(CPU *cpu, U32 instruction)
{
  U8 rd = (instruction >> 7) & 0x1F;
  U8 imm = instruction >> 12;
  cpu->reg[rd] = imm << 12;
}

void opcode_auipc(CPU *cpu, U32 instruction)
{
  U8 rd = (instruction >> 7) & 0x1F;
  U8 imm = instruction >> 12;
  cpu->reg[rd] = cpu->pc + (imm << 12);
}

void execute_instruction(CPU *cpu, U32 instruction)
{
  U8 opcode = instruction & 0x7F;
  switch(opcode)
  {
    case OPCODE_R:
    {opcode_r(cpu, instruction);} break;

    case OPCODE_I:
    {opcode_i(cpu, instruction);} break;

    case OPCODE_L:
    {opcode_l(cpu, instruction);} break;

    case OPCODE_S:
    {opcode_s(cpu, instruction);} break;

    case OPCODE_B:
    {opcode_b(cpu, instruction);} break;

    case OPCODE_JAL:
    {opcode_jal(cpu, instruction);} break;

    case OPCODE_JALR:
    {opcode_jalr(cpu, instruction);} break;

    case OPCODE_ECALL:
    {
      if(cpu->reg[17] == 2) return;
    } break;

    case OPCODE_LUI:
    {opcode_lui(cpu, instruction);} break;

    case OPCODE_AUIPC:
    {opcode_auipc(cpu, instruction);} break;
  }
  
  cpu->reg[0] = 0;
  cpu->pc += 1;
}
