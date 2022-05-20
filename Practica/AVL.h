#pragma once
#include "ABB.h"
//#include "NodoB.h"
#include <iostream>
#include <fstream>
#include "NodoAVL.h"
#define traza


template<class Key>
class AVL : public ABB<Key> {
    public:
        AVL () : ABB<Key>() {}
        AVL(NodoAVL<Key> *raiz) : ABB<Key>(raiz) {}
        ~AVL(){};
        //bool insertar (const Key& k);
        //bool buscar (const Key& k);
        //void insertarEquilRama(const Key& k, NodoB<Key> *nodo);
        //bool busqueda (const Key& k, NodoB<Key> *nodo);
        //bool eliminar (Key& k);
        //bool eliminacion (NodoB<Key>* &nodo, Key& k);
        //void sustituir (NodoB<Key>* &eliminado, NodoB<Key>* &sustituto);
        //bool balanceado();
        //bool balanceadoRama(NodoB<Key> *nodo);
        void rotacion_II (NodoAVL<Key>* &nodo);
        void rotacion_DD (NodoAVL<Key>* &nodo);
        void rotacion_ID (NodoAVL<Key>* &nodo);
        void rotacion_DI (NodoAVL<Key>* &nodo);

    protected:
        NodoAVL<Key>* &raiz() {return reinterpret_cast<NodoAVL<Key>*&>(AB<Key>::getRaiz2());}
};

template<class Key>
void AVL<Key>::rotacion_II (NodoAVL<Key>* &nodo) {
    #ifdef traza
    std::cout << "Desbalanceo" << std::endl;
    this->Imprimir();
    std::cout << "Rotación II en [" << nodo->getDato() << "]" << std::endl;
    #endif

    NodoAVL<Key>* nodo1 = nodo->NodoIzq();
    nodo->NodoIzq() = nodo1->NodoDer();
    nodo1->NodoDer() = nodo;
    if (nodo1->Balance() == 1) {
        nodo->Balance() = 0;
        nodo1->Balance() = 0;
    } else { // nodo1->Balance() == 0
        nodo->Balance() = 1;
        nodo1->Balance() = -1;
    }
    nodo = nodo1;
}

template<class Key>
void AVL<Key>::rotacion_DD (NodoAVL<Key>* &nodo) {
    #ifdef traza
    std::cout << "Desbalanceo" << std::endl;
    this->Imprimir();
    std::cout << "Rotación DD en [" << nodo->getDato() << "]" << std::endl;
    #endif

    NodoAVL<Key>* nodo1 = nodo->NodoIzq();
    nodo->NodoDer() = nodo1->NodoIzq();
    nodo1->NodoIzq() = nodo;
    if (nodo1->Balance() == -1) {
        nodo->Balance() = 0;
        nodo1->Balance() = 0;
    } else { // nodo1->Balance() == 0
        nodo->Balance() = -1;
        nodo1->Balance() = 1;
    }
    nodo = nodo1;
}

template<class Key>
void AVL<Key>::rotacion_ID (NodoAVL<Key>* &nodo) {
    #ifdef traza
    std::cout << "Desbalanceo" << std::endl;
    this->Imprimir();
    std::cout << "Rotación ID en [" << nodo->getDato() << "]" << std::endl;
    #endif

    NodoAVL<Key>* nodo1 = nodo->NodoIzq();
    NodoAVL<Key>* nodo2 = nodo1->NodoDer();
    nodo->NodoIzq() = nodo2->NodoDer();
    nodo2->NodoDer() = nodo;
    nodo1->NodoDer() = nodo2->NodoIzq();
    nodo2->NodoIzq() = nodo1;

    if (nodo2->Balance() == -1) {
        nodo1->Balance() = 1;
    } else {
        nodo1->Balance() = 0;
        if (nodo2->Balance() == 1) {
            nodo->Balance() = -1;
        } else {
            nodo->Balance() = 0;
        }
        
    }
    nodo2->Balance() = 0;
    nodo = nodo2;
    
}

template<class Key>
void AVL<Key>::rotacion_DI (NodoAVL<Key>* &nodo) {
    #ifdef traza
    std::cout << "Desbalanceo" << std::endl;
    this->Imprimir();
    std::cout << "Rotación DI en [" << nodo->getDato() << "]" << std::endl;
    #endif

    NodoAVL<Key>* nodo1 = nodo->NodoDer();
    NodoAVL<Key>* nodo2 = nodo1->NodoIzq();
    nodo->NodoDer() = nodo2->NodoIzq();
    nodo2->NodoIzq() = nodo;
    nodo1->NodoIzq() = nodo2->NodoDer();
    nodo2->NodoDer() = nodo1;

    if (nodo2->Balance() == 1) {
        nodo1->Balance() = -1;
    } else {
        nodo1->Balance() = 0;
        if (nodo2->Balance() == -1) {
            nodo->Balance() = 1;
        } else {
            nodo->Balance() = 0;
        }
        
    }
    nodo2->Balance() = 0;
    nodo = nodo2;
    
}
