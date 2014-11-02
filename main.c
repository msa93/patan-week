#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "qlib.h"
#include "glib.h"

struct _AlumnoValue {
  char *nombre;
  QDate fecha_nacimiento;
  QHashKeyValue *especialidad;
  /* This is an easter egg dedicated to our friend Fiestas */
  /* List of QHashKeyValue */
  QSList *fiestas; 
};

typedef struct _AlumnoValue AlumnoValue;

struct _FiestaValue {
  char *nombre;
  int precio;
  QDate fecha;
  /* List of QHashKeyValue*/
  QSList *alumnos;
};

typedef struct _FiestaValue FiestaValue;

#define ALUMNO_VALUE(t)       ((AlumnoValue *) t)
#define FIESTA_VALUE(t)       ((FiestaValue *) t)

int
func_hash_key_strings_equal (qpointer data, char * cmp)
{
  QHashKeyValue *key_value;
  key_value = Q_HASH_KEY_VALUE (data);
  return strcmp(key_value->key, cmp) == 0;
}

AlumnoValue *
alumno_value_new (const char * nombre, QDate *fecha_nacimiento,
    QHashKeyValue *especialidad)
{
  AlumnoValue* alumno_value;

  alumno_value = malloc (sizeof (AlumnoValue));
  alumno_value->nombre = strdup (nombre);
  alumno_value->fecha_nacimiento.day = fecha_nacimiento->day;
  alumno_value->fecha_nacimiento.month = fecha_nacimiento->month;
  alumno_value->fecha_nacimiento.year = fecha_nacimiento->year;
  alumno_value->especialidad = especialidad;
  alumno_value->fiestas = NULL;
  return alumno_value;
}

FiestaValue *
fiesta_value_new (const char * nombre, int precio, QDate *fecha)
{
  FiestaValue* fiesta_value;

  fiesta_value = malloc (sizeof (FiestaValue));
  fiesta_value->nombre = nombre;
  fiesta_value->precio = precio;
  fiesta_value->fecha.day = fecha->day;
  fiesta_value->fecha.month = fecha->month;
  fiesta_value->fecha.year = fecha->year;
  fiesta_value->alumnos = NULL;
  return fiesta_value;
}

/*****************************************************************************/

/*
// This is a generic way to parse. It is missing to output what has been parsed.
// We are keeping it simple below.

QSList*
patan_input_format_parse (const char * filename, PatanFilenameFormat patan_fmt)
{
  FILE *f;
  char c;


  f = fopen (filename, "r");

  if (!f)
    return NULL;


  do {
    int i, j;
    char something[1000];
    i = 0;
    while ((c = fgetc (f)) && isdigit (c) && (c != ' ')) {
      // TODO: This way to stop reading is really ugly 
      if (c == EOF)
        break;
      something[i] = c;
      i++;
    }
    // TODO: This way to stop reading is really ugly
    if (c == EOF)
      break;
    something[i] = '\0';
    printf ("id: %s\n", something);

    i = 0;
    c = fgetc (f);
    something[i] = c;
    i++;
    if (isalpha (c)) { 
      while ((c = fgetc (f)) && (isalpha (c) || (c == ' '))) {
        something[i] = c;
        i++;
      }
    } else {
      while ((c = fgetc (f)) && (isdigit (c)) && (c != ' ')) {
        something[i] = c;
        i++;
      }
    }
    something[i - 1] = '\0';

    printf ("%s\n", something);

    if ((c == ' ') || (isdigit (c))) {
      i = 0;
      if (isdigit (c)) {
        something[i] = c;
        i++;
      }
      while ((c = fgetc (f)) && isdigit (c) && (c != ' ')) {
        something[i] = c;
        i++;
      }
      something[i] = '\0';
      printf ("MOMO: %s\n", something);

      i = 0;
      while ((c = fgetc (f)) && isdigit (c)) {
        something[i] = c;
        i++;
      }
      something[i] = '\0';
      printf ("day: %s\n", something);

      i = 0;
      while ((c = fgetc (f)) && isdigit (c)) {
        something[i] = c;
        i++;
      }
      something[i] = '\0';
      printf ("month: %s\n", something);

      i = 0;
      while ((c = fgetc (f)) && isdigit (c)) {
        something[i] = c;
        i++;
      }
      something[i] = '\0';
      printf ("year: %s\n", something);

    }
    printf ("\n");
  } while (c != EOF);

  fclose (f);
  
}

*/

