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
void* pushFront(List* list, void * data) {
    if (list == NULL) return; // verifica si la lista existe

    Node * newNode = createNode(data) ; //crea un nuevo nodo con el dato

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

void pushCurrent(List * list, void * data) {
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
    return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}