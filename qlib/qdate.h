#ifndef __Q_DATE_H__
#define __Q_DATE_H__

typedef struct _QDate QDate;

struct _QDate {
  int year;
  int month;
  int day;
};

QDate q_date_new (int month, int day, int year);
char * q_date_to_string (QDate * date);
int qfunc_date_cmp (QDate * date1, QDate * date2);

#endif /* __Q_DATE_H__ */
