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
  bool isMultiLineComment = false;
  
  while(fgets(buffer, bufferLen, fptr))
  {
    lineNum++;
    if(strcmp(buffer, "\n") == 0) continue;
        
    char copy[32];
    strcpy(copy, buffer);

    char* rest = copy;
    char* token = strtok_r(rest, " \n", &rest);

    if(strcmp(token, "/*") == 0)
    {
      isMultiLineComment = true;
      continue;
    }

    if(strcmp(token, "*/") == 0)
    {
      isMultiLineComment = false;
      continue;
    }

    if(isMultiLineComment) continue;
    
    if(strcmp(token, "//") == 0) continue;

    if(strcmp(token, ".END") == 0) break;
    
    if(strcmp(token, ".VAR") == 0)
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

void reset_state(StateMachine& pProgramState)
{
  pProgramState.lastCond = COND_ZRO;
  pProgramState.instCount = -1;

  for(int i = 0; i < NUM_REGISTERS; i++)
  {
    std::string empty = " ";
    pProgramState.registers.push_back(empty);
  }
}

bool __instruction_exists(
  std::string instruction,
  const char* instructionName)
{
  return instruction.find(instructionName) != std::string::npos;
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

    if(__instruction_exists(inst, "LOAD"))
    {
      int reg;
      char stringVar[32];
      sscanf(inst.c_str(), "LOAD r%i %s", &reg, &stringVar);
      pProgramState.registers[reg].assign(pProgram.stringTable[stringVar].c_str());
      continue;
    }

    if(__instruction_exists(inst, "PRINTS"))
    {
      int reg;
      sscanf(inst.c_str(), "PRINTS r%i", &reg);
      std::cout << pProgramState.registers[reg] << std::endl;
      continue;
    }

    if(__instruction_exists(inst, "ADD"))
    {
      int reg1, reg2, reg3;
      sscanf(inst.c_str(), "ADD r%i r%i r%i", &reg3, &reg1, &reg2);
      double src1 = atof(pProgramState.registers[reg1].c_str());
      double src2 = atof(pProgramState.registers[reg2].c_str());
      pProgramState.registers[reg3] = std::to_string(src1 + src2);
      continue;
    }

    if(__instruction_exists(inst, "SUB"))
    {
      int reg1, reg2, reg3;
      sscanf(inst.c_str(), "SUB r%i r%i r%i", &reg3, &reg1, &reg2);
      double src1 = atof(pProgramState.registers[reg1].c_str());
      double src2 = atof(pProgramState.registers[reg2].c_str());
      pProgramState.registers[reg3] = std::to_string(src1 - src2);
      continue;
    }

    if(__instruction_exists(inst, "MUL"))
    {
      int reg1, reg2, reg3;
      sscanf(inst.c_str(), "MUL r%i r%i r%i", &reg3, &reg1, &reg2);
      double src1 = atof(pProgramState.registers[reg1].c_str());
      double src2 = atof(pProgramState.registers[reg2].c_str());
      pProgramState.registers[reg3] = std::to_string(src1 * src2);
      continue;
    }

    if(__instruction_exists(inst, "DIV"))
    {
      int reg1, reg2, reg3;
      sscanf(inst.c_str(), "DIV r%i r%i r%i", &reg3, &reg1, &reg2);
      double src1 = atof(pProgramState.registers[reg1].c_str());
      double src2 = atof(pProgramState.registers[reg2].c_str());
      pProgramState.registers[reg3] = std::to_string(src1 / src2);
      continue;
    }
  }
}