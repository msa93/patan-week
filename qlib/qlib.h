#ifndef __Q_LIB_H__
#define __Q_LIB_H__

#include "qtypes.h"
#include "qslist.h"

#define qalloc(type, n)        ((type *) qalloc (n * sizeof (type)))
#define INT_TO_QPOINTER(i)        ((qpointer)  (long) (i))

#endif /* __Q_LIB_H__ */
