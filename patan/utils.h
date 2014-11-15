#include "qlib.h"

#ifndef __PATAN_UTILS_H__
#define __PATAN_UTILS_H__

#define PATAN_FORMAT_TAB          "\t\t"

//#define PATAN_CONSOLE_INT_WIDTH 10
//#define PATAN_CONSOLE_STR_WIDTH 20

#define PATAN_CONSOLE_INT_FORMAT              "%-10d"
#define PATAN_CONSOLE_STR_FORMAT              "%-20s"

typedef enum {
  PATAN_CONSOLE_INT,
  PATAN_CONSOLE_STR
} PatanConsoleType;

typedef enum {
  PATAN_SORT_BY_ID,
  PATAN_SORT_BY_ESPECIALIDAD,
  PATAN_SORT_BY_NOMBRE,
  PATAN_SORT_BY_FECHA
} PatanSortBy;


int       func_hash_key_strings_equal         (qpointer data, char * cmp);

#endif /* __PATAN_UTILS_H__ */
