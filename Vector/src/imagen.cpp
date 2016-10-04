#include "imagen.h"
#include "pgm.h"
#include "byte.h"
#include <lista.h>
#include <string>
#include <cstring>
#include <fstream>


        /// Construye una imagen vacía (0 filas, 0 columnas)
        Imagen::Imagen(){
            nfilas=0;
            ncolumnas=0;
            datos = 0;
        }


        /**
         @brief Construye una imagen negra de tamaño @a filas x @a columnas
         @param filas 	número de filas de la imagen
         @param columnas	número de columnas de la imagen
         
         Construye una imagen de tamaño @a filas x @a columnas y pone todos
         sus elementos a 0.
         */
        Imagen::Imagen(int filas, int columnas){
            Inicializar(filas, columnas);
        }

        Imagen::~Imagen(){
            destruir();
        }

        Imagen::Imagen(const Imagen & orig){
            copiar(orig);
        }

        Imagen & Imagen::operator = (const Imagen & orig){
            if(this != & orig){
                destruir();
                
                Imagen(orig);
            }
            
            return *this;
        }

        void Imagen::destruir(){
            if(datos != 0){
                nfilas = ncolumnas = 0;
                delete [] datos;
                datos = 0;
            }
        }

        void Imagen::Inicializar(int filas, int columnas){
            datos = new byte [filas * columnas];
            
            nfilas = filas;
            ncolumnas = columnas;
            
            for (int i = 0; i < (filas * columnas); i++){
                datos[i] = 0;
            }
        }

        Imagen Imagen::concatenar(Imagen & a, Imagen & b){
            int filas, columnas;
            destruir();
            
            if(a.filas() > b.filas()){
                filas = a.filas();
            }
            else{
                filas = b.filas();
            }
            
            columnas = a.columnas() + b.columnas();
            
            Imagen final(filas, columnas);
            
            for(int i = 0; i < a.filas(); i++){
                for(int j = 0; j < a.columnas(); j++){
                    final.set(i, j, a.get(i, j));
                }
            }
            
            for(int i = 0; i < b.filas(); i++){
                for(int j = a.columnas(); j < a.columnas() + b.columnas(); j++){
                    final.set(i, j, b.get(i, j));
                }
            }
            copiar(final);
            
            return final;
        }

        void Imagen::copiar(const Imagen & orig){
            nfilas = orig.nfilas;
            ncolumnas = orig.ncolumnas;
            
            if (nfilas > 0 && ncolumnas > 0){
                datos = new byte [nfilas * ncolumnas];
            }
            
            for (int i = 0; i < nfilas * ncolumnas; i++){
                datos[i] = orig.datos[i];
            }
        }


        /**
         @brief Crea una imagen negra de tamaño @a filas x @a columnas
         @param filas 	número de filas de la imagen
         @param columnas	número de columnas de la imagen
         
         Dimensiona la imagen a tamaño @a filas x @a columnas y pone todos
         sus elementos a 0.
         */
        void Imagen::crear(int filas, int columnas){
            destruir();
            Inicializar(filas, columnas);
        }

        
        /**
         @brief Devuelve el número de filas de las imagen
         @return el número de filas de la imagen
         */
        int Imagen::filas(){
            return nfilas;
        }

        
        /**
         @brief Devuelve el número de columnas de las imagen
         @return el número de columnas de la imagen
         */
        int Imagen::columnas(){
            return ncolumnas;
        }

        
        /**
         @brief Asigna el valor @a v a la posición (@a x,@a y) de la imagen
         @param y 	fila de la imagen
         @param x 	columna de la imagen
         @param v 	valor a asignar
         
         Asigna el valor @a v a la posición (@a x,@a y) de la imagen. Dado que la imagen se guarda
         como un vector, la posición (@a x,@a y) corresponde a la posición @a y * @c ncolumnas + @a x
         del vector.
         */
        void Imagen::set(int y, int x, byte v){
            int coordenada;
            
            coordenada = y * ncolumnas + x;
            
            datos[coordenada] = v;
        }
        
        
        /**
         @brief Devuelve el valor de la posición (@a x,@a y) de la imagen
         @param y	 fila de la imagen
         @param x	 columna de la imagen
         @return el valor de la posición (@a x,@a y) de la imagen
         
         Devuelve el valor de la posición (@a x,@a y) de la imagen. Dado que la imagen se guarda
         como un vector, la posición (@a x,@a y) corresponde a la posición @a y * @c ncolumnas + @a x
         del vector.
         */
        byte Imagen::get(int y, int x) const{
            int coordenada;
            
            coordenada = y * ncolumnas + x;
            
            return datos[coordenada];
        }
    
        
        /**
         @brief Asigna el valor @a v a la posición @a i de la imagen considerada como vector
         @param i 	posición de la imagen considerada como vector
         @param v 	valor a asignar
         
         Asigna el valor @a v a la posición @a i de la imagen considerada como vector. La posición @a i
         corresponde con la posición @c y * @c ncolumnas + @c x de la imagen donde @c y representa la
         fila y @c x representa la columna.
         */
        void Imagen::setPos(int i, byte v){
            datos[i] = v;
        }
    
        
        /**
         @brief Devuelve el valor de la posición @a i de la imagen considerada como vector
         @param i 	posición de la imagen considerada como vector
         
         Devuelve el valor de la posición @a i de la imagen considerada como vector. La posición @a i
         corresponde con la posición @c y * @c ncolumnas + @c x de la imagen donde @c y representa la
         fila y @c x representa la columna.
         */
        byte Imagen::getPos(int i) const{
            return datos[i];
        }
    
        
        /**
         @brief Carga una imagen desde un fichero
         @param nombreFichero nombre del fichero que contiene la imagen
         @retval true 	si ha tenido éxito en la lectura
         @retval false 	si se ha producido algún error en la lectura
         
         Lee desde disco los datos de la imagen llamada @a nombreFichero y la guarda en la memoria. La función debe asegurarse de que la imagen es de un tipo de imagen conocido y de que su tamaño es menor del tamaño máximo permitido (@c MAXDATOS).
         */
        bool Imagen::leerImagen(const char nombreFichero[]){
            bool correcto = false;
            
            TipoImagen tipo = infoPGM(nombreFichero, nfilas, ncolumnas);
            
            if(tipo == IMG_PGM_BINARIO){
                crear(nfilas, ncolumnas);
                
                if (leerPGMBinario(nombreFichero, datos, nfilas, ncolumnas)){
                    correcto = true;
                }
            }
            
            if(tipo == IMG_PGM_TEXTO){
                crear(nfilas, ncolumnas);
                
                if (leerPGMTexto(nombreFichero, datos, nfilas, ncolumnas)){
                    correcto = true;
                }
            }
            
            return correcto;
        }
    
        
        /**
         @brief Guarda una imagen desde un fichero 
         @param nombreFichero nombre del fichero que contiene la imagen
         @param esBinario toma el valor @c true si el fichero se escribe en formato binario o @c false en caso contrario.
         @retval true 	si ha tenido éxito en la escritura
         @retval false 	si se ha producido algún error en la escritura
         */
        bool Imagen::escribirImagen(const char nombreFichero[], bool esBinario){
            bool escribir;
            
            if (esBinario)
                escribir = escribirPGMBinario(nombreFichero, datos, nfilas, ncolumnas);
            else
                escribir = escribirPGMTexto(nombreFichero, datos, nfilas, ncolumnas);
            
            return escribir;
        }

        Imagen Imagen::plano(int k){
            int filas_plano = filas();
            int col_plano = columnas();
            
            Imagen DePlano(filas_plano, col_plano);
            
            for (int i = 0; i < filas_plano; i++){
                for (int j = 0; j < col_plano; j++){
                    bool b = getbit(get(i, j), k);
                    
                    byte lak = 0;
                    
                    if(b)
                        on(lak, 7);
                    else
                        off(lak, 7);
                    
                    DePlano.set(i, j, lak);
                }
            }
            return DePlano;
        }

        bool Imagen::aArteASCII (const char grises[], char arteASCII[], int maxlong){
            bool cabe = false;
            int total_utilizados = 0;
            int contador = 0;
            int max_valor;
            int cardinal;
            
            max_valor = nfilas * ncolumnas;
            cardinal = strlen(grises);
            
            if((ncolumnas + 1) * nfilas <= maxlong){
                for(int i = 0; i <= max_valor; i++){
                    arteASCII[total_utilizados] = grises[datos[i] * cardinal / 256];
                    total_utilizados++;
                    contador++;
                    
                    if(contador == ncolumnas){
                        arteASCII[total_utilizados] = '\n';
                        total_utilizados++;
                        contador = 0;
                    }
                }
                
                arteASCII[total_utilizados] = '\0';
                cabe = true;
            }
            return cabe;
        }

        bool Imagen::listaAArteASCII(const Lista celdas){
            int cadenas = celdas.longitud();
            char arteASCII[1000001];
            bool resultado = true;
            ofstream fsalida;
    
            for (int i =0; (i < cadenas) && resultado; i++){
     			fsalida.open("ascii" + to_string(i + 1) + ".txt");
                if (fsalida){
                    resultado = resultado && aArteASCII((celdas.getCelda(i)).c_str(), arteASCII, 1000000);
                             
                    if (resultado)
                        fsalida << arteASCII << "\n";
                    else
                        fsalida << "La conversión no ha sido posible." << "\n";
                             
                    if (!fsalida)
                        resultado = false;
                }
                             
                fsalida.close();
            }
                             
            return resultado;
        }