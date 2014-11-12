#include <ctype.h>
#include <stdio.h>
#include "alumnos.h"

AlumnoValue *
alumno_value_new (const char * nombre, QDate *fecha_nacimiento,
    QHashKeyValue *especialidad)
{
  AlumnoValue *alumno_value;

  alumno_value = malloc (sizeof (AlumnoValue));
  alumno_value->nombre = strdup (nombre);
  alumno_value->fecha_nacimiento.day = fecha_nacimiento->day;
  alumno_value->fecha_nacimiento.month = fecha_nacimiento->month;
  alumno_value->fecha_nacimiento.year = fecha_nacimiento->year;
  alumno_value->especialidad = especialidad;
  alumno_value->fiestas = NULL;
  return alumno_value;
}


void
patan_alumno_value_print (qpointer data, qpointer user_data)
{
  QHashKeyValue *alumno;
  AlumnoValue *val = ALUMNO_VALUE (data);

  alumno = Q_HASH_KEY_VALUE (data);
  printf ("%s\t\t\t%s\t\t\t%d/%d/%d\n", (char *) alumno->key, (char *) val->nombre,
    val->fecha_nacimiento.day, val->fecha_nacimiento.month,
    val->fecha_nacimiento.year);
}

/* Compare Functions */
static int
patan_alumnos_cmp_by_id (QHashKeyValue * kv1,
    QHashKeyValue * kv2)
{
  return strcmp (kv1->key, kv2->key);
}


void
patan_alumnos_print (QSList * alumnos_list, PatanSortBy sort_by)
{
  printf ("ID\t\t\tESPECIALIDAD\n");

  switch (sort_by) {
    case PATAN_SORT_BY_ID:
      alumnos_list = q_slist_sort (alumnos_list,
          patan_alumnos_cmp_by_id);
      break;
    default:
      break;
  }
  q_slist_foreach (alumnos_list, patan_alumno_value_print, NULL);
}


QHashTable *
patan_alumnos_new ()
{
  return q_hash_table_new (qfunc_hash_numeric_string,
      func_hash_key_strings_equal);
}

void
patan_alumnos_insert (QHashTable * hash_table, const char * id,
    const char * nombre, QDate *date, QHashKeyValue *especialidad_kv)
{
  q_hash_table_insert (hash_table, strdup (id),
      alumno_value_new (strdup (nombre), date, especialidad_kv));
}


/* Parsear archivo de alumnos */

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

    i = 0;
    while ((c = fgetc (f)) && (isalpha (c) || (c == ' '))) {
      something[i] = c;
      i++;
    }
    something[i] = '\0';
    nombre = strdup (something);

    i = 0;
    something[i] = c;
    i++;
    while ((c = fgetc (f)) && isdigit (c) && (c != ' ')) {
      something[i] = c;
      i++;
    }
    something[i] = '\0';
    id_especialidad = strdup (something);

    i = 0;
    while ((c = fgetc (f)) && isdigit (c)) {
      something[i] = c;
      i++;
    }
    something[i] = '\0';
    date.day = atoi (something);

    i = 0;
    while ((c = fgetc (f)) && isdigit (c)) {
      something[i] = c;
      i++;
    }
    something[i] = '\0';
    date.month = atoi (something);

    i = 0;
    while ((c = fgetc (f)) && isdigit (c)) {
      something[i] = c;
      i++;
    }
    something[i] = '\0';
    date.year = atoi (something);


    q_hash_table_insert (hash_table, strdup (id_alumno),
        alumno_value_new (strdup (nombre), &date,
            q_hash_table_get_key_value_by_key (especialidades,
                id_especialidad)));

  } while (c != EOF);

  fclose (f);

  return hash_table;
}

