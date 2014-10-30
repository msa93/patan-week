#include "qlib.h"
#include "qtypes.h"
#include "qhash.h"

#define _qhashtable_alloc()               qalloc(QHashTable, 1)
#define _qhashtable_alloc_table(n)        qalloc(QSList, n)

QHashTable*
q_hash_table_new (QHashFunc hash_func, GEqualFunc equal_func)
{
  QHashTable *hash_table;
  hash_table = _qhashtable_alloc();
  hash_table->size = DEFAULT_QHASH_TABLE_SIZE;
  hash_table->equal_func = equal_func;
  hash_table->hash_func = hash_func;
  hash_table->table = _qhashtable_alloc_table (hash_table->size);  
}



