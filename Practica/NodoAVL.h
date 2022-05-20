#pragma once
#include <iostream>
#include "NodoB.h"

template<class Key>
class NodoAVL : public NodoB<Key>{
    public:
        NodoAVL() : NodoB<Key>() {};
        NodoAVL (const int bal, const Key &dat, NodoB<Key> *izq = NULL, NodoB<Key> *der = NULL) {
            NodoB<Key> (dat, izq, der);
            bal_ = bal;
        }

        NodoAVL* &NodoIzq() {return reinterpret_cast<NodoAVL<Key>*&>(NodoB<Key>::getNodoIzq());}
        NodoAVL* &NodoDer() {return reinterpret_cast<NodoAVL<Key>*&>(NodoB<Key>::getNodoDer());}

        int& Balance() {return bal_;}

    private:
        int bal_; 
        

};