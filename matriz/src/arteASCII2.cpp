/**
 * lee cualquier imagen indicada por el usuario y un fichero con cadenas 
 * de caracteres y crea ficheros de imagen transformadas, una por cadena
*/
#include<iostream>
#include<fstream>
#include<cstring>
#include "imagen.h"
#include "lista.h"

using namespace std;

const int MAXLONG = 1000;

void leelinea(char *s){
	do{
		cin.getline(s, MAXLONG);
	} while (s[0]=='\0');
}

int main(int argc, char **argv){
    if (argc != 3){
        cerr << "Use: " << argv[0] << " imagen.pgm grises.txt\n";
        cerr << "donde: imagen.pgm...";
        return 1;
    }
    else{
        char ficheroGrises[MAXLONG];
        char ficheroImagen[MAXLONG];
        Imagen origen;
        Lista celdas;
        
        cout << "Introduzca nombre de la imagen: ";
        leelinea(ficheroImagen);
        
        // Leer la imagen desde fichero
        if (!origen.leerImagen(ficheroImagen)){
            cerr << "Error leyendo imagen " << ficheroImagen << endl;
            return 1;
        }
        
        cout << "Introduzca el nombre de fichero con el conjunto de caracteres para realizar la conversion: ";
        leelinea(ficheroGrises);
        
        // Leer cadenas desde fichero
        if (celdas.leerLista(ficheroGrises)){
            // realizar las conversiones
            if (origen.listaAArteASCII(celdas)){
                cout << "Exito en la conversion." << endl;
                cout << "Chequee los ficheros asciiX.txt" << endl;
                cout << endl;
            }
            else{
                cerr << "La conversion no ha sido posible" << endl;
                cerr << endl;
            }
        }
        else{
            cerr << "Error leyendo fichero de grises " << ficheroGrises << endl;
        }
    }
}
