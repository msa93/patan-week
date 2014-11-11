#include <stdlib.h>
#include "qlib.h"
#include "patan.h"

typedef enum {
  PATAN_OPT_EXIT = -1
} PatanOpt;

void
patan_console_init (PatanEspecialidades ** especialidades,
  PatanAlumnos ** alumnos)
{
  *especialidades = patan_especialidades_new ();
  alumnos = patan_alumnos_new ();
  //fiestas = patan_fiestas_new ();
}

void
patan_console_register_especialidades (PatanEspecialidades * especialidades)
{
  printf ("REGISTRAR ESPECIALIDADES\n");
}

void
patan_console_main_menu (PatanEspecialidades * especialidades)
{
  int option, error;
  printf ("1) Registrar especialidades. \n");
  printf ("-1) Exit\n");

  do {
    printf ("Input option: \n");

    error = scanf ("%d", &option);
    if (!error) {
      switch (option) {
        case 1:
          patan_console_register_especialidades (especialidades);
          break;          
      }
    }

  } while (!error && (option != PATAN_OPT_EXIT));
}

int
main (int argc, char ** argv)
{
  PatanEspecialidades *especialidades;
  PatanAlumnos *alumnos;
  //PatanFiestas *fiestas;

  QSList *especialidades_list;

  patan_console_init (&especialidades, &alumnos);

  patan_especialidades_insert (especialidades, "001", "Ingenieria Informatica");
  patan_especialidades_insert (especialidades, "002", "Ingenieria de Minas");
  patan_especialidades_insert (especialidades, "003", "Ingenieria Mecanica");
  patan_especialidades_insert (especialidades, "004", "Matematica");
  patan_especialidades_insert (especialidades, "005", "Artes Escenicas");
  patan_especialidades_insert (especialidades, "006", "Derecho");

  especialidades_list = q_hash_table_get_key_values (especialidades);
  patan_especialidades_print (especialidades_list);

  return 0;
}
