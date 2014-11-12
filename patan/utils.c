#include <stdio.h>
#include <stdarg.h>
#include "utils.h"

void
patan_print_header (const char *str, ...)
{
  const char *s;
  va_list args;

  va_start (args, str);

  if (str)
    printf ("%s\t\t\t", str);
  while (s = va_arg (args, const char *))
    printf ("%s\t\t\t", s);
  printf ("\n");

  va_end (args);
}

int
func_hash_key_strings_equal (qpointer data, char * cmp)
{
  QHashKeyValue *key_value;
  key_value = Q_HASH_KEY_VALUE (data);
  return strcmp((char *)key_value->key, (char *) cmp) == 0;
}
