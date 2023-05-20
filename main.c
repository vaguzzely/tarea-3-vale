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