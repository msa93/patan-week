#include "qlib.h"
#include "utils.h"

#ifndef __PATAN_ESPECIALIDADES_H__
#define __PATAN_ESPECIALIDADES_H__

#define ESPECIALIDAD_VALUE(t) ((EspecialidadValue *) t)
#define PATAN_ESPECIALIDADES(t) ((PatanEspecialidades *) t)

typedef QHashTable PatanEspecialidades;

int         patan_especialidades_cmp_by_especialidad (QHashKeyValue * kv1,
                                                      QHashKeyValue * kv2);

void        patan_especialidad_value_print (qpointer data,
                                            qpointer user_data);

void        patan_especialidades_print (QSList * especialidades_list,
                                        PatanSortBy sort_by);

QHashTable* patan_especialidades_new (void);

void        patan_especialidades_insert (QHashTable * hash_table,
                                         const char * id,
                                         const char * especialidad);

int         patan_especialidad_eq_nombre (QHashKeyValue * especialidad_kv,
                                          char * nombre);

#endif
