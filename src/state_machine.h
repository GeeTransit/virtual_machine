#define NUM_REGISTERS 8
#define MAX_MEMORY 32768

typedef enum
{
  COND_POS,
  COND_ZRO,
  COND_NEG
} Condition;

typedef struct
{
  Condition lastCond;
  unsigned int instCount;
  
  unsigned int registers[NUM_REGISTERS];
  unsigned int memory[MAX_MEMORY];
} StateMachine;

typedef struct
{
  char** pInstructions;
  size_t programLen;
} Program;

Program load_program(const char* pFilePath);
void destroy_program(Program* pProgram);

void reset_state(StateMachine* pProgramState);
void execute_program(StateMachine* pProgramState, Program program);