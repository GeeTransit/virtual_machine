#include <stdio.h>

void __add(int src1, int src2, int* dst)
{
  *dst = src1 + src2;
}

void __sub(int src1, int src2, int* dst)
{
  *dst = src1 - src2;
}

void __mul(int src1, int src2, int* dst)
{
  *dst = src1 * src2;
}

void __div(int src1, int src2, int* dst)
{
  *dst = src1 / src2;
}

void __and(int src1, int src2, int* dst)
{
  *dst = src1 & src2;
}

void __or(int src1, int src2, int* dst)
{
  *dst = src1 | src2;
}

void __not(int src, int* dst)
{
  *dst = ~src;
}