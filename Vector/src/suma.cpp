#include <iostream>
#include <imagen.h>
#include <string>

using namespace std;

int main(int argc, char **argv){
    if (argc != 5){
        cerr << "Use: " << argv[0] << " img1.pgm img2.pgm img_out.pgm t|b\n";
        return 1;
    }
    else{
        if(*argv[4] == 't'){
            Imagen imagen1, imagen2, destino;
            
            //Lee las imágenes originales
            imagen1.leerImagen(argv[1]);
            imagen2.leerImagen(argv[2]);
            
            destino.concatenar(imagen1, imagen2);
            
            destino.escribirImagen(argv[3], false);
        }
        else{
            if(*argv[4] == 'b'){
                Imagen imagen1, imagen2, destino;
                
                //Lee las imágenes originales
                imagen1.leerImagen(argv[1]);
                imagen2.leerImagen(argv[2]);
                
                destino.concatenar(imagen1, imagen2);
                
                destino.escribirImagen(argv[3], true);
            }
            else{
                cerr << "Debe introducir t o b\n";
                return 1;
            }
        }
    }
}