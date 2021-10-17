#ifndef REGISTRO_H
#define REGISTRO_H
#include <iostream> 
struct Registro{
  char codigo [5];
  char nombre [20];
  char carrera [15];
  int  ciclo;
  long next;
  char file;

  void print(){
    std::cout<<codigo<<" "<<nombre<<" "<<carrera<<" "<<ciclo<<" "<<next<<" "<<file<<std::endl;
  }
};

#endif //REGISTRO_H