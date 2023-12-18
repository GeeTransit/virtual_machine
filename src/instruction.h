enum OpCode
{
  OP_CODE_ADD,
  OP_CODE_SUB,
  OP_CODE_MUL,
  OP_CODE_DIV,

  OP_CODE_AND,
  OP_CODE_OR,
  OP_CODE_NOT,

  OP_CODE_BE,
  OP_CODE_BL,

  OP_CODE_JMP
};

void add(int src1, int src2, int* dst);
void sub(int src1, int src2, int* dst);
void mul(int src1, int src2, int* dst);
void div(int src1, int src2, int* dst);

void and(int src1, int src2, int* dst);
void or(int src1, int src2, int* dst);
void not(int src, int* dst);