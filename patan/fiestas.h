#include "qlib.h"
#include "utils.h"

#ifndef __PATAN_FIESTAS_H__
#define __PATAN_FIESTAS_H__

#define FIESTA_VALUE(t)       ((FiestaValue *) t)

typedef QHashTable PatanFiestas;

typedef struct _FiestaValue FiestaValue;

struct _FiestaValue {
  char *nombre;
  int precio;
  QDate fecha;
  /* List of QHashKeyValue containing a key-value pair of AlumnoValue* */
  QSList *alumnos;
};

QHashTable*     patan_fiestas_new     ();
FiestaValue*    fiesta_value_new      (const char * nombre, int precio,
                                      QDate *fecha);
void            patan_fiestas_insert  (QHashTable * hash_table, const char * id,
                                      const char * nombre, int precio,
                                      QDate date);
QHashTable*     patan_parse_fiestas   (const char * filename);

#endif
