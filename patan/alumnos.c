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
  printf ("%s\n", alumno_value->nombre);
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
  AlumnoValue *val;

  alumno = Q_HASH_KEY_VALUE (data);
  val = ALUMNO_VALUE (alumno->value);

  printf ("%s\t\t%s\t\t%02d/%02d/%d\t\t%s\n", (char *) alumno->key,
      (char *) val->nombre, val->fecha_nacimiento.day,
      val->fecha_nacimiento.month, val->fecha_nacimiento.year,
      val->especialidad ? val->especialidad->value : NULL);
}

/* Compare Functions */
static int
patan_alumnos_cmp_by_id (QHashKeyValue * kv1,
    QHashKeyValue * kv2)
{
  return strcmp (kv1->key, kv2->key);
}

static int
patan_alumnos_cmp_by_nombre (QHashKeyValue * kv1,
    QHashKeyValue * kv2)
{
  AlumnoValue *val1 = Q_HASH_KEY_VALUE (kv1->value);
  AlumnoValue *val2 = Q_HASH_KEY_VALUE (kv2->value);

  return strcmp (val1->nombre, val2->nombre);
}

static int
patan_alumnos_cmp_by_fecha (QHashKeyValue * kv1,
    QHashKeyValue * kv2)
{
  QDate *date1, *date2;
  AlumnoValue *val1 = ALUMNO_VALUE (kv1->value);
  AlumnoValue *val2 = ALUMNO_VALUE (kv2->value);
  date1 = &(val1->fecha_nacimiento);
  date2 = &(val2->fecha_nacimiento);  
  return qfunc_date_cmp (date1, date2);
}

static int
patan_alumnos_cmp_by_especial (QHashKeyValue * kv1,
    QHashKeyValue * kv2)
{
  AlumnoValue *val1 = Q_HASH_KEY_VALUE (kv1->value);
  AlumnoValue *val2 = Q_HASH_KEY_VALUE (kv2->value);

  return strcmp (val1->especialidad->value, val2->especialidad->value);
}

void
patan_alumnos_print (QSList * alumnos_list, PatanSortBy sort_by)
{
  patan_print_header ("ID", "NOMBRE", "FECHA NAC", "ESPECIALIDAD",
      NULL);

  switch (sort_by) {
    case PATAN_SORT_BY_ID:
      alumnos_list = q_slist_sort (alumnos_list, patan_alumnos_cmp_by_id);
      break;
    case PATAN_SORT_BY_NOMBRE:
      alumnos_list = q_slist_sort (alumnos_list, patan_alumnos_cmp_by_nombre);
      break;
    case PATAN_SORT_BY_FECHA:
      alumnos_list = q_slist_sort (alumnos_list, patan_alumnos_cmp_by_fecha);
      break;
    case PATAN_SORT_BY_ESPECIALIDAD:
      alumnos_list = q_slist_sort (alumnos_list, patan_alumnos_cmp_by_especial);
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

