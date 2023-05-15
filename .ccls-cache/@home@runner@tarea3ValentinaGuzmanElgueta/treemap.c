#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}
/*1.- Implemente la función *createTreeMap* en el archivo treemap.c. Esta función recibe la función de comparación de claves y crea un mapa (TreeMap) inicializando sus variables. 
El siguiente código muestra como inicializar la función de comparación. Reserve memoria, inicialice el resto de variables y retorne el mapa.*/

  TreeMap * createTreeMap(int (*lt) (void* key1, void* key2)) 
{
  TreeMap * nuevo = (TreeMap*)malloc(sizeof(TreeMap));
  nuevo -> root = NULL;
  nuevo -> current = NULL;
  nuevo->lower_than = lt;
  return nuevo;
}

/*
3.- Implemente la función void insertTreeMap(TreeMap * tree, void* key, void * value). Esta función inserta un nuevo dato (key,value) en el árbol y hace que el current apunte al nuevo nodo.
Para insertar un dato, primero debe realizar una búsqueda para encontrar donde debería ubicarse. Luego crear el nuevo nodo y enlazarlo. Si la clave del dato ya existe retorne sin hacer nada (recuerde que el mapa no permite claves repetidas).
   
    void insertTreeMap(TreeMap* tree, void* key, void* value){


    }*/

/*Pair * searchTreeMap(TreeMap * tree, void* key) 
{
  TreeNode* node = tree->root; // empieza la búsqueda en la raíz
  while (node != NULL) // mientras no haya llegado al final del árbol
  {
    if (is_equal(tree, node->pair->key, key)) { // si se logra encontrar la clave
            tree->current = node; // actualiza el current
            return node->pair; // retorna el pair asociado al nodo q se encontró
        } else if (tree->lower_than(key, node->pair->key)) { // si la clave es menor que la clave del nodo actual, se va para la izquierda
            node = node->left;
        } else 
    { // si la clave es menor que la clave del nodo actual, se va a la derecha
            node = node->right;
    }
  }
  return NULL;
}*/

void insertTreeMap(TreeMap * tree, void* key, void * value) {
  if (searchTreeMap(tree, key) != NULL) return; // si la clave ya existe en el árbol, retorna sin hacer nada
  TreeNode * new = createTreeNode(key, value); // crea un nuevo nodo con la clave y valor dados
  TreeNode * parent = NULL;
  TreeNode * current = tree->root;
  do{
    // busca la posición donde insertar el nuevo nodo
    parent = current;
    if (tree->lower_than(key, current->pair->key)) {
      current = current->left;
    } else {
      current = current->right;
    }
  }while (current != NULL);
  
  
  new->parent = parent; // enlaza el nuevo nodo con su padre
  
  if (parent == NULL) { // si el árbol está vacío
    tree->root = new;
  } else if (tree->lower_than(key, parent->pair->key)) { // si la clave es menor que la clave del padre
    parent->left = new; // inserta el nuevo nodo a la izquierda del padre
  } else {
    parent->right = new; // inserta el nuevo nodo a la derecha del padre
  }
  tree->current = new; // hace que el current apunte al nuevo nodo
}

/*
4.- Implemente la función TreeNode * minimum(TreeNode * x). Esta función retorna el **nodo con la mínima clave** ubicado en el subárbol con raiz x. Para obtener el nodo tiene que, a partir del nodo x, irse por la rama izquierda hasta llegar al final del subárbol. Si x no tiene hijo izquierdo se retorna el mismo nodo.
   
    TreeNode * minimum(TreeNode * x){


        return NULL;
    }
*/
TreeNode * minimum(TreeNode * x)
{
  while (x->left != NULL)
  {
    x = x->left;
  }
  return x;
}

/*
5.- Implemente la función void removeNode(TreeMap * tree, TreeNode* node). Esta función elimina el nodo *node* del árbol *tree*. Recuerde que para eliminar un node existen 3 casos:
**Nodo sin hijos:** Se anula el puntero del padre que apuntaba al nodo
**Nodo con un hijo:** El padre del nodo pasa a ser padre de su hijo
**Nodo con dos hijos:** Descienda al hijo derecho y obtenga el menor nodo del subárbol (con la función minimum). Reemplace los datos (key,value) de *node* con los del nodo "minimum". Elimine el nodo minimum (para hacerlo puede usar la misma función *removeNode*).

    void removeNode(TreeMap * tree, TreeNode* node) {


    }

La función removeNode será usada por la función *eraseTreeMap* para eliminar datos del árbol usando la clave.

    void eraseTreeMap(TreeMap * tree, void* key){
        if (tree == NULL || tree->root == NULL) return;
        if (searchTreeMap(tree, key) == NULL) return;
        TreeNode* node = tree->current;
        removeNode(tree, node);
    } 

*/
void removeNode(TreeMap * tree, TreeNode* node) 
{ if (node == NULL) {
        return; // el nodo no existe
    }
    
    if (node->left == NULL && node->right == NULL) {
        
        if (node->parent == NULL) {
            // nodo a eliminar es el root del árbol
            tree->root = NULL;
        }
        else if (node->parent->left == node) {
            node->parent->left = NULL;
        }
        else {
            node->parent->right = NULL;
        }
        free(node);
        return;
    } 
    
    if (node->left != NULL && node->right != NULL) {
        // El nodo a eliminar tiene dos hijos
        TreeNode * aux = minimum(node->right);
        node->pair->key = aux->pair->key;
        node->pair->value = aux->pair->value;
        removeNode(tree, aux);
        return;
    }
    
    // El nodo a eliminar tiene un hijo
    TreeNode * aux = (node->left != NULL) ? node->left : node->right;
    if (node->parent == NULL) {
        // nodo a eliminar es el root del árbol
        tree->root = aux;
    }
    else if (node->parent->left == node) {
        node->parent->left = aux;
    }
    else {
        node->parent->right = aux;
    }
    aux->parent = node->parent;
    free(node);
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}

