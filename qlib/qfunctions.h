#ifndef __Q_FUNCTIONS_H__
#define __Q_FUNCTIONS_H__

#include <string.h>
#include "qtypes.h"

#define qfunc_string_equal(a, b)      (strcmp (a, b) == 0)

typedef int (*QEqualFunc)   (qpointer a, qpointer b);
typedef int (*QCompareFunc) (qpointer a, qpointer b);
typedef int (*QHashFunc)    (int size, qpointer key);
typedef void (*QFunc)        (qpointer data, qpointer user_data);

int qfunc_hash_numeric_string    (int size, const char * string);
int qfunc_strings_equal             (char * a, char * b);
int qfunc_int_cmp                 (int a, int b);

#endif /* __Q_FUNCTIONS_H__ */
