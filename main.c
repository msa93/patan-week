#include "qlib.h"
#include "glib.h"

#include "patan.h"

int
main ()
{
  QHashTable *especialidades, *alumnos, *fiestas;
  AlumnoValue *est_val;
  QSList *l;


  especialidades = patan_parse_especialidades ("especialidad.txt");
  alumnos = patan_parse_alumnos ("alumno.txt", especialidades);
  fiestas = patan_parse_fiestas ("fiestas.txt");
  patan_parse_asistencia ("asistencia.txt", fiestas, alumnos);

  est_val = q_hash_table_get_key_value_by_key (alumnos, "20105515")->value;

  l = est_val->fiestas;
  while (l != NULL) {
    printf ("alumno_id: %s\n", Q_HASH_KEY_VALUE (l->data)->key);
    l = l->next;
  }

  return TRUE;
}
