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

List * createList() 
{
  List* lista=(List*) malloc(sizeof(List));
  lista -> head = NULL;
  lista -> tail = NULL;
  lista-> current = NULL;
  return lista;
}

void * firstList(List * list) 
{
  if(!list->head) return NULL;
  list->current=list->head;
  return (list->head->data);
}

void * nextList(List * list) 
{
  //si no tiene nodos retorna null
  if (list->current == NULL) return NULL;
  //si el sgte a mi current no existe retorna null
  if (list->current->next == NULL) return NULL;
  //si la lista tiene datos, y el current no es el tail
  list->current = list->current->next;
  
  return list->current->data;
}

void * lastList(List * list) 
{
  list->current = list->tail;
  return list->current->data;
}

void * prevList(List * list) 
{
  if (list->current == NULL) return NULL;
  if (list->current->prev == NULL) return NULL;
  list->current = list->current->prev;
  return list->current->data;
}

void pushFront(List * list, void * data) 
{
  Node* n = createNode(data);
  n->next = list->head;
  if (list->head)
  {
    list->head->prev = n;
  }
  list->head = n;
  n->prev = NULL;

  if(list->tail == NULL)
    list->tail = list->head;
  
}

void pushBack(List * list, void * data) 
{
  list->current = list->tail;
  pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) 
{
  Node* nodo = createNode(data);
  nodo->prev = list->head;
  list->tail = nodo;
  if (list->head == NULL)
    list->head = nodo;
  
  if (list->head)
  {
    Node* aux = list->current;
    list->tail->prev = aux;
    
    nodo->next = list->current;
    aux->next = nodo;
  }
  else
  {
    pushFront(list,data);
  }
}

void DestruirNodo(Node* nodo)
{
  free(nodo);
}

void * popFront(List * list) 
{
  list->current = list->head;
  return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) 
{
  Node* aux;
  if(list->head)
  {
    if (list->current == list->head)
    {
      list->head->prev = NULL;
      aux = list->head;
      list->head = list->current->next;
      free(aux);
    }

    if(list->current == list->tail)
    {
      aux = list->tail;
      list->tail = list->current->prev;
      list->tail->next = NULL;
      free(aux);
    }
  }
  return NULL;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}
