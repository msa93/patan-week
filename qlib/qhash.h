#include "qtypes.h"

#ifndef __Q_HASH_H__
#define __Q_HASH_H__

#define DEFAULT_QHASH_TABLE_SIZE        300

typedef struct _QHashTable QHashTable;

struct _QHashTable {
  int size;
  QSList *table;
  GEqualFunc equal_func;
  QHashFunc hash_func;
};

QHashTable*     q_hash_table_new (QHashFunc hash_func, GEqualFunc equal_func);

#endif /* __Q_HASH_H__ */
