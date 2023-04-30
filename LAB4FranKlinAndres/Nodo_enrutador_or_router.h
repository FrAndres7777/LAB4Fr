
#ifndef NODO_ENRUTADOR_OR_ROUTER_H
#define NODO_ENRUTADOR_OR_ROUTER_H
#include <iostream>
#include <map>
#include <utility>
#include <algorithm>

using namespace std;

class enrutador
{
private:
    //caracteristicas privadas
    string nombre;

public:
    //caracteristicas publicas
    map<string,int> conexiones;
    map<string,pair<int,string>> costoNodos;
    map<string,int>::iterator it;
    map<string,pair<int,string>>::iterator it2;

    //metodos
    enrutador();
    ~enrutador();
    string getNombre() const;
    void setNombre(const string &value);

    void Conectar_Enrutador(const string &name,int costo);
    void eliminar_Enrutador(const string &name);
    void Agregar_Conexion(const string &name,const string &anterior, int cost);
    void TablaConexiones();
    void TablaCostos();
};

#endif // NODO_ENRUTADOR_OR_ROUTER_H