QHashTable *
patan_parse_fiestas (const char * filename) {
  FILE *f;
  char c;
  QHashTable *hash_table;


  f = fopen (filename, "r");

  if (!f)
    return NULL;

  hash_table = q_hash_table_new (qfunc_hash_numeric_string,
      func_hash_key_strings_equal);

  do {
    int i, j;
    char something[1000];
    i = 0;
    int precio;
    char *id_fiesta, *nombre;
    QDate date;

    while ((c = fgetc (f)) && isdigit (c) && (c != ' ')) {
      /* TODO: This way to stop reading is really ugly */
      if (c == EOF)
        break;
      something[i] = c;
      i++;
    }
    /* TODO: This way to stop reading is really ugly */
    if (c == EOF)
      break;
    something[i] = '\0';
    id_fiesta = strdup (something);

    //printf ("DEBUG: %s\n", something);

    i = 0;
    while ((c = fgetc (f)) && (!isdigit (c))) {
      something[i] = c;
      i++;
    }
    something[i] = '\0';
    nombre = strdup (something);
    //printf ("DEBUG: %s\n", something);

    i = 0;
    something[i] = c;
    i++;
    while ((c = fgetc (f)) && isdigit (c) && (c != ' ')) {
      something[i] = c;
      i++;
    }
    something[i] = '\0';
    precio = atoi (something);
    //printf ("DEBUG: %s\n", something);

    i = 0;
    while ((c = fgetc (f)) && isdigit (c)) {
      something[i] = c;
      i++;
    }
    something[i] = '\0';
    date.day = atoi (something);
    //printf ("day: %d\n", date.day);

    i = 0;
    while ((c = fgetc (f)) && isdigit (c)) {
      something[i] = c;
      i++;
    }
    something[i] = '\0';
    date.month = atoi (something);
    //printf ("month: %d\n", date.month);

    i = 0;
    while ((c = fgetc (f)) && isdigit (c)) {
      something[i] = c;
      i++;
    }
    something[i] = '\0';
    date.year = atoi (something);
    //printf ("year: %d\n", date.year);


    q_hash_table_insert (hash_table, strdup (id_fiesta),
        fiesta_value_new (strdup (nombre), precio, &date));


    //printf ("\n");
  } while (c != EOF);

  fclose (f);

  return hash_table;
}

QHashTable *
patan_parse_alumnos (const char * filename, QHashTable *especialidades) {
  FILE *f;
  char c;
  QHashTable *hash_table;


  f = fopen (filename, "r");

  if (!f)
    return NULL;

  hash_table = q_hash_table_new (qfunc_hash_numeric_string,
      func_hash_key_strings_equal);

  do {
    int i, j;
    char something[1000];
    i = 0;
    char *id_alumno, *nombre, *id_especialidad;
    QDate date;

    while ((c = fgetc (f)) && isdigit (c) && (c != ' ')) {
      /* TODO: This way to stop reading is really ugly */
      if (c == EOF)
        break;
      something[i] = c;
      i++;
    }
    /* TODO: This way to stop reading is really ugly */
    if (c == EOF)
      break;
    something[i] = '\0';
    id_alumno = strdup (something);

    //printf ("DEBUG: %s\n", something);

    i = 0;
    while ((c = fgetc (f)) && (isalpha (c) || (c == ' '))) {
      something[i] = c;
      i++;
    }
    something[i] = '\0';
    nombre = strdup (something);
    //printf ("DEBUG: %s\n", something);

    i = 0;
    something[i] = c;
    i++;
    while ((c = fgetc (f)) && isdigit (c) && (c != ' ')) {
      something[i] = c;
      i++;
    }
    something[i] = '\0';
    id_especialidad = strdup (something);
    //printf ("DEBUG: %s\n", something);

    i = 0;
    while ((c = fgetc (f)) && isdigit (c)) {
      something[i] = c;
      i++;
    }
    something[i] = '\0';
    date.day = atoi (something);
    //printf ("day: %d\n", date.day);

    i = 0;
    while ((c = fgetc (f)) && isdigit (c)) {
      something[i] = c;
      i++;
    }
    something[i] = '\0';
    date.month = atoi (something);
    //printf ("month: %d\n", date.month);

    i = 0;
    while ((c = fgetc (f)) && isdigit (c)) {
      something[i] = c;
      i++;
    }
    something[i] = '\0';
    date.year = atoi (something);
    //printf ("year: %d\n", date.year);


    q_hash_table_insert (hash_table, strdup (id_alumno),
        alumno_value_new (strdup (nombre), &date,
            q_hash_table_get_key_value_by_key (especialidades,
                id_especialidad)));


    //printf ("\n");
  } while (c != EOF);

  fclose (f);

  return hash_table;
}

