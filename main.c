#include <stdio.h>

#include "qlib.h"
#include "glib.h"

int
main ()
{
  QSList *list = NULL;
  list = q_slist_prepend (list, INT_TO_QPOINTER (10));
  list = q_slist_prepend (list, INT_TO_QPOINTER (3));
  printf ("%d\n", QPOINTER_TO_INT (list->data));

  return TRUE;
}
