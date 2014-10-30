#include "qlib.h"
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
  return !list;
}

gpointer
q_slist_find_compare (QSList *list, gpointer data, QEqualFunc func)
{
  QSList *l;
  for (l = list; l && func(data, l->data); l = l->next);
  return l;
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
  QSList *l, *cur;

  l = list;
  while (l) {
    cur = l;
    l = cur->next;
    free (l->data);
    free (cur); 
  }
  return NULL;
}

