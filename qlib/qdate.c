#include "qlib.h"
#include "qdate.h"

QDate*
q_date_new (int month, int day, int year)
{
  QDate *date;
  date = malloc (sizeof (QDate));
  date->month = month;
  date->day = day;
  date->year = year;

  return date;
}
