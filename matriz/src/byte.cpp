#include "byte.h"
#include <iostream>
#include "imagen.h"

using namespace std;

void on (byte &b, int pos){
    byte mask = 1 << (7 - pos);
    
    b = b | mask;
}

void off(byte &b, int pos){
    byte mask = 1 << (7 - pos);
    
    mask = ~mask;
    
    b = b & mask;
}

bool getbit(byte b, int pos){
    byte mask = 1 << pos;
    bool encendido = false;
    
    b = b & mask;
    
    if (b != 0)
        encendido = true;
    
    return encendido;
}

void encender(byte &b){
    for (int i = 0; i < 8; i++){
        on(b,i);
    }
}

void apagar(byte &b){
    for (int i = 0; i < 8; i++){
        off(b,i);
    }
}

void asignar(byte &b, const bool v[]){
    for (int i = 0; i < 8; i++){
        if (v[i])
            on(b,7 - i);
        else
            off(b,7 - i);
    }
}

void volcar(byte b, bool v[]){
    for (int i = 0; i < 8; i++){
        if (getbit(b,7 - i))
            v[i] = true;
        else
            v[i] = false;
    }
}

void encendidos(byte b, int posic[], int &cuantos){
    cuantos = 0;
    
    for (int i = 0; i < 8; i++){
        if (getbit(b,7 - i)){
            posic[i] = i;
            cuantos++;
        }
    }
}
