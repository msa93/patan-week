#QLib
QLib es una librería escrita para manejar distintas estructuras de datos. 

####QSList
QSList es una lista simplemente enlazada.

- Inicializar una lista
```c
QSList *list = NULL;
```
- Agregar un elemento al inicio de la lista
```c
QSList *list_int = NULL;
QSList *list_str = NULL;
/* Agregar enteros */
list_int = q_slist_prepend (list_int, INT_TO_QPOINTER (10));
list_int = q_slist_prepend (list_int, INT_TO_QPOINTER (60));
list_int = q_slist_prepend (list_int, INT_TO_QPOINTER (90));
list_int = q_slist_prepend (list_int, INT_TO_QPOINTER (50));
/* Para agregar enteros da igual hacer esto: (pero nos aparecera un feo Warning)
list_int = q_slist_prepend (list_int, 80);
list_int = q_slist_prepend (list_int, 80);
/* Agregar strings. strdup es parte de las librerías de <string.h> en C */
list_str = q_slist_prepend (list_int, strdup ("hola"));
list_str = q_slist_prepend (list_int, strdup ("y tu como"));
list_str = q_slist_prepend (list_int, strdup ("te"));
list_str = q_slist_prepend (list_int, strdup ("llamas"));
```



