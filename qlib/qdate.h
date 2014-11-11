#ifndef __Q_DATE_H__
#define __Q_DATE_H__

typedef struct _QDate QDate;

struct _QDate {
  int year;
  int month;
  int day;
};

QDate q_date_new (int month, int day, int year);

#endif /* __Q_DATE_H__ */
