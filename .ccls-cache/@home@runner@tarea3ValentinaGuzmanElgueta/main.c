#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definición de estructuras

typedef struct NodoTarea {
    char nombre[50];
    int prioridad;
    struct NodoTarea** precedentes;
    int num_precedentes;
    int indice;
    int completada; // Nuevo campo para indicar si la tarea está completada o no
} NodoTarea;

typedef struct GrafoTareas {
    NodoTarea* nodos[50];
    int num_nodos;
} GrafoTareas;

typedef struct Accion {
    int tipo;
    void* data;
} Accion;

typedef struct PilaAcciones {
    Accion* acciones[50];
    int num_acciones;
} PilaAcciones;

// Funciones auxiliares para la pila

typedef struct NodoPila {
    Accion* accion;
    struct NodoPila* siguiente;
} NodoPila;

typedef struct Pila {
    NodoPila* tope;
} Pila;

Pila* crearPila() {
    Pila* pila = (Pila*)malloc(sizeof(Pila));
    pila->tope = NULL;
    return pila;
}

void apilar(Pila* pila, Accion* accion) {
    NodoPila* nuevoNodo = (NodoPila*)malloc(sizeof(NodoPila));
    nuevoNodo->accion = accion;
    nuevoNodo->siguiente = pila->tope;
    pila->tope = nuevoNodo;
}

Accion* desapilar(Pila* pila) {
    if (pila->tope == NULL) {
        return NULL;
    }

    NodoPila* nodoDesapilado = pila->tope;
    Accion* accion = nodoDesapilado->accion;
    pila->tope = nodoDesapilado->siguiente;
    free(nodoDesapilado);
    return accion;
}


// Funciones auxiliares



GrafoTareas* crearGrafoTareas() {
    GrafoTareas* grafo = (GrafoTareas*)malloc(sizeof(GrafoTareas));
    grafo->num_nodos = 0;
    return grafo;
}

void agregarTarea(GrafoTareas* grafo, const char* nombre, int prioridad) {
    NodoTarea* nuevaTarea = (NodoTarea*)malloc(sizeof(NodoTarea));
    strcpy(nuevaTarea->nombre, nombre);
    nuevaTarea->prioridad = prioridad;
    nuevaTarea->precedentes = NULL;
    nuevaTarea->num_precedentes = 0;
    nuevaTarea->indice = grafo->num_nodos; // Asignar el índice de la tarea

    grafo->nodos[grafo->num_nodos] = nuevaTarea;
    grafo->num_nodos++;
}

NodoTarea* buscarTareaPorNombre(GrafoTareas* grafo, const char* nombre) {
    for (int i = 0; i < grafo->num_nodos; i++) {
        if (strcmp(grafo->nodos[i]->nombre, nombre) == 0) {
            return grafo->nodos[i];
        }
    }
    return NULL;
}

void establecerPrecedencia(GrafoTareas* grafo, const char* nombreTarea1, const char* nombreTarea2) {
    NodoTarea* tarea1 = buscarTareaPorNombre(grafo, nombreTarea1);
    NodoTarea* tarea2 = buscarTareaPorNombre(grafo, nombreTarea2);

    if (tarea1 == NULL || tarea2 == NULL) {
        printf("Error: No se encontró alguna de las tareas especificadas.\n");
        return;
    }

    tarea2->precedentes = realloc(tarea2->precedentes, (tarea2->num_precedentes + 1) * sizeof(NodoTarea*));
    tarea2->precedentes[tarea2->num_precedentes] = tarea1;
    tarea2->num_precedentes++;
}

void marcarTareaCompletada(GrafoTareas* grafo, const char* nombre) {
    NodoTarea* tarea = buscarTareaPorNombre(grafo, nombre);

    if (tarea == NULL) {
        printf("Error: No se encontró la tarea especificada.\n");
        return;
    }

    // Eliminar la tarea del grafo
    int indiceTarea = tarea->indice;
    free(grafo->nodos[indiceTarea]);

    // Mover los nodos restantes una posición hacia arriba
    for (int i = indiceTarea; i < grafo->num_nodos - 1; i++) {
        grafo->nodos[i] = grafo->nodos[i + 1];
        grafo->nodos[i]->indice = i; // Actualizar el índice del nodo
    }

    grafo->num_nodos--; // Actualizar el número de nodos del grafo
}

void deshacerUltimaAccion(GrafoTareas* grafo, PilaAcciones* pilaAcciones) {
    if (pilaAcciones->num_acciones == 0) {
        printf("No hay acciones que deshacer.\n");
        return;
    }
    NodoTarea->completada = 1;
    Accion* ultimaAccion = pilaAcciones->acciones[pilaAcciones->num_acciones - 1];

    switch (ultimaAccion->tipo) {
        case 0: { // Agregar tarea
            NodoTarea* tareaEliminada = (NodoTarea*)ultimaAccion->data;
            grafo->nodos[grafo->num_nodos] = tareaEliminada;
            tareaEliminada->indice = grafo->num_nodos;
            grafo->num_nodos++;
            printf("Se deshizo la acción: Agregar tarea.\n");
            break;
        }
        case 2: { // Establecer precedencia
            char* nombreTarea1 = (char*)ultimaAccion->data;
            char* nombreTarea2 = (char*)ultimaAccion->data + sizeof(char) * 50;
            establecerPrecedencia(grafo, nombreTarea2, nombreTarea1); // Intercambiar el orden de las tareas
            printf("Se deshizo la acción: Establecer precedencia.\n");
            break;
        }
        case 3: { // Marcar tarea como completada
          NodoTarea* tareaMarcada = (NodoTarea*)ultimaAccion->data;
          tareaMarcada->completada = 0; // Marcar la tarea como no completada
          printf("Se deshizo la acción: Marcar tarea como completada.\n");
          break;
        }


        default:
            printf("Acción desconocida.\n");
            break;
    }

    // Liberar memoria de la última acción deshecha
    free(ultimaAccion->data);
    free(ultimaAccion);
    pilaAcciones->num_acciones--;
}

