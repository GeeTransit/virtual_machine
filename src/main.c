#define _CRT_SECURE_NO_WARNINGS

#include "cpu.h"
#include <stdio.h>

#define SIZE 2048

int main(void)
{
  CPU cpu = create_cpu(SIZE * sizeof(char));
  
  execute_instruction(&cpu, 0x00000517);
  execute_instruction(&cpu, 0x03450513);
  execute_instruction(&cpu, 0x00000597);
  execute_instruction(&cpu, 0x03658593);
  execute_instruction(&cpu, 0x008000ef);
  execute_instruction(&cpu, 0x00200893);
  execute_instruction(&cpu, 0x00000073);
  execute_instruction(&cpu, 0x00058283);
  execute_instruction(&cpu, 0x00550023);
  execute_instruction(&cpu, 0x00028863);
  execute_instruction(&cpu, 0x00150513);
  execute_instruction(&cpu, 0x00158593);
  execute_instruction(&cpu, 0xfedff06f);
  execute_instruction(&cpu, 0x00008067);
  execute_instruction(&cpu, 0x00000000);
  execute_instruction(&cpu, 0x00000000);
  execute_instruction(&cpu, 0x0C853503);
  execute_instruction(&cpu, 0x0D843583);

  for(int i = 0; i < NUM_REGISTERS; i++)
  {
    printf("%04x\n", cpu.reg[i]);
  }

  printf("%s\n", cpu.dram.mem);
  
  FILE *fp = fopen("dump", "w");
  fwrite(cpu.dram.mem, SIZE * sizeof(char), 1, fp);
  fclose(fp);

  printf("PC: %i", cpu.pc);
  return 0;
}
