#pragma once
#include <iostream>
#include "NodoB.h"

template<class Key>
class NodoAVL : public NodoB<Key>{
    public:
        NodoAVL() : NodoB<Key>() {};
        NodoAVL (const Key& dat, NodoB<Key> *izq = NULL, NodoB<Key> *der = NULL) : NodoB<Key>(dat, izq, der), bal_(0) {}
            /*std::cout << "construyendo... " << dat << std::endl;
            NodoB<Key> (dat, izq, der);
            std::cout << "Saliendo del constructor..." << this->getDato() << std::endl;
            bal_ = bal;
        }*/
        ~NodoAVL(){};

        Key& getDato() {return reinterpret_cast<Key&>(NodoB<Key>::getDato());}

        NodoAVL* &NodoIzq() {return reinterpret_cast<NodoAVL<Key>*&>(NodoB<Key>::getNodoIzq());}
        NodoAVL* &NodoDer() {return reinterpret_cast<NodoAVL<Key>*&>(NodoB<Key>::getNodoDer());}

        int& Balance() {return bal_;}

    private:
        int bal_; 
        
};