#pragma once
#include "NodoB.h"
#include <iostream>
#include <fstream>

template<class Key>
class AB {
    public:
        AB () : raiz_(nullptr) {}
        ~AB() {Podar(raiz_);}

        virtual bool insertar (const Key& k) = 0;
        virtual bool buscar (const Key& k) = 0;
        virtual bool eliminar (Key& k) = 0;

        void inorden() const;
        
        void Impresion(std::ostream& os, NodoB<Key> *raiz);
        void ImpresionNivel(std::ostream& os, NodoB<Key> *raiz, int nivel);
        void Imprimir();
        void Podar(NodoB<Key>* nodo);

        bool Vacio(NodoB<Key> *nodo);
        bool Hoja(NodoB<Key> *nodo);

        int Tamano(NodoB<Key> *nodo);
        int Tamano();

        bool Equilibrado(NodoB<Key> *nodo);
        bool Equilibrado();
        //NodoB<Key>* getRaiz() {return raiz_;}
        NodoB<Key>* &getRaiz() {return raiz_;}

    protected:
        void setRaiz2(Key nodo_padre, NodoB<Key> *nodo_hijo1 = NULL, NodoB<Key> *nodo_hijo2 = NULL);
        void setRaiz3(Key nodo_padre);
        void setRaiz(NodoB<Key> raiz) {raiz_ = raiz;}
        
        NodoB<Key> getRaiz2() {return raiz_;}
        //NodoB<Key> getRaiz2() const {return raiz_;}
        int Nivel (NodoB<Key> *nodo);

        int AltN(NodoB<Key> *nodo);
        int Alt();

        NodoB<Key>* &raiz() {return raiz_;}        

    private:
        NodoB<Key> *raiz_;
        
};

template<class Key>
std::ostream& operator<<(std::ostream& os, AB<Key> *raiz) {
    NodoB<Key> *nodo = raiz->getRaiz();
    raiz->Impresion(os, nodo);
    return os;

}


template<class Key>
void AB<Key>::setRaiz2(Key nodo_padre, NodoB<Key> *nodo_hijo1, NodoB<Key> *nodo_hijo2) {
    raiz_->setDato(nodo_padre);
    raiz_->setNodoDer(nodo_hijo1);
    raiz_->setNodoIzq(nodo_hijo2);
}

template<class Key>
void AB<Key>::setRaiz3(Key nodo_padre) {
    raiz_ = new NodoB<Key> (nodo_padre);
}

template<class Key>
void AB<Key>::Podar(NodoB<Key>* nodo) {
    if (nodo == NULL) {
        return;
    }

    Podar(nodo->getNodoIzq());
    Podar(nodo->getNodoDer());
    delete nodo;
    nodo = NULL;
}

template<class Key>
bool AB<Key>::Vacio(NodoB<Key> *nodo) {
    if (nodo == NULL) {
        return true;
    }
    return false;
}

template<class Key>
bool AB<Key>::Hoja(NodoB<Key> *nodo) {
    if (!(nodo->getNodoDer()) && !(nodo->getNodoIzq())) {
        return true;
    }
    return false;
}

template<class Key>
void AB<Key>::Imprimir() {
    Impresion(std::cout, raiz_);
}

template<class Key>
int AB<Key>::Nivel (NodoB<Key> *nodo) {
    if (nodo == NULL) {
        return 0;
    } 

    int nivel_izq = Nivel(nodo->getNodoIzq());
    int nivel_der = Nivel(nodo->getNodoDer());

    if (nivel_der > nivel_izq) {
        return nivel_der + 1;
    } else {
        return nivel_izq + 1;
    }
    

}


template<class Key>
void AB<Key>::Impresion(std::ostream& os, NodoB<Key> *raiz) {

    //int nivel = Nivel(raiz_);
    int nivel = Nivel(raiz);

    for (int i = 1; i <= nivel+1; i++) {
        os << "Nivel " << i-1 << ": ";
        ImpresionNivel(os, raiz, i);
        os << std::endl;
    }


}

template<class Key>
void AB<Key>::ImpresionNivel(std::ostream& os, NodoB<Key> *raiz, int nivel) {
    
    if (raiz == NULL) {
        if (nivel < 2) {
            os << "[.]";
            return;
        } else {
            return;
        }
    }

    if (nivel == 1) {
        os << "["<< raiz->getDato() << "]";        

    } else if (nivel > 1) {
        ImpresionNivel(os, raiz->getNodoIzq(), nivel-1); // -1
        ImpresionNivel(os, raiz->getNodoDer(), nivel-1);
    }
}


template<class Key>
void AB<Key>::inorden() const {
    if (raiz_ == NULL) {
        return;
    }
    raiz_->inordenNodo();
}




template<class Key>
bool AB<Key>::Equilibrado(NodoB<Key> *nodo) {

    if (nodo == NULL) {
        return true;
    }
    int equilibrio = Tamano(nodo->izdo_) - Tamano(nodo->getNodoDer());
    if (equilibrio == 1) {
        return (Equilibrado(nodo->izdo_) && Equilibrado(nodo->getNodoDer()));
    } 

    return false;

}

template<class Key>
int AB<Key>::Tamano(NodoB<Key> *nodo) {
    if (nodo != NULL) {
        return (1 + Tamano(nodo->getNodoDer()) + Tamano(nodo->getNodoIzq()));
    }
    return 0;
}

template<class Key>
bool AB<Key>::Equilibrado() {
    if (raiz_ == NULL) {
        return true;
    }
    int equilibrio = Tamano(raiz_->getNodoIzq()) - Tamano(raiz_->getNodoDer());
    if (equilibrio == 1) {
        return (Equilibrado(raiz_->getNodoIzq()) && Equilibrado(raiz_->getNodoDer()));
    } 

    return false;
}

template<class Key>
int AB<Key>::Tamano() {
    if (raiz_ != NULL) {
        return (1 + Tamano(raiz_->getNodoIzq()) + Tamano(raiz_->getNodoDer()));
    }
    return 0;
}

template<class Key>
int AB<Key>::Alt() {
    return AtlN(raiz_);
}

template<class Key>
int AB<Key>::AltN(NodoB<Key> *nodo) {
    if (nodo == NULL) {
        return 0;
    }
    int alt_i = AltN(nodo->getNodoIzq());
    int alt_d = AltN(nodo->getNodoDer());
    if (alt_d > alt_i) {
        return alt_d + 1;
    } else {
        return alt_i + 1;
    }
}