#include <cstdio>
#include <cstdlib>
#include <cstring>

#include "state_machine.h"

Program load_program(const char* pFilePath)
{
  Program outProg;

  int bufferLen = 32;
  char buffer[32];
  FILE* fptr = fopen(pFilePath, "r");
  
  int lineNum = 0;
  
  // Pass 1: symbol table
  outProg.programLen = 0;
    
  while(fgets(buffer, bufferLen, fptr))
  {
    lineNum++;
    if(strcmp(buffer, "\n") == 0) continue;
    
    char copy[32];
    strcpy(copy, buffer);

    char* rest = copy;
    char* token = strtok_r(rest, " \n", &rest);

    if(strcmp(token, ".END") == 0) break;
    
    if(strcmp(token, ".STR") == 0)
    {
      char* variable = strtok_r(rest, " ", &rest);
      char* string = strtok_r(rest, "\n\"\"", &rest);
      outProg.stringTable[variable] = string;
      continue;
    }

    outProg.programLen++;
  }

  // Pass 2: "compiler"
  outProg.ppInstructions.reserve(outProg.programLen);
  fseek(fptr, 0, SEEK_SET);

  while(fgets(buffer, bufferLen, fptr))
  {
    // Skip assembler directives;
    if(buffer[0] == '.') continue;
    if(strcmp(buffer, "\n") == 0) continue;
    
    outProg.ppInstructions.push_back(buffer);
  }

  fclose(fptr);
  
  return outProg;
}

void destroy_program(Program& pProgram)
{
}

void reset_state(StateMachine& pProgramState)
{
  pProgramState.lastCond = COND_ZRO;
  pProgramState.instCount = -1;

  for(int i = 0; i < NUM_REGISTERS; i++)
  {
    pProgramState.registers.push_back("");
  }
}

void execute_program(StateMachine& pProgramState, Program& pProgram)
{
  while(true)
  {
    pProgramState.instCount++;
    std::string inst = pProgram.ppInstructions[pProgramState.instCount];
    if(inst.compare("STOP") == 0)
    {
      break;
    }

    if(inst.find("LEA") != std::string::npos)
    {
      int reg;
      char stringVar[16];
      sscanf(inst.c_str(), "LEA r%i %s", &reg, &stringVar);
      std::cout << pProgram.stringTable[stringVar] << std::endl;
      pProgramState.registers[reg] = pProgram.stringTable[stringVar];
    }
  }

  std::cout << pProgramState.registers[0] << std::endl;
}