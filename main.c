#include <stdlib.h>
#include "qlib.h"
#include "patan.h"

typedef enum {
  PATAN_OPT_EXIT = -1
} PatanOpt;

void
patan_init (PatanEspecialidades ** especialidades,
  PatanAlumnos ** alumnos)
{
  *especialidades = patan_especialidades_new ();
  *alumnos = patan_alumnos_new ();
  //fiestas = patan_fiestas_new ();
}

int
main (int argc, char ** argv)
{
  PatanEspecialidades *especialidades;
  PatanAlumnos *alumnos;
  QDate d1, d2, d3, d4; 

  //PatanFiestas *fiestas;

  QSList *especialidades_list;

  patan_init (&especialidades, &alumnos);

  patan_especialidades_insert (especialidades, "005", "Artes Escenicas");
  patan_especialidades_insert (especialidades, "003", "Ingenieria Mecanica");
  patan_especialidades_insert (especialidades, "001", "Ingenieria Informatica");
  patan_especialidades_insert (especialidades, "002", "Ingenieria de Minas");
  patan_especialidades_insert (especialidades, "004", "Matematica");
  patan_especialidades_insert (especialidades, "006", "Derecho");

  d1 = q_date_new (1, 17, 1994);
  d2 = q_date_new (3, 19, 1995);
  d3 = q_date_new (5, 5, 1992);
  d4 = q_date_new (4, 8, 1992);

  patan_alumnos_insert (alumnos, "20105515", "Fabian Orccon", &d1, NULL);
  patan_alumnos_insert (alumnos, "20128060", "Alberto Suarez", &d2, NULL);
  patan_alumnos_insert (alumnos, "20115365", "Alberto Suarez", &d3, NULL);
  patan_alumnos_insert (alumnos, "20125666", "Alberto Suarez", &d4, NULL);


  especialidades_list = q_hash_table_get_key_values (especialidades);
  patan_especialidades_print (especialidades_list, PATAN_SORT_BY_ESPECIALIDAD);
  patan_alumnos_print (alumnos, PATAN_SORT_BY_ID);

  return 0;
}
