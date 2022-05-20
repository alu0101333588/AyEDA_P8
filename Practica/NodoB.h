#pragma once
#include <iostream>

template<class Key>
class NodoB {
    public:
        NodoB (const Key& dat, NodoB *izq = NULL, NodoB *der = NULL) : dato_(dat), izdo_(izq), dcho_(der) {}

        // NodoB<Key> *nodo,
        //NodoB* setNodo2(Key valor);

        NodoB* &getNodoIzq() {return izdo_;}
        NodoB* &getNodoDer() {return dcho_;}

        Key getDato() {return dato_;}
        Key* &Dato() {return dato_;}

        void setNodo(NodoB* nodo);

        void setDato(Key dato) {dato_ = dato;}

        void setNodoIz(Key k);
        void setNodoDe(Key k);
        void inordenNodo();
        void inordenNodo2(NodoB<Key> *nodo);
        void imprimir ();


    private:
        Key dato_; 
        NodoB *izdo_;
        NodoB *dcho_;

};


template<class Key>
void NodoB<Key>::setNodo(NodoB<Key>* nodo){
    dato_ = nodo->getDato();
    izdo_ = nodo->getNodoIzq();
    dcho_ = nodo->getNodoDer();
}


template<class Key>
void NodoB<Key>::setNodoIz(Key k) {
    izdo_ = new NodoB<Key> (k);
}

template<class Key>
void NodoB<Key>::setNodoDe(Key k) {
    dcho_ = new NodoB<Key> (k);
}

template<class Key>
void NodoB<Key>::inordenNodo() {
    inordenNodo2(this);
    std::cout << std::endl;
}

template<class Key>
void NodoB<Key>::inordenNodo2(NodoB<Key> *nodo) {
    if (nodo == NULL) {
        return;
    }

    inordenNodo2(nodo->getNodoIzq());
    std::cout << "[" << nodo->getDato() << "] ";    
    inordenNodo2(nodo->getNodoDer());
}

template<class Key>
void NodoB<Key>::imprimir() {
    std::cout << "***********************" << std::endl;
    std::cout << "Nodo: " << getDato() << std::endl;
    if (getNodoDer() != NULL) {
        std::cout << "Hijo derecho: " << getNodoDer()->getDato() << std::endl;
    }
    if (getNodoIzq() != NULL) {
        std::cout << "Hijo izquierdo: " << getNodoIzq()->getDato() << std::endl;
    }
    std::cout << "***********************" << std::endl;
}
