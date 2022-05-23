#pragma once
#include "AB.h"
#include <iostream>
#include <fstream>


template<class Key>
class ABE : public AB<Key> {
    public:
        bool insertar (const Key& k);
        bool buscar (const Key& k);
        void insertarEquilRama(const Key& k, NodoB<Key> *nodo);
        bool busqueda (const Key& k, NodoB<Key> *nodo);
        bool eliminar (Key& k);
};


template<class Key>
bool ABE<Key>::eliminar (Key& k) {
    std::cout << "La operación de eliminación no está disponible en el ABE" << std::endl;
    return false;
}


template<class Key>
bool ABE<Key>::insertar (const Key& k) {
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
void ABE<Key>::insertarEquilRama(const Key& k, NodoB<Key> *nodo) {
    int tam_izq = AB<Key>::Tamano(nodo->getNodoIzq());
    int tam_der = AB<Key>::Tamano(nodo->getNodoDer());

    if (tam_izq <= tam_der) {
        if (nodo->getNodoIzq() != NULL) {
            insertarEquilRama(k, nodo->getNodoIzq());
        } else {
            nodo->setNodoIz(k);
        }
    } else {
        if (nodo->getNodoDer() != NULL){
            insertarEquilRama(k, nodo->getNodoDer());
        } else {            
            nodo->setNodoDe(k);
        }
    }
}

template<class Key>
bool ABE<Key>::buscar (const Key& k) {
    return busqueda(k, AB<Key>::getRaiz());
}

template<class Key>
bool ABE<Key>::busqueda (const Key& k, NodoB<Key> *nodo) {
    if (nodo == NULL) {
        return false;
    } else {
        if (k == nodo->getDato()) {
            return true;
        } else {
            if (busqueda(k, nodo->getNodoIzq())){
                return true;
            } else {
                return busqueda(k, nodo->getNodoDer());
            }
        }
    }
    return false;
}



