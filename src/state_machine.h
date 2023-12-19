#define NUM_REGISTERS 8

#include <cstddef>

#include <vector>
#include <iostream>
#include <unordered_map>

enum Condition
{
  COND_POS,
  COND_ZRO,
  COND_NEG
};

struct StateMachine
{
  Condition lastCond;
  uint32_t instCount; 
  std::vector<std::string> registers;
};

struct Program
{
  std::vector<std::string> ppInstructions;
  std::unordered_map<std::string, std::string> stringTable;
  size_t programLen;
};

Program load_program(const char* pFilePath);
void destroy_program(Program& pProgram);

void reset_state(StateMachine& pProgramState);
void execute_program(StateMachine& pProgramState, Program& pProgram);