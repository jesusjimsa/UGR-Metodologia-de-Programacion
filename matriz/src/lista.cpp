#include <string>
#include <fstream>
#include "lista.h"

using namespace std;

Lista::Lista(){
    cabecera = 0;
}
   
Lista::Lista(string valor){
    cabecera = 0;
    insertar(valor);
}

Lista::~Lista(){
    destruir();
}

Lista::Lista(const Lista & orig){
    cabecera = 0;
    
    for (int i = 0; i < orig.longitud(); i++){
        insertar(orig.getCelda(i));
    }
}

Lista & Lista::operator = (const Lista & orig){
    if(this != & orig){
        destruir();
        
        Lista(orig);
    }
    
    return *this;
}

Lista Lista::operator + (const Lista & orig) const{
    Lista suma;
    Celda *auxsuma, *auxinicio, *auxorig;
    
    if(cabecera){
        suma.cabecera = new Celda;
        suma.cabecera -> datos = cabecera -> datos;
        auxsuma = suma.cabecera;
        auxinicio = cabecera -> siguiente;
        
        while (auxinicio){
            auxsuma -> siguiente = new Celda;
            auxsuma = auxsuma -> siguiente;
            auxsuma -> datos = auxinicio -> datos;
            auxinicio = auxinicio -> siguiente;
        }
    }
    if(orig.cabecera){
        if(!suma.cabecera){
            suma.cabecera = new Celda;
            suma.cabecera -> datos = orig.cabecera -> datos;
            auxsuma = suma.cabecera;
            auxorig = orig.cabecera -> siguiente;
        }
        else{
            auxorig = orig.cabecera;
        }
        
        while(auxorig){
            auxsuma -> siguiente = new Celda;
            auxsuma = auxsuma -> siguiente;
            auxsuma -> datos = auxorig -> datos;
            auxorig = auxorig -> siguiente;
        }
    }
    
    if(suma.cabecera){
        auxsuma -> siguiente = 0;
    }
    
    return suma;
}

void Lista::destruir(){
    Celda *p;
    
    p = cabecera;
    
    while (cabecera != 0){
        cabecera = cabecera -> siguiente;
        delete p;
        p = cabecera;
    }
}  

void Lista::insertar(string valor){
    Celda *p;
    
    if (cabecera != 0){
        p = cabecera;
        
        while (p -> siguiente != 0) {
            p = p -> siguiente;
        }
        
        p -> siguiente = new Celda;
        p = p -> siguiente;
    }
    else{
        cabecera = new Celda;
        p = cabecera;
    }
    
    p -> datos = valor;
    p -> siguiente = 0;
}

string Lista::getCelda(int pos) const{
    string caracteres;
    
    if (pos >= 0 && pos < longitud()){
        Celda *p;
        int i = 0;
        
        p = cabecera;
        
        //Suponemos que empieza a contar desde 0
        
        while (i < pos){
            p = p -> siguiente;
            i++;
        }
        
        caracteres = p -> datos;
    }
    
        return caracteres;
}

int Lista::longitud() const{
    Celda *p;
    int n = 0;
    
    p = cabecera;
    
    while (p -> siguiente != 0){
        p = p -> siguiente;
        n++;
    }
    
    return n;
}

bool Lista::leerLista(const char nombrefichero[]){
	// vaciar la lista
	destruir();
	
	// abrir fichero (y comprobar que se abrió correctamente)
	ifstream fin;
	fin.open(nombrefichero);
	if (!fin){
		return false;
	}
	
	string grises;
	int lineas;
	getline(fin, grises); //la primera linea se ignora
	fin >> lineas; //leo el numero de datos de grises
	getline(fin, grises); //leer salto de linea
	
	if (!fin){ //¿hubo error en las lecturas?
		return false;
	}
	
	int i = 0;
	getline(fin, grises); //leer cadena de caracteres
	while ((i < lineas) && fin){
		if (grises != ""){ // saltar líneas en blanco
			insertar(grises);
			i++;
		}
		getline(fin, grises); //leer cadena de caracteres
	}
	
	if (i < lineas){ //¿hubo error en las lecturas?
		destruir();
		return false;
	}
		
	fin.close();
	return true;
}
