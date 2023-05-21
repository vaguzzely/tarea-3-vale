#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//aquí defino las estructuras que utilizaré en esta tarea
typedef struct Tarea {
    char nombre[50];
    int prioridad;
    struct Tarea** precedentes; //
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


//esta función corresponde a la opción 4 del menú, sirve para marcar una tarea como completada (y eliminarla), si es precedente de otra tarea, esta también se elimina del [] de precedentes de la tarea con la que tenga relación.

int marcarTareaCompletada(GrafoTareas* grafo, const char* nombre) {

  //se verifica si la tarea existe, utilizando la función auxiliar buscarTareaPorNombre
    Tarea* tarea = buscarTareaPorNombre(grafo, nombre);

    if (tarea == NULL) {
        printf("Error: No se encontró la tarea especificada. :c\n");
        return 0;
    }
  

    // si la encuentra, elimina la tarea del grafo
    int indiceTarea = tarea->indice;
    free(grafo->nodos[indiceTarea]);

    // se mueven los nodos restantes una posición hacia arriba
    for (int i = indiceTarea + 1; i < grafo->numNodos; i++) {
        grafo->nodos[i - 1] = grafo->nodos[i];
        grafo->nodos[i - 1]->indice = i - 1; // se actualiza el índice del nodo
    }

    grafo->numNodos--; // se actualiza el número de nodos

    // se actualizan los precedentes de las tareas restantes
    for (int i = 0; i < grafo->numNodos; i++) {
        Tarea* tareaActual = grafo->nodos[i];
        for (int j = 0; j < tareaActual->numPrecedentes; j++) {
            if (tareaActual->precedentes[j]->indice == indiceTarea) {
                // elimina la tarea completada de los precedentes
                for (int k = j; k < tareaActual->numPrecedentes - 1; k++) {
                    tareaActual->precedentes[k] = tareaActual->precedentes[k + 1];
                }
                tareaActual->numPrecedentes--;
                break;
            }
        }
    }

    // actualiza los precedentes en la copia de los nodos
    for (int i = 0; i < grafo->numNodos; i++) {
        Tarea* tareaActual = grafo->nodos[i];
        for (int j = 0; j < tareaActual->numPrecedentes; j++) {
            if (tareaActual->precedentes[j]->indice > indiceTarea) {
                tareaActual->precedentes[j]->indice--; // actualiza el índice del precedente
            }
        }
    }
  return 1;
}


/*
int compararPrioridad(const void* a, const void* b) {
    Tarea* tarea1 = *(Tarea**)a;
    Tarea* tarea2 = *(Tarea**)b;

    // ordena en orden de prioridad
    return tarea1->prioridad - tarea2->prioridad;
}
*/
void ordenamientoTopologicoAuxPrecedencia(Tarea* tarea, int visitado[], int nivel) {
    visitado[tarea->indice] = 1; // Marcar la tarea como visitada

    // recorre las tareas precedentes y se llama recursivamente
    for (int i = 0; i < tarea->numPrecedentes; i++) {
        Tarea* precedente = tarea->precedentes[i];
        if (!visitado[precedente->indice]) {
            ordenamientoTopologicoAuxPrecedencia(precedente, visitado, nivel + 1);
        }
    }

    // muestra la tarea actual con su nivel y precedentes
    printf("%*s- %s (Prioridad: %d)\n", nivel * 2, "", tarea->nombre, tarea->prioridad);
}

//función auxiliar que compara la prioridad y precedencia de las tareas, de esta forma se imprime de forma ordenada cuando se llama a mostrar tareas
int compararPrioridadPrecedencia(const void* a, const void* b) {
    Tarea* tarea1 = *(Tarea**)a;
    Tarea* tarea2 = *(Tarea**)b;

    // Comparar primero por precedencia
    if (tarea1->numPrecedentes != tarea2->numPrecedentes) {
        return tarea1->numPrecedentes - tarea2->numPrecedentes;
    }

    // si tienen la misma precedencia, comparar por prioridad
    return tarea1->prioridad - tarea2->prioridad;
}

//muestra las tareas
void mostrarTareas(GrafoTareas* grafo) {
    printf("Tareas por hacer, ordenadas por prioridad y precedencia:\n");

    // crear una copia de las tareas del grafo
    Tarea* tareasOrdenadas[grafo->numNodos];
    for (int i = 0; i < grafo->numNodos; i++) {
        tareasOrdenadas[i] = grafo->nodos[i];
    }

    // ordena las tareas por prioridad y precedencia
    qsort(tareasOrdenadas, grafo->numNodos, sizeof(Tarea*), compararPrioridadPrecedencia);

    // imprime las tareas en orden y con su número correspondiente c:
    for (int i = 0; i < grafo->numNodos; i++) {
        Tarea* tarea = tareasOrdenadas[i];
        printf("%d. %s (Prioridad: %d)", i + 1, tarea->nombre, tarea->prioridad);
        if (tarea->numPrecedentes > 0) {
            printf(" - Precedente: ");
            for (int j = 0; j < tarea->numPrecedentes; j++) {
                printf("%s", tarea->precedentes[j]->nombre);
                if (j < tarea->numPrecedentes - 1) {
                    printf(", ");
                }
            }
        }
        printf("\n");
    }
}


int main() {
    GrafoTareas* grafo = crearGrafoTareas();

    int opcion;
    char nombre[50];
    int prioridad;
    char tarea1[50];
    char tarea2[50];
   // char nombre_archivo[100];

    do {
        printf("\nBienvenido ૮ ˶ᵔ ᵕ ᵔ˶ ა\n");
        printf("\n ₊✩°｡⋆˚⁺Este programa te ayudará a organizar tus tareas por hacer. El menú te permite hacer diversas cosas, espero te guste ⁺˚⋆｡°✩₊\n");
        printf("\n ₊✩°｡⋆˚⁺ ₊✩°｡⋆˚⁺Menú⁺˚⋆｡°✩₊⁺˚⋆｡°✩₊\n");
        printf("1. Agregar tarea\n");
        printf("2. Establecer precedencia entre tareas\n");
        printf("3. Mostrar tareas por hacer\n");
        printf("4. Marcar tarea como completada\n");
        printf("5. Salir\n");
        printf("Ingrese una opción: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("Ingrese el nombre de la tarea: ");
                scanf("%s", nombre);
                printf("Ingrese la prioridad de la tarea: ");
                scanf("%d", &prioridad);
                agregarTarea(grafo, nombre, prioridad);
                printf("Tarea agregada exitosamente. (>ᴗ<)\n");
                break;
            case 2:
                printf("Ingrese el nombre de la tarea precedente: ");
                scanf("%s", tarea1);
                printf("Ingrese el nombre de la tarea que debe realizarse después: ");
                scanf("%s", tarea2);
                if (establecerPrecedencia(grafo, tarea1, tarea2) == 1){
                  printf("Precedencia establecida exitosamente.(>ᴗ<)\n");
                    }
                break;
            case 3:
                mostrarTareas(grafo);
                break;
            case 4:
                printf("Ingrese el nombre de la tarea completada: ");
                scanf("%s", nombre);
                if (marcarTareaCompletada(grafo, nombre) == 1){
                printf("Tarea marcada como completada.(>ᴗ<)\n");}
                break;
            case 5:
                printf("Saliendo del programa...⸜(｡˃ ᵕ ˂ )⸝\n");
                break;
            default:
                printf("Opción inválida. Intente nuevamente.(ᴗ_ ᴗ。)\n");
        }
    
    } while (opcion != 5);
  
  return 0;
}