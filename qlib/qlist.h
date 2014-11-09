#include "qfunctions.h"
#include "qtypes.h"

#ifndef __Q_LIST_H__
#define __Q_LIST_H__

typedef struct _QList QList;

struct _QList {
  qpointer data;
  QList *next;
  QList *prev;
};

QList*      q_list_last               (QList *list);
QList*      q_list_prepend            (QList * list, qpointer data);
QList*      q_list_append             (QList * list, qpointer data);
qboolean    q_list_is_empty           (QList *list);
QList*      q_list_find_compare       (QList * list, qpointer data,
                                       QEqualFunc func);
QList*      q_list_free               (QList * list);


#endif /* __Q_LIST_H__ */
