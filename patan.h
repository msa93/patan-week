#include "qlib.h"

#ifndef __PATAN_H__
#define __PATAN_H__

struct _AlumnoValue {
  char *nombre;
  QDate fecha_nacimiento;
  QHashKeyValue *especialidad;
  /* This is an easter egg dedicated to our friend Oscar Fiestas */
  /* List of QHashKeyValue containing a key-value pair of FiestaValue* */
  QSList *fiestas; 
};

typedef struct _AlumnoValue AlumnoValue;

struct _FiestaValue {
  char *nombre;
  int precio;
  QDate fecha;
  /* List of QHashKeyValue containing a key-value pair of AlumnoValue* */
  QSList *alumnos;
};

typedef struct _FiestaValue FiestaValue;

#define ALUMNO_VALUE(t)       ((AlumnoValue *) t)
#define FIESTA_VALUE(t)       ((FiestaValue *) t)
#define ESPECIALIDAD_VALUE(t) ((EspecialidadValue *) t)

#endif /* __PATAN_H__ */
