#include "qtypes.h"
#include "qslist.h"

#define _qslist_alloc()     qalloc(QSList, 1)

QSList*
q_slist_prepend (QSList *list, qpointer data)
{
  QSList *new_list;

  new_list = _qslist_alloc();
  new_list->next = list;
  new_list->data = data;
  return new_list;
}

qboolean
q_slist_is_empty (QSList *list)
{
  return QSList == NULL;
}


/**
 * q_slist_free:
 *
 * Free a list and free each data element.
 *
 * Returns: an empty list.
 **/

QSList*
q_slist_free (QSList *list)
{
  QSList *l;

  l = list;
  while (l) {
    cur = l;
    l = cur->next;
    free (l->data);
    free (cur); 
  }
  return NULL;
}

