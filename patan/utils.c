#include <stdio.h>
#include <stdarg.h>
#include "utils.h"

void
patan_print_header (const char *str, ...)
{
  PatanConsoleType type;
  const char *s;
  va_list args;

  va_start (args, str);

  s = str;
  while (s) {
    type = va_arg (args, int);
    switch (type) {
      case PATAN_CONSOLE_INT:
        printf (PATAN_CONSOLE_INT_FORMAT, s);
        break;
      case PATAN_CONSOLE_STR:
        printf (PATAN_CONSOLE_STR_FORMAT, s);
        break;
      default:
        break;
    }
    s = va_arg (args, const char *);
  }
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
