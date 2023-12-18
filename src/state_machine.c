#include <stdio.h>
#include "state_machine.h"

Program load_program(const char* pFilePath)
{
  Program outProg;

  int bufferLen = 32;
  char buffer[32];
  FILE* fptr = fopen(pFilePath, "r");
  while(fgets(buffer, bufferLen, fptr))
  {
    printf("%s", buffer);
  }
  
  return outProg;
}

void reset_state(StateMachine* pProgramState)
{
  pProgramState->lastCond = COND_ZRO;
  pProgramState->instCount = 0;
  
  for(int i = 0; i < NUM_REGISTERS; i++)
  {
    pProgramState->registers[i] = 0;
  }

  for(int i = 0; i < MAX_MEMORY; i++)
  {
    pProgramState->memory[i] = 0;
  }
}

void execute_program(StateMachine* pProgramState, Program program)
{
  
}