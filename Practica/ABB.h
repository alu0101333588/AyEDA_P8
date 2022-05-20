#pragma once
#include "AB.h"
#include "NodoB.h"
#include <iostream>
#include <fstream>

#include "NodoAVL.h"


template<class Key>
class ABB : public AB<Key> {
    public:
        bool insertar (const Key& k);
        bool buscar (const Key& k);
        void insertarEquilRama(const Key& k, NodoB<Key> *nodo);
        bool busqueda (const Key& k, NodoB<Key> *nodo);
        bool eliminar (Key& k);
        bool eliminacion (NodoB<Key>* &nodo, Key& k);
        void sustituir (NodoB<Key>* &eliminado, NodoB<Key>* &sustituto);
        bool balanceado();
        bool balanceadoRama(NodoB<Key> *nodo);
        ~ABB(){};

    protected:
        NodoAVL<Key>* &raiz() {return reinterpret_cast<NodoAVL<Key>*&>(AB<Key>::raiz());}
};

template<class Key>
bool ABB<Key>::eliminar (Key& k) {
    std::cout << "PRUEBA. NIVEL ABB" << std::endl;
    if (AB<Key>::getRaiz() == NULL || !buscar(k)){
        return false;
    } 
    return eliminacion(AB<Key>::getRaiz(), k);
}


template<class Key>
bool ABB<Key>::eliminacion (NodoB<Key>* &nodo, Key& k) {
    if (nodo == NULL){
        return false;
    } 

    if (k < nodo->getDato()) { // k < nodo
        return eliminacion(nodo->getNodoIzq(), k);
    } else if (k > nodo->getDato()) { // k > nodo
        return eliminacion(nodo->getNodoDer(), k);
    } else { // k == nodo
        NodoB<Key>* Eliminado = nodo;
        if (nodo->getNodoDer() == NULL) {
            nodo = nodo->getNodoIzq();
        } else if (nodo->getNodoIzq() == NULL) {
            nodo = nodo->getNodoDer();
        } else {
            sustituir(Eliminado, nodo->getNodoIzq());
        }
        return true;
    }
    return false;
    
}

template<class Key>
void ABB<Key>::sustituir (NodoB<Key>* &eliminado, NodoB<Key>* &sustituto) {

    if (sustituto->getNodoDer() != NULL) {
        sustituir(eliminado, sustituto->getNodoDer());
    } else {
        eliminado->setDato(sustituto->getDato()); 
        eliminado = sustituto;
        sustituto = sustituto->getNodoIzq();

    }

}

template<class Key>
bool ABB<Key>::balanceado() {
   return balanceadoRama(AB<Key>::getRaiz());
}

template<class Key>
bool ABB<Key>::balanceadoRama(NodoB<Key> *nodo){
    if (nodo == NULL) {
        return true;
    } 
    int balance = AB<Key>::AltN(nodo->getNodoIzq()) - AB<Key>::AltN(nodo->getNodoDer());
    switch (balance){
    case -1:
    case 0:
    case 1:
        return (balanceadoRama(nodo->getNodoIzq()) && balanceadoRama(nodo->getNodoDer()));
        break;
    default:
        return false;
        break;
    }

}

template<class Key>
bool ABB<Key>::insertar (const Key& k) {
    std::cout << "PRUEBA. NIVEL ABB" << std::endl;
    if (buscar(k)) {
        return false;
    }
    if (AB<Key>::getRaiz() == NULL) {
        AB<Key>::setRaiz3(k);
    } else {
        insertarEquilRama(k, AB<Key>::getRaiz());
    }
    return true; 
}

template<class Key>
void ABB<Key>::insertarEquilRama(const Key& k, NodoB<Key> *nodo) {

    if (nodo == NULL) {
        nodo = new NodoB<Key> (k);
        std::cout << "nodo: " << nodo->getDato() << std::endl;
        
    } else if (k < nodo->getDato()) {

        if (nodo->getNodoIzq() != NULL) {
            insertarEquilRama(k, nodo->getNodoIzq());
        } else {
            nodo->setNodoIz(k);
        }

    } else {
        if (nodo->getNodoDer() != NULL) {
            insertarEquilRama(k, nodo->getNodoDer());
        } else {
            nodo->setNodoDe(k);
        }
    }

}

template<class Key>
bool ABB<Key>::buscar (const Key& k) {
    return busqueda(k, AB<Key>::getRaiz());
}

template<class Key>
bool ABB<Key>::busqueda (const Key& k, NodoB<Key> *nodo) {

    if (nodo == NULL) {
        return false;
    }
    if (k == nodo->getDato()) {
        return true;
    } 
    if (k < nodo->getDato()) {
        return busqueda(k, nodo->getNodoIzq());
    }
    return busqueda(k, nodo->getNodoDer());
}



