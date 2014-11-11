#include "utils.h"

int
func_hash_key_strings_equal (qpointer data, char * cmp)
{
  QHashKeyValue *key_value;
  key_value = Q_HASH_KEY_VALUE (data);
  return strcmp((char *)key_value->key, (char *) cmp) == 0;
}
