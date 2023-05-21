La tarea fue realizada de forma individual.

(｡˃ ᵕ ˂ )

Se utilizaron las herraminetas replit y github:

Link repositorio de github: https://github.com/vaguzzely/tarea3ValentinaGuzm-nElgueta
Link replit: https://replit.com/join/avhfzlwwyj-vaguzzely     ó      https://replit.com/@vaguzzely/tarea3ValentinaGuzmanElgueta#main.c


Coevaluación:

no aplica

Archivo README:

----------------------------------
El menú se ve así:
Bienvenido ૮ ˶ᵔ ᵕ ᵔ˶ ა
₊✩°｡⋆˚⁺Este programa te ayudará a organizar tus tareas por hacer. El menú te permite hacer diversas cosas, espero te guste ⁺˚⋆｡°✩₊

₊✩°｡⋆˚⁺ ₊✩°｡⋆˚⁺Menú⁺˚⋆｡°✩₊⁺˚⋆｡°✩₊
1. Agregar tarea
2. Establecer precedencia entre tareas
3. Mostrar tareas por hacer
4. Marcar tarea como completada
5. Salir
================================================================
---------------------------------
El usuario debe ingresar la opción que quiera.

Todas las funciones realizan lo que se pide, el único detalle a recordar es que las tareas no pueden tener más de una tarea precedente.
Al ingresar por consola las tareas que aparecen en el ejemplo del documento (las ingresé en deroden), estas se muestran ordenadas y con los precedentes correspondientes, tal cual aparacen en el documento tarea 3 c:

Primero ingreso las tareas desordenadas (sin ordenarlas por prioridad)
al usar la opción 3 (mostrarTareas), esta las imprime ordenadas por prioridad de esta forma:

Ingrese una opción: 3
Tareas por hacer, ordenadas por prioridad y precedencia:
1. TD (Prioridad: 1)
2. TB (Prioridad: 2)
3. TA (Prioridad: 3)
4. TC (Prioridad: 4)
5. TE (Prioridad: 5)
-
luego establezco la precedencia (de la misma forma que en el ejemplo del documento tarea 3), y esta se establece adecuadamente,
al mostrar las tareas, estas se imprimen de forma ordenada, considerando la prioridad y la precedencia, tal cual en el documento tarea 3:

Ingrese una opción: 3
Tareas por hacer, ordenadas por prioridad y precedencia:
1. TD (Prioridad: 1)
2. TA (Prioridad: 3)
3. TB (Prioridad: 2) - Precedente: TA
4. TC (Prioridad: 4) - Precedente: TB
5. TE (Prioridad: 5) - Precedente: TD

Al marcar la tarea TA como completada (eliminar la tarea TA), el programa imprime lo siguiente cuando se muestran las tareas por hacer:

Tareas por hacer, ordenadas por prioridad y precedencia:
1. TD (Prioridad: 1)
2. TB (Prioridad: 2)
3. TC (Prioridad: 4) - Precedente: TB
4. TE (Prioridad: 5) - Precedente: TD

----------------------------------------------------------------

Si desea ver una descripión con más detalle de cada una de las funciones, puede leer lo siguiente:

Función 1:
Nombre: agregarTarea(GrafoTareas* grafo, const char* nombre, int prioridad)
Descripción: Permite al usuario ingresar el nombre de la tarea y un dato tipo int que corresponde a la prioridad. Se agrega al grafo
Posibles causas de errores: El programa no da errores mientras se ingrese bien lo que se le pide.

Función 2:
Nombre: establecerPrecedencia(GrafoTareas* grafo, const char* nombreTarea1, const char* nombreTarea2)
Descripción: Permite al usuario establecer una relación de precedencia entre tareas, se le pide al usuario ingresar el nombre de dos tareas (ya ingresadas con anterioridad al programa),
la primera que se ingresa es la que será precedente de la segunda que se ingrese.
Posibles causas de errores: Esta función marcha bien siempre y cuando las tareas ingresadas por el usuario existan.

Función 3:
Nombre: marcarTareaCompletada(GrafoTareas* grafo, const char* nombre) 
Descripción: esta función corresponde a la opción 4 del menú, sirve para marcar una tarea como completada (y eliminarla), si es precedente de otra tarea, esta también se elimina del []
de precedentes de la tarea con la que tenga relación.
Posibles causas de errores: Esta función trabaja correctamente siempre y cuando la tarea ingresada por el usuario exista. El usuario debe ingresar lo que se le pida.

Función 4:
Nombre: void mostrarTareas(GrafoTareas* grafo
Descripción: Muestra las tareas en el orden correspondiente, respetando las relaciones de prioridad y precedencia.
Esta función trabaja correctamente.

---------------------------------------------------------------------------------
(｡˃ ᵕ ˂ )(｡˃ ᵕ ˂ )(｡˃ ᵕ ˂ )(｡˃ ᵕ ˂ )(｡˃ ᵕ ˂ )(｡˃ ᵕ ˂ )(｡˃ ᵕ ˂ )(｡˃ ᵕ ˂ )(｡˃ ᵕ ˂ )(｡˃ ᵕ ˂ )

La tarea no tiene implementado un archivo del tipo grafos.c o grafos.h porque al hacerlo, en el main no quedaba ninguna función que se pedía para la tarea, tan solo quedaba el menú, por lo tanto
no quise que quedara así y dejé todo en un mismo archivo main, espero no hayan inconvenientes, pero de así serlo, agradecería un comentario de retroalimentación para comprender mejor el tema c:,
muchas gracias por revisar la tarea!!