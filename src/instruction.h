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

void __add(int src1, int src2, int* dst);
void __sub(int src1, int src2, int* dst);
void __mul(int src1, int src2, int* dst);
void __div(int src1, int src2, int* dst);

void __and(int src1, int src2, int* dst);
void __or(int src1, int src2, int* dst);
void __not(int src, int* dst);