#include "qlib.h"
#include "patan.h"

int
main (int argc, char ** argv)
{
  QHashTable *especialidades, *alumnos, *fiestas;

  especialidades = patan_especialidades_new ();
  alumnos = patan_alumnos_new ();
  fiestas = patan_fiestas_new ();

  patan_especialidades_insert (especialidades, "001", "Ingenieria Informatica");
  patan_especialidades_insert (especialidades, "002", "Ingenieria de Minas");
  patan_especialidades_insert (especialidades, "003", "Ingenieria Mecanica");
  patan_especialidades_insert (especialidades, "004", "Matematica");
  patan_especialidades_insert (especialidades, "005", "Artes Escenicas");
  patan_especialidades_insert (especialidades, "006", "Derecho");

  return 0;
}
