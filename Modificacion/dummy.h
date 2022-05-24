#pragma once
#include <iostream>

class Dummy {
    public:
        Dummy (int clave) : Clave_(clave) {}
        Dummy () {}
        //friend int operator+(Dummy clave1, Dummy clave2);
        //friend int operator-(Dummy clave1, Dummy clave2);
        friend bool operator<(Dummy clave1, Dummy clave2);
        friend bool operator>(Dummy clave1, Dummy clave2);
        friend std::ostream& operator>>(std::ostream& in, Dummy clave1);
        friend std::istream& operator<<(std::istream& os, Dummy clave1);
        friend bool operator==(Dummy clave1, Dummy clave2);
    

        int getClave() {return Clave_;}
        unsigned getContador() {return Contador_;}
        //int getDato() {return Dato_;}

        void setClave(int clave1) {Clave_ = clave1;}
        void setContador(int dato1) {Contador_ = dato1;}
        static unsigned Contador_;
        int Clave_;
        
        
};


int operator-(Dummy clave1, Dummy clave2) {
    return clave1.getClave() - clave2.getClave();
}


int operator+(Dummy clave1, Dummy clave2) {
    return clave1.getClave() + clave2.getClave();
}


bool operator>(Dummy clave1, Dummy clave2) {
    clave1.Contador_++; 
    clave2.Contador_++; 
    return clave1.getClave() > clave2.getClave();
}


bool operator<(Dummy clave1, Dummy clave2) {
    clave1.Contador_++; 
    clave2.Contador_++; 
    return clave1.getClave() < clave2.getClave();
}

std::ostream& operator<<(std::ostream& os, Dummy clave1) {
    //os << "Clave: " << clave1.getClave() << ". Dato: " << clave1.getDato() << std::endl;
    os << clave1.getClave();
    return os;

}

std::istream& operator>>(std::istream& in, Dummy clave1) { // ¿Problema? se pasa como copia y por tanto el cambio no se hace efectivo
    int clave;
    //std::cout << "Clave: ";
    in >> clave; 
    clave1.setClave(clave);
    /*std::cout << "Dato: ";
    in >> clave; 
    clave1.setDato(clave);*/
    return in;
}

bool operator==(Dummy clave1, Dummy clave2) {
    //std::cout << "prueba: " << clave1.getClave() << " :: " << clave2.getClave() << std::endl;
    clave1.Contador_++; 
    clave2.Contador_++; 
    return clave1.getClave() == clave2.getClave();
}