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
        AVL () {}
        //AVL () : ABB<Key>() {}
        AVL(NodoAVL<Key> *raiz) : ABB<Key>(raiz) {}
        ~AVL(){};
        bool insertar (Key& k);
        void Insertar_Balanceo(NodoAVL<Key>* &nodo, NodoAVL<Key>* nuevo, bool& crece);
        void insert_re_balanceo_dcha(NodoAVL<Key>* &nodo);
        void insert_re_balanceo_izda(NodoAVL<Key>* &nodo);
        bool eliminar (Key k);
        void elimina_rama(NodoAVL<Key>* &nodo, Key k, bool& decrece);
        void sustituye(NodoAVL<Key>* &eliminado, NodoAVL<Key>* &sust, bool& decrece);
        void eliminar_re_balancea_izda(NodoAVL<Key>* &nodo, bool& decrece);
        void eliminar_re_balancea_dcha(NodoAVL<Key>* &nodo, bool& decrece);


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
        NodoAVL<Key>* &raiz() {return reinterpret_cast<NodoAVL<Key>*&>(AB<Key>::raiz());}
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

template<class Key>
bool AVL<Key>::insertar (Key& k) {
    
    std::cout << "PRUEBA " << "NIVEL AVL" << std::endl;

    if (ABB<Key>::buscar(k)) {
        return false;
    }
    
    NodoAVL<Key>* nuevo = new NodoAVL<Key>(k);
    bool crece = false;
    Insertar_Balanceo(ABB<Key>::raiz(), nuevo, crece);
    return true;
}

template<class Key>
void AVL<Key>::Insertar_Balanceo(NodoAVL<Key>* &nodo, NodoAVL<Key>* nuevo, bool& crece){
    if (nodo == NULL) {
        nodo = nuevo;
        crece = true;
    } else if (nuevo->getDato() < nodo->getDato()) {
        Insertar_Balanceo(nodo->NodoIzq(), nuevo, crece);
        if (crece) {
            insert_re_balanceo_izda(nodo);
        } else {
            Insertar_Balanceo(nodo->NodoDer(), nuevo, crece);
            if (crece) {
                insert_re_balanceo_dcha(nodo);
            }
        }
    }
}

template<class Key>
void AVL<Key>::insert_re_balanceo_izda(NodoAVL<Key>* &nodo) {
    bool crece;
    switch(nodo->Balance()) {
        case -1:
            nodo->Balance() = 0;
            crece = false;
            break;

        case 0:
            nodo->Balance() = 1;
            break;

        case 1:
            NodoAVL<Key>* nodo1 = nodo->NodoIzq();
            if (nodo1->Balance() == 1) {
                rotacion_II(nodo);
            } else {
                rotacion_ID(nodo);
                crece = false;
            } 
            break;
    }

}

template<class Key>
void AVL<Key>::insert_re_balanceo_dcha(NodoAVL<Key>* &nodo) {
    bool crece;
    switch(nodo->Balance()) {
        case 1:
            nodo->Balance() = 0;
            crece = false;
            break;

        case 0:
            nodo->Balance() = -1;
            break;

        case -1:
            NodoAVL<Key>* nodo1 = nodo->NodoDer();
            if (nodo1->Balance() == -1) {
                rotacion_DD(nodo);
            } else {
                rotacion_DI(nodo);
                crece = false;
            } 
            break;
    }

}

template<class Key>
bool AVL<Key>::eliminar (Key k) {
    std::cout << "PRUEBA " << "NIVEL AVL" << std::endl;

    if (ABB<Key>::buscar(k)) {
        return false;
    }
    
    bool decrece = false;
    elimina_rama(AVL<Key>::raiz(), k, decrece);
    return true;
}

template<class Key>
void AVL<Key>::elimina_rama(NodoAVL<Key>* &nodo, Key k, bool& decrece) {
    if (nodo == NULL) {
        return;
    }
    if (k < nodo->getDato()) {
        elimina_rama(nodo->NodoIzq(), k, decrece);
        if (decrece) {
            eliminar_re_balancea_izda(nodo, decrece);
        } else if (k > nodo->getDato()) {
            elimina_rama(nodo->NodoDer(), k, decrece);
            if (decrece) {
                eliminar_re_balancea_dcha(nodo, decrece);
            }
        } else { // k == nodo->getDato()
            NodoAVL<Key>* Eliminado = nodo;
            if (nodo->NodoIzq() == NULL) {
                nodo = nodo->NodoDer();
                decrece = true;
            } else if (nodo->NodoDer() == NULL) {
                nodo = nodo->NodoIzq();
                decrece = true;
            } else {
                sustituye(Eliminado, nodo->NodoIzq(), decrece);
                if (decrece) {
                    eliminar_re_balancea_izda(nodo, decrece);
                }
            }
            delete Eliminado;
        } 
    }
}

template<class Key>
void AVL<Key>::sustituye(NodoAVL<Key>* &eliminado, NodoAVL<Key>* &sust, bool& decrece) {
    if (sust->NodoDer() != NULL) {
        sustituye(eliminado, sust->NodoDer(), decrece);
        if (decrece) {
            eliminar_re_balancea_dcha(sust, decrece);
        }
    } else {
        eliminado->getDato() = sust->getDato();
        eliminado = sust;
        sust = sust->NodoIzq();
        decrece = true;
    }
}

template<class Key>
void AVL<Key>::eliminar_re_balancea_izda(NodoAVL<Key>* &nodo, bool& decrece) {
    switch(nodo->Balance()) {
        case -1:
            NodoAVL<Key>* nodo1 = nodo->NodoDer();
            if (nodo1->Balance() > 0) {
                rotacion_DI(nodo);
            } else {
                if (nodo1->Balance() == 0) {
                    decrece = false;
                }
                rotacion_DD(nodo);
            }
            break;
        
        case 0:
            nodo->Balance() = -1;
            decrece = false;
            break;
        
        case 1:
            nodo->Balance() = 0;
            break;
    }
}


template<class Key>
void AVL<Key>::eliminar_re_balancea_dcha(NodoAVL<Key>* &nodo, bool& decrece) {
    switch(nodo->Balance()) {
        case 1:
            NodoAVL<Key>* nodo1 = nodo->NodoDer();
            if (nodo1->Balance() > 0) {
                rotacion_ID(nodo);
            } else {
                if (nodo1->Balance() == 0) {
                    decrece = false;
                }
                rotacion_II(nodo);
            }
            break;
        
        case 0:
            nodo->Balance() = 1;
            decrece = false;
            break;
        
        case -1:
            nodo->Balance() = 0;
            break;
    }
}