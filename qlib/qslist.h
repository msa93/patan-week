#include "qtypes.h"

#ifndef __Q_SLIST_H__
#define __Q_SLIST_H__

typedef struct _QSList QSList;

struct _QSList {
  qpointer data;
  QSList *next;
};

QSList*     q_slist_prepend (QSList *list, qpointer data);
qboolean    q_slist_is_empty (QSList *list);
GSList*     q_list_find (GSList *list, gpointer data);
QSList*     q_list_free (QSList *list);

#endif /* __Q_SLIST_H__ */
