#include <stddef.h>
#include <stdbool.h>
#include "lista_simple.h"

Nodo* crearNodo(void *dato, size_t size){
    Nodo *nuevo =(Nodo *)malloc(sizeof(Nodo));
    if(nuevo!=NULL){
        nuevo->siguiente = NULL;
        nuevo->dato = malloc(size);
        //malloc de forma "normal" es de tipo void, cuando lo usamos indicamos 
        //el tipo de dato para el cual malloc, va a reservar memoria
        //pero si ya es void, solo se implementa malloc
        memcpy(nuevo->dato, dato, size);
        //Destino,Origen,Tamaño
    }
    return nuevo;
}

void borrarNodo(Nodo *n){
    if((n!=NULL)&&(n->siguiente==NULL)){
        free(n->dato);
        free(n);
        n=NULL;
    }
}

bool modificarNodo(Nodo *n, void *d, size_t size){
    if(n!=NULL){
        memcpy(n->dato, d, size);
    }
}

Lista* crearLista(){
    Lista *l = (Lista*)malloc(sizeof(Lista));
    if(l!=NULL){
        l->head=NULL;
        l->tail=NULL;
    }
    return l;
}

bool esVacia(Lista* lista){
    return lista->head == NULL;
}

void insertarInicio(Lista* lista, void* dato, size_t size){
    Nodo *nuevo = crearNodo(dato, size);
    nuevo->siguiente=lista->head;
    lista->head=nuevo;
}

void insertarFinal(Lista* lista, void* dato, size_t size){
    Nodo *nuevo = crearNodo(dato, size);
    if (esVacia(lista)) {
        lista->head = nuevo;
        lista->tail = nuevo;
    } else {
        lista->tail->siguiente = nuevo;
        lista->tail = nuevo;
    }
}

void insertarPorPosicion(Lista* lista, void* dato, size_t size, int pos){
    if(esVacia(lista)){
        return ;
    }
    //este es el contador de todos los elemento que hay en la lista
    int total = 1;
    for(Nodo *tmp = lista->head; tmp !=NULL; tmp=tmp->siguiente){
        total++;
    }
    //este es el comtador de penultimo elemento que se encuentra antes de donde se
    //quiere insertar, se que se puede hacer con un ciclo for, pero 
    //me es mas facil hacerlo con un while a mandera didatica
    Nodo* anterior = lista->head;
    int i = 1;
    while (i < pos - 1 && anterior->siguiente != NULL) {
        anterior = anterior->siguiente;
        i++;
    }
    //casos de cada funcion 
    if(pos == 1){
        insertarInicio(lista, dato, size);
    }else if (pos == total){
        insertarFinal(lista, dato, size);
    }else if((pos>=1)&&(pos<total)){
        Nodo *nuevo = crearNodo(dato, size);
        nuevo->siguiente=anterior->siguiente;
        anterior->siguiente=nuevo;
    }else{
        printf("La posicion no es valida\n");
    }
}

void eliminarInicio(Lista* lista){
    Nodo *tmp = lista->head;
    lista->head=lista->head->siguiente;
    tmp->siguiente=NULL;
    borrarNodo(tmp);
    //segun la profesora, esto no es necesario, pero es por seguridad
    tmp=NULL;
}

void eliminarFinal(Lista* lista){
    if (esVacia(lista)) return;
    Nodo *tmp = lista->tail;
    if (lista->head == lista->tail) { 
        lista->head = lista->tail = NULL;
    } else {
        Nodo *ant = lista->head;
        while (ant->siguiente != lista->tail) { 
            ant = ant->siguiente;
        }
        ant->siguiente = NULL;
        lista->tail = ant;
    }
    borrarNodo(tmp);
}

void eliminarPorPosicion(Lista* lista, int pos){
    if(esVacia(lista)){
        return ;
    }
    int total = 1;
    for(Nodo *tmp = lista->head; tmp !=NULL; tmp=tmp->siguiente){
        total++;
    }
    //este es el comtador de penultimo elemento que se encuentra antes de donde se
    //quiere insertar, se que se puede hacer con un ciclo for, pero 
    //me es mas facil hacerlo con un while a mandera didatica
    Nodo* anterior = lista->head;
    int i = 1;
    while (i < pos - 1 && anterior->siguiente != NULL) {
        anterior = anterior->siguiente;
        i++;
    }
    if(pos == 1){
        eliminarInicio(lista);
    }else if (pos == total){
        eliminarFinal(lista);
    }else if((pos>=1)&&(pos<total)){
        Nodo *tmp = anterior->siguiente;
        anterior->siguiente=tmp->siguiente;
        borrarNodo(tmp);
    }else{
        printf("La posicion no es valida\n");
    }
}
void eliminarPorElemento(Lista* lista, void* dato2, CompararFunc cmp){
    if (esVacia(lista)) return;
    Nodo *actual = lista->head;
    Nodo *anterior = NULL;

    while (actual != NULL) {
        if (cmp(actual->dato, dato2) == 0) {
            if (actual == lista->head) {
                eliminarInicio(lista);
            } else if (actual == lista->tail) {
                eliminarFinal(lista);
            } else {
                anterior->siguiente = actual->siguiente;
                borrarNodo(actual);
            }
            return;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
}
void eliminarElementosIguales(Lista* lista, void* dato, CompararFunc cmp){
    if (esVacia(lista)) return;
    Nodo* actual = lista->head;
    Nodo* anterior = NULL;
    while (actual != NULL) {
        if (cmp(actual->dato, dato) == 0) {
            Nodo* nodoABorrar = actual;
            if (actual == lista->head) {
                lista->head = actual->siguiente;
                actual = lista->head;
                if (lista->head == NULL) {
                    lista->tail = NULL;
                }
            } 
            else {
                anterior->siguiente = actual->siguiente;
                if (actual == lista->tail) {
                    lista->tail = anterior;
                }
                actual = anterior->siguiente;
            }
            borrarNodo(nodoABorrar);
        } 
        else {
            anterior = actual;
            actual = actual->siguiente;
        }
    }
}

// Búsquedas
void* buscarPorPosicion(Lista* lista, int pos);
int buscarPorElemento(Lista* lista, void* dato, CompararFunc cmp);

// Navegación
Nodo* primero(Lista* lista);
Nodo* ultimo(Lista* lista);
Nodo* siguiente(Nodo* actual);

// Modificar
void modificar(Lista* lista, int pos, void* dato, size_t size);

// Utilidad
void imprimirLista(Lista* lista, ImprimirFunc imprimir);
void vaciarLista(Lista* lista);
void borrarLista(Lista* lista);
