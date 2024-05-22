#define _CRT_SECURE_NO_WARNINGS

#include "cpu.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
  CPU cpu = create_cpu(1);

  if(argc != 2)
  {
    fprintf(stderr, "usage: %s <binary-file>", argv[0]);
    return 2;
  }

  FILE *f = fopen(argv[1], "rb");
  fseek(f, 0, SEEK_END);
  long fsize = ftell(f);
  fseek(f, 0, SEEK_SET);

  char *mem = malloc(fsize);
  fread(mem, fsize, 1, f);
  fclose(f);

  cpu.dram.mem = mem;

  while(1)
  {
    U32 pc = cpu.pc;
    U32 instr = mem[pc] | mem[pc+1]<<8 | mem[pc+2]<<16 | mem[pc+3]<<24;
    execute_instruction(&cpu, instr);
    if(cpu.pc == pc)  // ecall
    {
      if(cpu.reg[17] == 0)
      {
        cpu.reg[10] = getchar();
      }
      else if(cpu.reg[17] == 1)
      {
        putchar(cpu.reg[10]);
        fflush(stdin);
      }
      else if(cpu.reg[17] == 2)
      {
        break;
      }
      cpu.pc += 4;
    }
  }

  printf("\n\n\nDump:");

  for(int i = 0; i < NUM_REGISTERS; i++)
  {
    printf("%04x\n", cpu.reg[i]);
  }

  FILE *fp = fopen("dump", "wb");
  fwrite(cpu.dram.mem, fsize, 1, fp);
  fclose(fp);

  printf("PC: %i", cpu.pc);
  return 0;
}
