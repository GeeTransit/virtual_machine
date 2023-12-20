#include "state_machine.h"

int main(int argc, char** argv)
{
  Program prog = load_program(argv[1]);
  StateMachine state;
  
  reset_state(state);
  execute_program(state, prog);
  reset_state(state);
  return 0;
}