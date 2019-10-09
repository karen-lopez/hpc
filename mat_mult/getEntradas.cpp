#include <stdio.h>
#include <iostream>
using namespace std;

//compile line:g++ getEntradas.cpp -o get
//./get >entradas

int main() {

  /*/if(argc!=5){ // para crear entradas manualmente
    cout<<"-Para compilar ejecute: \n"
    "\tg++ -std=c++11 -pthread prueba1.cc -o main.out\n"
    "-Ejemplo de llamado: \n"
    "\t./main.out <# hilos> <tamano de la matrix> <operacion> <out name>\n"
    "-Operaciones: \n"
    "\t1. secuencial.\n"
    "\t2. x hilos\n"
    "\t3. tiling\n"
    "\t4. tiling x hilos\n";
    return 0;
  //}*/
  int t = 2;
  for(int i = 0; i < 15; i++){

    //secuencial
    for (int i = 1; i <= 10; i++) {
      cout<<0<<" "<<i*100<<" "<<1<<endl;

    }

    //hilos, t = numero de hilos
    for (int i = 1; i <= 10; i++) {
      cout<<t<<" "<<i*100<<" "<<2<<endl;

    }

    //tiling
    for (int i = 1; i <= 10; i++) {
      cout<<t<<" "<<i*100<<" "<<3<<endl;

    }

        //tiling x hilos
    for (int i = 1; i <= 10; i++) {
      cout<<t<<" "<<i*100<<" "<<4<<endl;
    }
    if(i == 4) t = 4;
    if(i == 9) t = 6;

  }
  return 0;
}
