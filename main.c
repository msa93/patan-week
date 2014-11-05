#include <gtk/gtk.h>
#include "qlib.h"
#include "glib.h"

#include "patan.h"

enum
{
  COL_ID = 0,
  COL_ESPECIALIDAD,
  NUM_COLS
} ;
 
static GtkTreeModel *
create_and_fill_model (QHashTable * especialidades)
{
  GtkTreeStore  *treestore;
  GtkTreeIter    toplevel, child;
  QSList *especialidades_list, *l;
 
  treestore = gtk_tree_store_new(NUM_COLS,
                                 G_TYPE_STRING,
                                 G_TYPE_STRING);
 
  especialidades_list = q_hash_table_get_key_values (especialidades);
  l = especialidades_list;

  while (l) {
    gchar *id, *especialidad;

    id = Q_HASH_KEY_VALUE (l->data)->key;
    especialidad = Q_HASH_KEY_VALUE (l->data)->value;

    /* Append a top level row and leave it empty */
    gtk_tree_store_append(treestore, &toplevel, NULL);
    gtk_tree_store_set(treestore, &toplevel,
                       COL_ID, id,
                       COL_ESPECIALIDAD, especialidad,
                       -1);
    l = l->next;
  }

  return GTK_TREE_MODEL(treestore);
}
 
static GtkWidget *
create_view_and_model (QHashTable * especialidades)
{
  GtkTreeViewColumn   *col;
  GtkCellRenderer     *renderer;
  GtkWidget           *view;
  GtkTreeModel        *model;
 
  view = gtk_tree_view_new();
 
  /* --- Column #1 --- */
 
  col = gtk_tree_view_column_new();
 
  gtk_tree_view_column_set_title(col, "id");
 
  /* pack tree view column into tree view */
  gtk_tree_view_append_column(GTK_TREE_VIEW(view), col);
 
  renderer = gtk_cell_renderer_text_new();
 
  /* pack cell renderer into tree view column */
  gtk_tree_view_column_pack_start(col, renderer, TRUE);
 
  /* connect 'text' property of the cell renderer to
   *  model column that contains the first name */
  gtk_tree_view_column_add_attribute(col, renderer, "text", COL_ID);
 
 
  /* --- Column #2 --- */
 
  col = gtk_tree_view_column_new ();
 
  gtk_tree_view_column_set_title(col, "especialidad");
 
  /* pack tree view column into tree view */
  gtk_tree_view_append_column(GTK_TREE_VIEW(view), col);
 
  renderer = gtk_cell_renderer_text_new();
 
  /* pack cell renderer into tree view column */
  gtk_tree_view_column_pack_start(col, renderer, TRUE);
 
  /* connect 'text' property of the cell renderer to
   *  model column that contains the last name */
  gtk_tree_view_column_add_attribute(col, renderer, "text", COL_ESPECIALIDAD);
 
 
  model = create_and_fill_model(especialidades);
 
  gtk_tree_view_set_model(GTK_TREE_VIEW(view), model);
 
  g_object_unref(model); /* destroy model automatically with view */
 
  gtk_tree_selection_set_mode(gtk_tree_view_get_selection(GTK_TREE_VIEW(view)),
                              GTK_SELECTION_NONE);
 
  return view;
}
 

int
main (int argc, char ** argv)
{
/*
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
*/


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



  GtkWidget *window;
  GtkWidget *view;

  gtk_init (&argc, &argv);

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title (GTK_WINDOW (window), "Window");

  g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

  view = create_view_and_model(especialidades);

  gtk_container_add (window, view);

  gtk_widget_show_all (window);

  gtk_main ();

  return 0;
}
