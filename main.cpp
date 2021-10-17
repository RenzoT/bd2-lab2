#include <iostream>
#include <string.h>
#include "SequentialFile.h"
#include <vector>

using namespace std;


int main() {
  auto sec = SequentialFile("datos","data_aux");
  Registro registro1{"0001", "Alonso", "CS", 2};
  Registro registro2{"0003", "Lucero", "Ing Civil", 3};
  Registro registro3{"0004", "Noemi", "Turismo", 1};
  Registro registro4{"0002", "Diana", "Bioingenieria", 8};
  Registro registro5{"0111", "Alejandro", "Arquitectura", 3};
  Registro registro6{"0222", "Violeta", "CS", 2};

  vector<Registro> records;
  records.push_back(registro1);
  records.push_back(registro2);
  records.push_back(registro3);
  records.push_back(registro4);
  records.push_back(registro5);
  records.push_back(registro6);

  sec.insertAll(records);
  //sec.print();
  Registro registro7{"0123", "Mauro", "CS", 10};
  Registro registro8{"0333", "Mauro", "CS", 10};
  Registro registro9{"0444", "Mauro", "CS", 10};
    Registro registro10{"0234", "Mauro", "CS", 10};
    Registro registro11{"0232", "Mauro", "CS", 10};
    Registro registro12{"0009", "Mauro", "CS", 10};
    Registro registro13{"1253", "Mauro", "CS", 10};
  //sec.deleteRow("0111");
  sec.add(registro7);
  sec.add(registro8);
  sec.add(registro9);
    sec.add(registro10);
    sec.add(registro11);
    sec.add(registro12);
  sec.print();
  //sec.add(registro7);
  auto rec = sec.search("0003","0440");
  for (auto it = begin(rec); it != end(rec); it++){
    (*it).print();
  }

  return 0;
}