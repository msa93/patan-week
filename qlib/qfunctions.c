#include "qfunctions.h"

int
qfunc_hash_numeric_string (int size, const char * string)
{
  int i, sum;
  char c;
  sum = 0;
  for (i = 0; c = string[i]; i++)
    sum += c - '0';
  return sum % size;
}

int
qfunc_strings_equal (char * a, char * b)
{
  return strcmp(a, b) == 0;
}

int
qfunc_int_cmp (int a, int b)
{
  return a - b;
}
