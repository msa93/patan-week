#include "qlib.h"

#ifndef __PATAN_UTILS_H__
#define __PATAN_UTILS_H__

#define PATAN_FORMAT_TAB        "\t\t"

typedef enum {
  PATAN_SORT_BY_ID,
  PATAN_SORT_BY_ESPECIALIDAD,
  PATAN_SORT_BY_NOMBRE
} PatanSortBy;


int       func_hash_key_strings_equal         (qpointer data, char * cmp);

#endif /* __PATAN_UTILS_H__ */
