#include "instruction.h"
#include "state_machine.h"

int main(int argc, char** argv)
{
  Program prog = load_program("test1.chc");
  StateMachine state;
  
  reset_state(state);
  execute_program(state, prog);
  reset_state(state);
  destroy_program(prog);
  return 0;
}