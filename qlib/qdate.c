#include <stdio.h>
#include "qlib.h"
#include "qdate.h"

QDate
q_date_new (int month, int day, int year)
{
  QDate date;

  date.month = month;
  date.day = day;
  date.year = year;

  return date;
}

char *
q_date_to_string (QDate * date)
{
  char ret[11];
  sprintf (ret, "%02d/%02d/%d", date->day, date->month, date->year);
  
  return strdup (ret);
}
 
int
qfunc_date_cmp (QDate * date1, QDate * date2)
{
  return 10000 * date1->year + 100 * date1->month + date1->day -\
      10000 * date2->year + 100 * date2->month + date2->day;
}
