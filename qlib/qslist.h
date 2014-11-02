#include "qfunctions.h"
#include "qtypes.h"

#ifndef __Q_SLIST_H__
#define __Q_SLIST_H__

typedef struct _QSList QSList;

struct _QSList {
  qpointer data;
  QSList *next;
};

QSList*     q_slist_prepend (QSList *list, qpointer data);
QSList*     q_list_append (QSList *list, gpointer data);
qboolean    q_slist_is_empty (QSList *list);
QSList*     q_slist_find_compare (QSList *list, gpointer data, QEqualFunc func);
QSList*     q_list_free (QSList *list);

#endif /* __Q_SLIST_H__ */
