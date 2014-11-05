#include "qlib.h"

#ifndef __PATAN_H__
#define __PATAN_H__

/*
 * PATAN'S WEEK
 *
 * ¿Por que usamos tablas hash?
 * Respuesta rapida: Porque el ID es unico.
 * Los archivos de texto dados en la tarea son la base de datos del programa. 
 * Cada archivo tiene algo en comun, que es un <id>. Este <id> debe respetar la
 * unicidad. En el caso de un alumno, un <id> seria su codigo de estudiante y
 * solo el y nadie mas tiene el mismo codigo. 
 * El hecho que podamos identificar a cada elemento de la base de datos con un
 * <id> nos hace pensar que podemos usar los <id> como KEY y los datos
 * podemos usarlo como VALUE. 
 *
 * A continuacion, se detallan las estructuras que representan la base de datos.
 * La estructura esta hecha de tal manera que no sea necesario crear
 * adicionalmente una tabla hash extra solo para ASISTENCIA.
 *
 * ESPECIALIDAD
 * Las especialidades son representadas por una tabla hash donde cada elemento
 * se compone de lo siguiente:
 *   KEY: <id> [string de digitos unicamente]
 *   VALUE: <nombre_especialidad> [string]
 * 
 * ALUMNO
 * Los alumnos son representados por una tabla hash donde cada elemento
 * se compone de lo siguiente:
 *   KEY: <id> [string de digitos unicamente, codigo de alumno]
 *   VALUE:
 *     {
 *       <nombre> [string, el nombre del alumno]
 *       <fecha_nacimiento> [QDate, fecha en la que nacio el alumno]
 *       <especialidad> [puntero a ESPECIALIDAD a la cual pertenece el alumno]
 *       <fiestas> [lista de FIESTAS a las cuales se ha inscrito]
 *     }
 *
 * FIESTA
 * Las fiestas son representadas por una tabla hash donde cada elemento
 * se compone de lo siguiente:
 *   KEY: <id> [string de digitos unicamente]
 *   VALUE:
 *     {
 *       <nombre> [string, el nombre del evento o fiesta]
 *       <precio> [int, costo de la entrada a la fiesta]
 *       <fecha> [QDate, fecha de la fiesta]
 *       <alumnos> [lista de ALUMNOS inscritos en la fiesta]
 *     }
 *
 * TODO
 * Lo ideal seria tener de alguna manera todo relacionado. Pero puede que ya sea
 * demasiado ambicioso. Por ejemplo, relacionar especialidades con alumnos, para
 * obtener desde la misma ESPECIALIDAD == Ingenieria Informatica, por ejemplo,
 * todos los alumnos que estudian en Ingenieria Informatica y fueron a la FIESTA
 * == Fiesta de Cachimbos 2012.
*/

typedef struct _AlumnoValue AlumnoValue;
typedef struct _FiestaValue FiestaValue;

struct _AlumnoValue {
  char *nombre;
  QDate fecha_nacimiento;
  QHashKeyValue *especialidad;
  /* This is an easter egg dedicated to our friend Oscar Fiestas */
  /* List of QHashKeyValue containing a key-value pair of FiestaValue* */
  QSList *fiestas; 
};



struct _FiestaValue {
  char *nombre;
  int precio;
  QDate fecha;
  /* List of QHashKeyValue containing a key-value pair of AlumnoValue* */
  QSList *alumnos;
};


QHashTable*     patan_especialidades_new        ();
void            patan_especialidades_insert     (QHashTable * hash_table,
                                                const char * id,
                                                const char * especialidad);
QHashTable*     patan_alumnos_new     ();
void            patan_alumnos_insert  (QHashTable * hash_table, const char * id,
                                      const char * nombre, QDate date,
                                      QHashKeyValue *especialidad_kv);
QHashTable*     patan_fiestas_new     ();
void            patan_fiestas_insert  (QHashTable * hash_table, const char * id,
                                      const char * nombre, int precio,
                                      QDate date);
void            patan_registrar_asistencia      (QHashKeyValue * alumno_kv,
                                                QHashKeyValue * fiesta_kv);

int patan_especialidades_cmp_by_especialidad (QHashKeyValue * kv1,
    QHashKeyValue * kv2);


#define ALUMNO_VALUE(t)       ((AlumnoValue *) t)
#define FIESTA_VALUE(t)       ((FiestaValue *) t)
#define ESPECIALIDAD_VALUE(t) ((EspecialidadValue *) t)

#endif /* __PATAN_H__ */
