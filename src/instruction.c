#include <stdio.h>

void add(int src1, int src2, int* dst)
{
  *dst = src1 + src2;
}

void sub(int src1, int src2, int* dst)
{
  *dst = src1 - src2;
}

void mul(int src1, int src2, int* dst)
{
  *dst = src1 * src2;
}

void div(int src1, int src2, int* dst)
{
  *dst = src1 / src2;
}

void and(int src1, int src2, int* dst)
{
  *dst = src1 & src2;
}

void or(int src1, int src2, int* dst)
{
  *dst = src1 | src2;
}

void not(int src, int* dst)
{
  *dst = ~src;
}