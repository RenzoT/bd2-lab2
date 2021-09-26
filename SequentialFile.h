#include <iostream>
#include <string.h>
#include <fstream>
#include <vector>
#include "Registro.h"
#include <algorithm>

using namespace std;

class SequentialFile{
private:
  string dataFileName;
  string auxFileName;

  void reBuild(){
      
  }
  
  long binarySearch(fstream& file, long size, string key, bool &buscar){
    long int m;
    long int begin = 0;
    long int last = size - 1;

    Registro registro;

    while(begin <= last) {
        m = begin + (last - begin) / 2;
        file.seekg(m * (sizeof(Registro) + 1));
        file.read((char*) &registro, sizeof(Registro));
        
        if(string(registro.codigo) == key) {
            buscar = true;
            return m;
        }

        if(string(registro.codigo) < key) {begin = m + 1;}   
        else {last = m - 1;}
    }

    if(key > string(registro.codigo)) {
        return m;
    } else {
        return m - 1; 
    }
  }

  long LinearSearch(fstream &file, string key, Registro registro, bool buscar){
    long pos;
    while(registro.next != -1 && registro.file != 'd' && registro.codigo != key){
      file.seekg(registro.next * (sizeof(Registro) + 1));
      pos = file.tellg() / (sizeof(Registro) +1);
      file.read((char*) &registro, sizeof(Registro));
    }
    if(registro.codigo == key){
      buscar = true;
    }

    return pos;
  }

  
public:
  SequentialFile(string fileName,string auxName){
    this->dataFileName = fileName + ".dat";
    this->auxFileName = auxName + ".dat";
  }

  void insertAll(vector<Registro> registros){
    fstream file;
    file.open(this->dataFileName, ios::binary);

    if(file.is_open()){
      //sort
        sort(registros.begin(), registros.end(), [this](const Registro& r1, const Registro& r2) {
            return strcmp(r1.codigo, r2.codigo) < 0;
        });

        file.seekg(0, ios::end);

        long  next = 1;

        for(auto it = begin(registros); it != end(registros); ++it) {
            (*it).next = next;

            if(it == end(registros) - 1) {
                (*it).next= -1;
            }

            file.write((char*)&(*it),sizeof(Registro));
            ++next;
        }

        file.close();

    }
    else{
        cout<<"No se pudo abrir el archivo"<<endl;
    }
  }

  void add(Registro registro){
      fstream mainFile;
      mainFile.open(this->dataFileName,ios::binary);

      if (mainFile.is_open()){
        bool exists = false;
        mainFile.seekg(0,ios::end);
        long n_elements = mainFile.tellg()/(sizeof(Registro) + 1);
        long pos = binarySearch(mainFile,n_elements,registro.codigo,exists);

        if (exists){
            cout<<"El registro ya existe "<<endl;
        }
        else{
            Registro record;
            mainFile.seekg(pos * sizeof(Registro) + 1);
            mainFile.read((char*)&record,sizeof(record));

            fstream auxFile;
            auxFile.open(this->auxFileName, ios::binary);

            if (auxFile.is_open()){
                long aux_pos;
                long next;
                char file;

                if (record.file == 'a'){
                    aux_pos = LinearSearch(auxFile,record.codigo,record,exists);

                    if (exists){
                        throw "El registro ya existe ";
                    }
                    else{
                        next = record.next;
                        file = record.file;

                        auxFile.seekg(0,ios::end);
                        record.next = (auxFile.tellg()/(sizeof(Registro) + 1));
                        record.file = 'a';

                        auxFile.seekg(aux_pos * sizeof(Registro) + 1);
                        auxFile.write((char*) &record,sizeof(Registro));
                    }

                }
                else{
                    next = record.next;
                    file = record.file;

                    auxFile.seekg(0,ios::end);
                    record.next = (auxFile.tellg() / (sizeof(Registro) + 1));
                    record.file = 'a';

                    mainFile.seekg(pos * sizeof(Registro) + 1);
                    mainFile.write((char*) &record,sizeof(Registro));
                }
                
                auxFile.seekg(0, ios::end);
                registro.next = next;
                registro.file = file;
                auxFile.write((char*) &registro,sizeof(Registro));

                long n_elementsAux = auxFile.tellg() / (sizeof(Registro) + 1);

                auxFile.close();

                if(n_elementsAux == 5) {
                    reBuild();
                }

            }
            else{
                cout<<"No se pudo abrir el archivo auxiliar"<<endl;
            }

        }

      }
      else{
          cout<<"No se pudo abrir el archivo de datos"<<endl;
      }
  }

  Registro search(string key){
    Registro record;

    fstream inFile;
    inFile.open(this->dataFileName,ios::binary);
    if (inFile.is_open()){
      
      bool exists = false;
      inFile.seekg(0,ios::end);
      long n_elements = inFile.tellg() / (sizeof(Registro) + 1);
      long pos = binarySearch(inFile,n_elements,key,exists); //binarySearch
      inFile.seekg(pos * (sizeof(Registro) + 1));
      inFile.read((char*)&record, sizeof(Registro));
      inFile.close();

      if (exists){
        return record;
      }
      else{
        if(record.file == 'd'){
            throw "El registro no existe";
        }
        else{
          fstream auxFile;
          auxFile.open(this->auxFileName,ios::binary);

          if (auxFile.is_open()){
            LinearSearch(auxFile,key,record,exists);
            auxFile.close();

            if (exists) return record;
            else throw "El registro no existe";

          }
          else{
            throw "No se pudo abrir el archivo auxiliar";
          }
        }
      }
    }
    
    else{
      throw "No se pudo abrir el archivo de datos";
    }
  }
  
  vector<Registro> search(string begin, string end){
    
  }
  
};