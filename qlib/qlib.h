#ifndef __Q_LIB_H__
#define __Q_LIB_H__

#include <stdlib.h>

#include "qtypes.h"
#include "qslist.h"
#include "qhash.h"
#include "qfunctions.h"
#include "qdate.h"


#define INT_TO_QPOINTER(i)        ((qpointer)  (long) (i))
#define QPOINTER_TO_INT(i)        ((int) (long) (i))

#define qalloc(type, n)        ((type *) malloc (n * sizeof (type)))



#endif /* __Q_LIB_H__ */
