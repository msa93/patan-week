#include <ctype.h>
#include <stdio.h>
#include "fiestas.h"

FiestaValue *
fiesta_value_new (const char * nombre, int precio, QDate * fecha)
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

void
patan_fiesta_value_print (qpointer data, qpointer user_data)
{
  QHashKeyValue *fiesta;
  FiestaValue *val;

  fiesta = Q_HASH_KEY_VALUE (data);
  val = FIESTA_VALUE (fiesta->value);

  printf ("%s\t\t%s\t\t%d/%d/%d\t\t%d\n", (char *) fiesta->key,
      (char *) val->nombre, val->fecha.day, val->fecha.month,
      val->fecha.year, val->precio);
}

/* Compare Functions */
static int
patan_fiestas_cmp_by_id (QHashKeyValue * kv1,
    QHashKeyValue * kv2)
{
  return strcmp (kv1->key, kv2->key);
}

static int
patan_fiestas_cmp_by_nombre (QHashKeyValue * kv1,
    QHashKeyValue * kv2)
{
  FiestaValue *val1 = Q_HASH_KEY_VALUE (kv1->value);
  FiestaValue *val2 = Q_HASH_KEY_VALUE (kv2->value);

  return strcmp (val1->nombre, val2->nombre);
}

void
patan_fiestas_print (QSList * fiestas_list, PatanSortBy sort_by)
{
  patan_print_header ("ID", "NOMBRE", "FECHA", "PRECIO (S/.)",
      NULL);

  switch (sort_by) {
    case PATAN_SORT_BY_ID:
      fiestas_list = q_slist_sort (fiestas_list, patan_fiestas_cmp_by_id);
      break;
    case PATAN_SORT_BY_NOMBRE:
      fiestas_list = q_slist_sort (fiestas_list, patan_fiestas_cmp_by_nombre);
      break;
    default:
      break;
  }
  q_slist_foreach (fiestas_list, patan_fiesta_value_print, NULL);
}

QHashTable *
patan_fiestas_new ()
{
  return q_hash_table_new (qfunc_hash_numeric_string,
      func_hash_key_strings_equal);
}

void
patan_fiestas_insert (QHashTable * hash_table, const char * id,
    const char * nombre, int precio, QDate * date)
{
  q_hash_table_insert (hash_table, strdup (id),
      fiesta_value_new (strdup (nombre), precio, date));
}


/* Parsear archivo de fiestas */


QHashTable *
patan_parse_fiestas (const char * filename)
{
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

    i = 0;
    while ((c = fgetc (f)) && (!isdigit (c))) {
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
    precio = atoi (something);

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


    q_hash_table_insert (hash_table, strdup (id_fiesta),
        fiesta_value_new (strdup (nombre), precio, &date));

  } while (c != EOF);

  fclose (f);

  return hash_table;
}

