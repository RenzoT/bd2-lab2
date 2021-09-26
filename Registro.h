#ifndef REGISTRO_H
#define REGISTRO_H

struct Registro{
  char codigo [5];
  char nombre [20];
  char carrera [15];
  int  ciclo;
  long next;
  char file;
};

#endif //REGISTRO_H