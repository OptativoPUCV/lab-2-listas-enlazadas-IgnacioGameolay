#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

// Crea una lista vacía. Inicializa los punteros head, tail y current a NULL.
List * createList() {
    // Reserva memoria para una nueva lista.
    List* newList = (List*) malloc(sizeof(List));

    // Inicializa los punteros de la lista: cabeza (head), cola (tail) y el actual (current) en NULL.
    newList->head = NULL;
    newList->tail = NULL;
    newList->current = NULL;

    // Devuelve la lista vacía creada.
    return newList;
}

// Coloca el puntero current en el primer nodo de la lista y devuelve su dato.
void * firstList(List * list) {
    // Si la lista está vacía, devuelve NULL.
    if (list == NULL || list->head == NULL) {
        return NULL;
    }
    // Si la lista no está vacía, coloca current en el primer nodo.
    list->current = list->head;

    // Devuelve el dato del primer nodo.
    return list->current->data;
}

// Mueve el puntero current al siguiente nodo de la lista y devuelve su dato.
void * nextList(List * list) {
    // Si la lista o el nodo actual no existen o el siguiente nodo es NULL, devuelve NULL.
    if (list == NULL || list->current == NULL || list->current->next == NULL) {
        return NULL;
    }
    // Mueve el puntero current al siguiente nodo.
    list->current = list->current->next;

    // Devuelve el dato del nodo siguiente.
    return list->current->data;
}

// Coloca el puntero current en el último nodo de la lista y devuelve su dato.
void * lastList(List * list) {
    // Si la lista está vacía o no tiene un último nodo, devuelve NULL.
    if (list == NULL || list->tail == NULL) {
        return NULL;
    }
    // Si la lista no está vacía, coloca current en el último nodo.
    list->current = list->tail;

    // Devuelve el dato del último nodo.
    return list->current->data;
}

// Mueve el puntero current al nodo anterior de la lista y devuelve su dato.
void * prevList(List * list)  {
    // Si la lista o el nodo actual no existen o el nodo anterior es NULL, devuelve NULL.
    if (list == NULL || list->current == NULL || list->current->prev == NULL) {
        return NULL;
    }
    // Mueve el puntero current al nodo anterior.
    list ->current = list->current->prev;

    // Devuelve el dato del nodo anterior.
    return list->current->data;
}

/* PUSHFRONT
Se verifica si list es null , si la lista no existe, retorna sin hacer nada
se crea e inicializa un nuevo nodo con createNode(data)
Se verifica si la lista esta vacia, si lo esta, el nuevo nodo se convierte en head y tail
si no, el nuevo nodo paunta al nodo que antes era head
el antiguo head actualiza su prev para apuntar al nuevo nodo y
se actializa head para que apunte al nuevo

*/
void pushFront(List* list, void * data) {
    if (list == NULL) return; // verifica si la lista existe

    Node * newNode = createNode(data); //crea un nuevo nodo con el dato

    if (list->head == NULL) { //si la lista esta vacia
        list->head = list->tail = newNode; // El nuevo nodo es el unico en la lista
    } else {
        newNode->next = list->head; // enlaza el nuevo nodo con el antiguo head
        list->head->prev = newNode; // enlaza el antiguo head con el nuevo nodo
        list->head = newNode; // actualiza head para que apunte al nuevo nodo
    }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

/* PushCurrent
Verifica si list o list->current son null, si la lista no existe o current
no apunta a un nodo, simplemente retorna
Crea e inicializa un nuevo nodo con createNode(data)
Ajusta los punteros para insertar el nuevo nodo despues del current
Si current-> next no es Null, ajusta su prev para apuntar al nuevo nodo
manteniendo la conexion en ambas direcciones
Si current era el ultimo nodo actualiza el tail
actualiza el current-> para enlazar en nuevo nodo

*/
void pushCurrent(List * list, void * data) {
    if (list == NULL || list->current == NULL ) return; //verifica si la lista o current existen
    Node * newNode = createNode(data); // crea un nuevo nodo con el dato
    newNode->next = list->current->next; // el nuevo nodo apunta al siguiente de current
    newNode->prev = list->current; //el nuevo nodo apunta a current como previo

    if (list->current->next != NULL) {
        list->current->next->prev = newNode; // ajusta el anterior del siguiente nodo
    } else {
        list->tail = newNode;  //si current era el ultimo nodo, actualiza tail
    }
    list->current->next = newNode; // Enlaza el nodo actual con el nuevo nodo

}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

/* POPCURRENT
verifica si list o list->current son null
si la lista no existe o current no apunta a un  nodo retorna null
guarda el nodo a eliminar y su dato 
esto es necesario para retornar el dato despues de liberar la memoria
si current es el primer nodo: 
mueve head al siguiente nodo,, si el nuevo head existe, ajusta
su prev a null, si la lista queda vacia, ajusta tail a null
si current es el ultimo nodo:
mueve tail al nodo anterior, ajusta tail->next a null
si current esta en el medio, ajusta los punteros prev y next de los
nodos adyacentes para eliminar el nodo actual de la lista
nueve el current al siguiente nodo, permitiendo seguir iterando por
la lista sin perder la referencia
libera la memoria del nodo eliminado y retorna el dato

*/
void * popCurrent(List * list) {
    if (list == NULL || list->current == NULL) return NULL; //verifica si la lista o current existen

    Node * nodeToRemove = list->current; // guarda el nodo a eliminar
    void * data = nodeToRemove->data; // guarda el dato a retornar
    //si el nodo a eliminar es el primero
    if (nodeToRemove == list->head) {
        list->head = nodeToRemove->next; //mueve head al siguiente nodo
        if (list->head) list->head->prev = NULL; //si hay un nuevo head, ajusta su prev
        else list->tail = NULL; //si la lista queda vacia, tail tambien es NULL
    }
    //si el nodo a eliminar es el ultimo
    else if (nodeToRemove == list->tail) {
        list->tail = nodeToRemove->prev; // mueve tail al nodo anterior
        if (list->tail) list->tail->next = NULL; //si hay un nuevo tail, ajusta su next
    }
    //si el nodo esta en el medio
    else {
        nodeToRemove->prev->next = nodeToRemove->next; //salta el nodo a eliminar
        nodeToRemove->next->prev = nodeToRemove->prev; //ajusto el nodo siguente
    }
    list->current = nodeToRemove->next; //mueve current al siguiente nodo
    free(nodeToRemove); //libera la memoria dle nodo eliminado
    return data; //retorna el dato del nodo eliminado
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}