QHashTable *
patan_parse_especialidades (const char * filename) {
  FILE *f;
  char c;
  QHashTable *hash_table;


  f = fopen (filename, "r");

  if (!f)
    return NULL;

  hash_table = q_hash_table_new (qfunc_hash_numeric_string,
      func_hash_key_strings_equal);

  do {
    int i, j;
    char something[1000];
    i = 0;
    char *id_especialidad, *especialidad;

    while ((c = fgetc (f)) && isdigit (c) && (c != ' ')) {
      /* TODO: This way to stop reading is really ugly */
      if (c == EOF)
        break;
      something[i] = c;
      i++;
    }
    /* TODO: This way to stop reading is really ugly */
    if (c == EOF)
      break;
    something[i] = '\0';
    id_especialidad = strdup (something);

    //printf ("DEBUG: %s\n", something);

    i = 0;
    while ((c = fgetc (f)) && (isalpha (c) || (c == ' '))) {
      something[i] = c;
      i++;
    }
    something[i] = '\0';
    especialidad = strdup (something);
    //printf ("DEBUG: %s\n", something);


    q_hash_table_insert (hash_table, strdup (id_especialidad),
        strdup (especialidad));

    //printf ("\n");
  } while (c != EOF);

  fclose (f);

  return hash_table;
}

void
patan_parse_asistencia (const char * filename, QHashTable *fiestas,
    QHashTable *alumnos)
{
  FILE *f;
  char c;

  f = fopen (filename, "r");

  if (!f)
    return NULL;


  do {
    int i, j;
    char something[1000];
    i = 0;
    char *id_fiesta, *id_alumno;
    QHashKeyValue *fiesta_kv, *alumno_kv;
    FiestaValue *fiesta_val;
    AlumnoValue *alumno_val;

    while ((c = fgetc (f)) && isdigit (c) && (c != ' ')) {
      /* TODO: This way to stop reading is really ugly */
      if (c == EOF)
        break;
      something[i] = c;
      i++;
    }
    /* TODO: This way to stop reading is really ugly */
    if (c == EOF)
      break;
    something[i] = '\0';
    id_fiesta = something;
    fiesta_kv = q_hash_table_get_key_value_by_key (fiestas, id_fiesta);
    fiesta_val = FIESTA_VALUE (fiesta_kv->value);

    //printf ("DEBUG: %s\n", something);

    i = 0;
    while ((c = fgetc (f)) && (isdigit (c)) && (c != ' ')) {
      something[i] = c;
      i++;
    }
    something[i] = '\0';
    //printf ("DEBUG: %s\n", something);
    id_alumno = something;
    alumno_kv = q_hash_table_get_key_value_by_key (alumnos, id_alumno);
    alumno_val = ALUMNO_VALUE (alumno_kv->value);

    fiesta_val->alumnos = q_slist_prepend (fiesta_val->alumnos, alumno_kv);
    alumno_val->fiestas = q_slist_prepend (alumno_val->fiestas, fiesta_kv);


    //q_hash_table_insert (hash_table, strdup (id_especialidad),
    //    strdup (especialidad));

    printf ("\n");
  } while (c != EOF);

  fclose (f);
}

/*****************************************************************************/

int
main ()
{
  QHashTable *especialidades, *alumnos, *fiestas;
  AlumnoValue *est_val;
  FiestaValue *fie_val;
  QSList *l;


  especialidades = patan_parse_especialidades ("especialidad.txt");
  /*
  printf ("ESPECIALIDAD====: %s\n",
      q_hash_table_get_key_value_by_key (especialidades, "101")->value);
  */

  alumnos = patan_parse_alumnos ("alumno.txt", especialidades);

  /*
  est_val = q_hash_table_get_key_value_by_key (alumnos, "20070101")->value;
  printf ("AAAA====: %s\n",
      est_val->especialidad->value);
  */


  //printf ("---------------------------------------------\n");

  fiestas = patan_parse_fiestas ("fiestas.txt");

  fie_val = q_hash_table_get_key_value_by_key (fiestas, "001")->value;
  printf ("ESPECIALIDAD====: %s\n",
      fie_val->nombre);


  patan_parse_asistencia ("asistencia.txt", fiestas, alumnos);


  //fie_val = q_hash_table_get_key_value_by_key (fiestas, "001")->value;

  est_val = q_hash_table_get_key_value_by_key (alumnos, "20105515")->value;
  l = est_val->fiestas;
  while (l != NULL) {
    printf ("alumno_id: %s\n", Q_HASH_KEY_VALUE (l->data)->key);

    //printf ("%s\n", alumno_kv->nombre);

    l = l->next;
  }




  return TRUE;
}
