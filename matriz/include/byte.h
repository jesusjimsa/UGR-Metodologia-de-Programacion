#ifndef _byte_H_
#define	_byte_H_

#include <string>
using namespace std;

typedef unsigned char byte;

void on(byte &b, int pos);

void off(byte &b, int pos);

bool getbit(byte b, int pos);

string byteToString(byte b);

void encender(byte &b);

void apagar(byte &b);

void asignar(byte &b, const bool v[]);

void volcar(byte b, bool v[]);

void encendidos(byte b, int posic[], int &cuantos);

#endif

