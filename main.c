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
