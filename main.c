#include <stdio.h>
#include <stdlib.h>
#include "qlib.h"
#include "patan.h"

typedef enum {
  PATAN_OPT_REGISTRAR_ESPECIALIDAD = 1,
  PATAN_OPT_REGISTRAR_ALUMNO = 2,
  PATAN_OPT_REGISTRAR_FIESTA = 3,
  PATAN_OPT_MOSTRAR_ESPECIALIDADES = 4,
  PATAN_OPT_MOSTRAR_ALUMNOS = 5,
  PATAN_OPT_MOSTRAR_FIESTAS = 6,
  /* Especialidades */
  PATAN_OPT_SORT_ESPECIALIDADES_BY_ID = 1,
  PATAN_OPT_SORT_ESPECIALIDADES_BY_ESPECIALIDAD = 2,
  /* Alumnos */
  PATAN_OPT_SORT_ALUMNOS_BY_ID = 1,
  PATAN_OPT_SORT_ALUMNOS_BY_NOMBRE = 2,
  PATAN_OPT_SORT_ALUMNOS_BY_FECHA_NACIMIENTO = 3,
  /* Fiestas */
  PATAN_OPT_SORT_FIESTAS_BY_ID = 1,
  PATAN_OPT_SORT_FIESTAS_BY_NOMBRE = 2,
  PATAN_OPT_SORT_FIESTAS_BY_FECHA = 3,
  /* Extras */
  PATAN_OPT_BACK = 0,
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

void
patan_console_ask_for_files (PatanEspecialidades ** especialidades,
  PatanAlumnos ** alumnos, PatanFiestas ** fiestas)
{
  char filename[100];

  printf ("Ingrese archivo de especialidades: ");
  scanf ("%s", filename);
  *especialidades = patan_parse_especialidades (filename);

  printf ("Ingrese archivo de alumnos: ");
  scanf ("%s", filename);
  *alumnos = patan_parse_alumnos (filename, *especialidades);

  printf ("Ingrese archivo de fiestas: ");
  scanf ("%s", filename);
  *fiestas = patan_parse_fiestas (filename);
}

static void
patan_console_show_main_menu ()
{
  printf ("1) Registrar especialidad.\n");
  printf ("2) Registrar alumno.\n");
  printf ("3) Registrar fiesta.\n"); 
  printf ("4) Mostrar especialidades.\n"); 
  printf ("5) Mostrar alumnos.\n");
  printf ("6) Mostrar fiestas.\n");
  printf ("-1) Quit.\n");
}

static void
patan_console_show_sort_by_especialidades ()
{
  printf ("1) Ordenar por id.\n");
  printf ("2) Ordenar por especialidad.\n");
  printf ("-1) Back.\n");
}

static void
patan_console_show_sort_by_alumnos ()
{
  printf ("1) Ordenar por id.\n");
  printf ("2) Ordenar por nombre.\n");
  printf ("3) Ordenar por fecha de nacimiento.\n");
  printf ("4) Ordenar por fecha de especialidad.\n");
  printf ("-1) Back.\n");
}

qboolean
patan_console_menu (PatanEspecialidades * especialidades,
  PatanAlumnos * alumnos, PatanFiestas * fiestas)
{
  PatanOpt opt;
  qboolean ret;

  ret = TRUE;
  patan_console_show_main_menu ();

  printf ("Ingrese opcion: ");
  scanf ("%d", &opt);

  switch (opt) {
    case PATAN_OPT_REGISTRAR_ESPECIALIDAD:
      break;
    case PATAN_OPT_REGISTRAR_ALUMNO:
      break;
    case PATAN_OPT_REGISTRAR_FIESTA:
      break;
    case PATAN_OPT_MOSTRAR_ESPECIALIDADES:
    {
      PatanSortBy sort_by;
      QSList *especialidades_list;

      patan_console_show_sort_by_especialidades ();

      printf ("Ingrese opcion: ");
      scanf ("%d", &opt);

      switch (opt) {
        case PATAN_OPT_SORT_ESPECIALIDADES_BY_ID:
          especialidades_list = q_hash_table_get_key_values (especialidades);
          patan_especialidades_print (especialidades_list, PATAN_SORT_BY_ID);
          break;
        case PATAN_OPT_SORT_ESPECIALIDADES_BY_ESPECIALIDAD:
          especialidades_list = q_hash_table_get_key_values (especialidades);
          patan_especialidades_print (especialidades_list,
              PATAN_SORT_BY_ESPECIALIDAD);
          break;
        default:
          opt = PATAN_OPT_BACK;
          break;
      }
      break;
    }
    case PATAN_OPT_MOSTRAR_ALUMNOS:
    {
      PatanSortBy sort_by;
      QSList *alumnos_list;

      patan_console_show_sort_by_alumnos ();

      printf ("Ingrese opcion: ");
      scanf ("%d", &opt);

      switch (opt) {
        case PATAN_OPT_SORT_ALUMNOS_BY_ID:
          alumnos_list = q_hash_table_get_key_values (alumnos);
          patan_alumnos_print (alumnos_list, PATAN_SORT_BY_ID);
          break;
        case PATAN_OPT_SORT_ALUMNOS_BY_NOMBRE:
          alumnos_list = q_hash_table_get_key_values (alumnos);
          patan_alumnos_print (alumnos_list,
              PATAN_SORT_BY_NOMBRE);
          break;
        case PATAN_OPT_SORT_ALUMNOS_BY_FECHA_NACIMIENTO:
          /* TODO */
          break;
        case PATAN_OPT_SORT_ALUMNOS_BY_ESPECIALIDAD:
          /* TODO */
          break;
        default:
          opt = PATAN_OPT_BACK;
          break;
      }
      break;
    }
    case PATAN_OPT_EXIT:
      ret = FALSE;
      break;
    default:
      ret = TRUE;
  }
  return ret;
}

void
patan_console_loop (PatanEspecialidades * especialidades,
  PatanAlumnos * alumnos, PatanFiestas * fiestas)
{
  while (patan_console_menu (especialidades, alumnos, fiestas) == TRUE);
}


int
main (int argc, char ** argv)
{
  PatanEspecialidades *especialidades;
  PatanAlumnos *alumnos;
  PatanFiestas *fiestas;

  patan_console_ask_for_files (&especialidades, &alumnos, &fiestas);

  patan_console_loop (especialidades, alumnos, fiestas);

/*
  QDate d1, d2, d3, d4;
  QDate d5, d6, d7; 

  //PatanFiestas *fiestas;

  QSList *especialidades_list;
  QSList *alumnos_list;
  QSList *fiestas_list;

  patan_init (&especialidades, &alumnos, &fiestas);
  //especialidades = patan_parse_especialidades ("especialidad.txt");

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
  patan_fiestas_insert (fiestas, "3", "Fiesta de Finales", 90, &d7);

  especialidades_list = q_hash_table_get_key_values (especialidades);
  patan_especialidades_print (especialidades_list, PATAN_SORT_BY_ESPECIALIDAD);

  alumnos_list = q_hash_table_get_key_values (alumnos);
  patan_alumnos_print (alumnos_list, PATAN_SORT_BY_NOMBRE);

  fiestas_list = q_hash_table_get_key_values (fiestas);
  patan_fiestas_print (fiestas_list, PATAN_SORT_BY_ID);

*/

  

  return 0;
}
