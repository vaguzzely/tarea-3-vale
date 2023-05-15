#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "treemap.h"
//#include#include#include#include#include

typedef struct 
{
  char* nombreTarea;
  int prioridad;
  List* listaPrecedentes;
} Tarea;


/*1. Agregar tarea (nombre, prioridad): La usuaria ingresa el nombre de una tarea y su prioridad (un número entero). La aplicación agrega la tarea a la lista de tareas por hacer.*/
void registrarTarea()
{
}

/*2. Establecer precedencia entre tareas (tarea1, tarea2): La usuaria ingresa los nombres de dos tareas existentes. La aplicación establece que la tarea1 debe realizarse antes que la tarea2.*/
void establecerPrecedencia()
{
  
}



/*3. Mostrar tareas por hacer: La aplicación muestra todas las tareas pendientes, ordenadas según su prioridad y teniendo en cuenta las relaciones de precedencia.*/
void mostrarTareasPendientes()
{
}

/*4. Marcar tarea como completada (nombre): La usuaria ingresa el nombre de una tarea. La aplicación marca la tarea como completada y la elimina de la lista de tareas por hacer. Si la tarea tiene relaciones de precedencia, se debe colocar una advertencia: “¿estás seguro que desea eliminar la tarea?”*/

void marcarTareaCompletada()
{
  
}

/*5. Deshacer última acción: La aplicación deshace la última acción realizada por la usuaria, ya sea agregar/eliminar una tarea, establecer precedencia o marcar una tarea como completada. Si no hay acciones que deshacer, se debe mostrar un aviso.*/

void deshacerUltimaAccion()
{}


/*6. Cargar datos de tareas desde un archivo de texto (nombre_archivo): La aplicación carga los datos de las tareas pendientes desde un archivo de texto indicado por la usuaria.
*/
void cargarDatosTareas()
{}


int main()
{}