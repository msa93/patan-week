#include "qlib.h"
#include "qtypes.h"
#include "qlist.h"

#define _qlist_alloc()     qalloc(QList, 1)

/**
 * q_list_last:
 * @list: any #QList element
 *
 * Gets the last element in a #GList.
 *
 * Returns: the last element in the #GList,
 *     or %NULL if the #GList has no elements
 */

QList *
q_list_last (QList *list)
{
  if (list) {
    while (list->next)
      list = list->next;
  }

  return list;
}

QList*
q_list_prepend (QList * list, qpointer data)
{
  QList *new_list;

  new_list = _qlist_alloc();
  new_list->next = list;
  new_list->prev = NULL;
  new_list->data = data;

  if (list)
    list->prev = new_list;

  return new_list;
}

QList*
q_list_append (QList * list, qpointer data)
{
  QList *new_list, *last;

  new_list = _qlist_alloc();
  new_list->next = NULL;
  new_list->data = data;


  if (list) {
    last = q_list_last (list);
    last->next = new_list;
    new_list->prev = last;
    return list;
  } else {
    new_list->prev = NULL;
    return new_list;
  }
}

qboolean
q_list_is_empty (QList * list)
{
  return !list;
}

QList*
q_list_find_compare (QList * list, qpointer data, QEqualFunc func)
{
  QList *l;
  for (l = list; l != NULL; l = l->next) {
    if (func(l->data, data))
      break;
  }
  return l;
}

/**
 * q_slist_foreach:
 *
 * Call a function for each element of the list.
 *
 **/

void
q_list_foreach (QList * list, QFunc func, qpointer user_data)
{
  QList *l;
  l = list;
  while (l) {
    func (l->data, user_data);
    l = l->next;
  }
}

/**
 * q_list_free:
 *
 * Free a list and free each data element.
 *
 * Returns: an empty list.
 **/

QList*
q_list_free (QList * list)
{
  QList *l, *cur;

  l = list;
  while (l) {
    cur = l;
    l = cur->next;
    free (l->data);
    free (cur); 
  }
  return NULL;
}

