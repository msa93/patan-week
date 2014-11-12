#include <stdlib.h>
#include "qlib.h"
#include "patan.h"

typedef enum {
  PATAN_OPT_EXIT = -1
} PatanOpt;

void
patan_init (PatanEspecialidades ** especialidades,
  PatanAlumnos ** alumnos, PatanFiestas ** fiestas)
{
  *especialidades = patan_especialidades_new ();
  *alumnos = patan_alumnos_new ();
  *fiestas = patan_fiestas_new ();
}

int
main (int argc, char ** argv)
{
  PatanEspecialidades *especialidades;
  PatanAlumnos *alumnos;
  PatanFiestas *fiestas;

  QDate d1, d2, d3, d4;
  QDate d5, d6, d7; 

  //PatanFiestas *fiestas;

  QSList *especialidades_list;
  QSList *alumnos_list;
  QSList *fiestas_list;

  patan_init (&especialidades, &alumnos, &fiestas);

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
  patan_alumnos_insert (alumnos, "20115365", "Jorge Rodriguez", &d3, NULL);
  patan_alumnos_insert (alumnos, "20125666", "Felipe Kross", &d4, NULL);

  d5 = q_date_new (1, 15, 2014);
  d6 = q_date_new (7, 9, 2013);
  d7 = q_date_new (5, 30, 2014);

  patan_fiestas_insert (fiestas, "2", "Minerva", 30, &d5);
  patan_fiestas_insert (fiestas, "1", "Cachimbos Locos 2013", 60, &d6);
  patan_fiestas_insert (fiestas, "3", "Fiesta de Fin de Ciclo 2014", 90, &d7);

  especialidades_list = q_hash_table_get_key_values (especialidades);
  patan_especialidades_print (especialidades_list, PATAN_SORT_BY_ESPECIALIDAD);

  alumnos_list = q_hash_table_get_key_values (alumnos);
  patan_alumnos_print (alumnos_list, PATAN_SORT_BY_NOMBRE);

  fiestas_list = q_hash_table_get_key_values (fiestas);
  patan_fiestas_print (fiestas_list, PATAN_SORT_BY_ID);

  return 0;
}
