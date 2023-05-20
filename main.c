#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//aquí defino las estructuras que utilizaré en esta tarea
typedef struct Tarea {
    char nombre[50];
    int prioridad;
    struct Tarea** precedentes; //array
    int numPrecedentes;
    int indice;
} Tarea;

//defino la estructura del grafo
typedef struct GrafoTareas {
    Tarea* nodos[50];
    int numNodos;
} GrafoTareas;

//funciones del grafo para que funcione bien en el programa

GrafoTareas* crearGrafoTareas() {
    GrafoTareas* grafo = (GrafoTareas*)malloc(sizeof(GrafoTareas));
    grafo->numNodos = 0;
    return grafo;
}

//función que agrega la tarea ingresada por el usuario
void agregarTarea(GrafoTareas* grafo, const char* nombre, int prioridad) {
    Tarea* nuevaTarea = (Tarea*)malloc(sizeof(Tarea));
    strcpy(nuevaTarea->nombre, nombre);
    nuevaTarea->prioridad = prioridad;
    nuevaTarea->precedentes = NULL;
    nuevaTarea->numPrecedentes = 0;
    nuevaTarea->indice = grafo->numNodos; // Asignar el índice de la tarea
    
    grafo->nodos[grafo->numNodos] = nuevaTarea;
    grafo->numNodos++;
}

//función auxiliar para la búsqueda de la tarea a través del nombre, esta se utiliza principalmente al momento de establecer precedencia ya que en esa función no se puede establecer precedencia entre tareas no existentes (que no se han ingresado con anterioriodad por el usuario)
Tarea* buscarTareaPorNombre(GrafoTareas* grafo, const char* nombre) {
    for (int i = 0; i < grafo->numNodos; i++) {
        if (strcmp(grafo->nodos[i]->nombre, nombre) == 0) {
            return grafo->nodos[i];
        }
    }
    return NULL;
}


//función que establece la precedencia entre tareas, se le pide al usuario ingresar el nombre de dos tareas (ya ingresadas con anterioridad al programa), la primera que se ingresa es la que será precedente de la segunda que se ingresa

int establecerPrecedencia(GrafoTareas* grafo, const char* nombreTarea1, const char* nombreTarea2) {
    Tarea* tarea1 = buscarTareaPorNombre(grafo, nombreTarea1);
    Tarea* tarea2 = buscarTareaPorNombre(grafo, nombreTarea2);

    if (tarea1 == NULL || tarea2 == NULL) {
        printf("Error: No se encontró alguna de las tareas especificadas.\n");
        return 0;
    }
  
    tarea2->precedentes = realloc(tarea2->precedentes, (tarea2->numPrecedentes + 1) * sizeof(Tarea*));
    tarea2->precedentes[tarea2->numPrecedentes] = tarea1;
    tarea2->numPrecedentes++;
  return 1;
}