/*
2.- Implemente la función Pair* searchTreeMap(TreeMap* tree, void* key), la cual busca el nodo con clave igual a key y retorna el **Pair** asociado al nodo. Si no se encuentra la clave retorna NULL.
Recuerde hacer que el current apunte al nodo encontrado.

    Pair* searchTreeMap(TreeMap* tree, void* key) {


        return NULL;
    }
*/



Pair * searchTreeMap(TreeMap * tree, void* key) 
{
  TreeNode* node = tree->root; // empieza la búsqueda en la raíz
  while (node != NULL) // mientras no haya llegado al final del árbol
  {
    if (is_equal(tree, node->pair->key, key)) { // si se logra encontrar la clave
            tree->current = node; // actualiza el current
            return node->pair; // retorna el pair asociado al nodo q se encontró
        } else if (tree->lower_than(key, node->pair->key)) { // si la clave es menor que la clave del nodo actual, se va para la izquierda
            node = node->left;
        } else 
    { // si la clave es menor que la clave del nodo actual, se va a la derecha
            node = node->right;
    }
  }
  return NULL;
}

/*7.- La función Pair* upperBound(TreeMap* tree, void* key) retorna el **Pair** con clave igual a key. En caso de no encontrarlo retorna el primer par asociado a una clave mayor o igual a key. 
Para implementarla puede realizar una búsqueda normal y usar un puntero a nodo auxiliar ub_node que vaya guardando el nodo con la menor clave *mayor o igual a key*. Finalmente retorne el par del nodo ub\_node.

    Pair* upperBound(TreeMap* tree, void* key){
        

    }

*/

Pair * upperBound(TreeMap * tree, void* key) 
{
  TreeNode *ub_node = NULL;
  TreeNode *aux = tree->root;
  while(aux != NULL)
  {
    if(is_equal(tree, aux->pair->key, key))
    {
      return aux->pair;
    }
    if(tree->lower_than(key, aux->pair->key))
    {
      ub_node = aux;
            aux = aux->left;
        }
    else
    {
      aux = aux->right;
    }
  }
    if(ub_node == NULL)
    {
      return NULL;
    }
    return ub_node->pair;
}
/*6.- Implemente las funciones para recorrer la estructura: Pair* firstTreeMap(TreeMap* tree) retorna el primer **Pair** del mapa (el menor). Pair* nextTreeMap(TreeMap* tree)  retornar el siguiente **Pair** del mapa a partir del puntero TreeNode* current. Recuerde actualizar este puntero.

    Pair * firstTreeMap(TreeMap * tree) {
        

        return NULL;
    }

    Pair * nextTreeMap(TreeMap * tree) {
       

        return NULL;
    }
*/
Pair * firstTreeMap(TreeMap * tree) 
{
  if (tree == NULL || tree->root == NULL) return NULL; // si el árbol está vacío, retorna NULL
  
  TreeNode * current = tree->root;
  
// busca el nodo más a la izquierda del árbol
  do{
    current = current->left;
  }while (current->left != NULL);

  tree->current = current; // actualiza el current
  return current->pair; // retorna el pair asociado al nodo encontrado
}

Pair * nextTreeMap(TreeMap * tree) 
{
  TreeNode *aux = tree->current;
  if(aux->right != NULL)
  {
    aux = aux->right;
    aux = minimum(aux);
    tree->current = aux;
    return aux->pair;
  }

    if(aux->right == NULL)
    {
      while(aux != NULL)
      {
        if(aux->parent == NULL)
        {
          return NULL;
        }
        if(aux == tree->root) 
        {
    return NULL;
        }
        if(tree->lower_than(aux->pair->key, aux->parent->pair->key) == 1)
        {
          aux = aux->parent;
          tree->current = aux;
          return aux->pair;
        } 
        else 
        {
          aux = aux->parent;
        }
      }
    }
  return NULL;
}

