#ifndef __Q_LIB_H__
#define __Q_LIB_H__

#include <stdlib.h>

#include "qtypes.h"
#include "qslist.h"

#define INT_TO_QPOINTER(i)        ((qpointer)  (long) (i))
#define QPOINTER_TO_INT(i)        ((int) (long) (i))

#define qalloc(type, n)        ((type *) malloc (n * sizeof (type)))

typedef int (*QEqualFunc) (qpointer a, qpointer b);
typedef int (*QHashFunc)  (qpointer key);

#endif /* __Q_LIB_H__ */
