
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
    //caracteristicas privadasSS
    string nombre;

public:
    //caracteristicas publicasSS
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

enrutador::enrutador()
{
    string nombre = "";
    conexiones.clear();
}

enrutador::~enrutador()
{

}

string enrutador::getNombre() const
{
    return nombre;
}

void enrutador::setNombre(const string &value)
{
    nombre = value;
}

void enrutador::Conectar_Enrutador(const string &name, int costo)
{

    conexiones[name] = costo;
}

void enrutador::eliminar_Enrutador(const string &name)
{
    conexiones.erase(name);
}

void enrutador::Agregar_Conexion(const string &name, const string &anterior, int costo)
{
    costoNodos[name] = make_pair(costo,anterior);
}

void enrutador::TablaConexiones()
{

    cout << " \t";// PRIMERA PARTE  A B C D F  (SUPERIOR)
    for(it=conexiones.begin();it!=conexiones.end();it++){
        cout << it->first << "\t";
    }
    cout << endl << endl << nombre << "\t";
    //VALORES CADA CONEXION
    for(it=conexiones.begin();it!=conexiones.end();it++){
        cout << it->second << "\t";
    }



    cout << endl;
}

void enrutador::TablaCostos()
{

    cout << " \t";// PRIMERA PARTE  A B C D F ,, ,, , ,  (SUPERIOR)
    for(it2=costoNodos.begin();it2!=costoNodos.end();it2++){
        cout << it2->first << "\t";
    }
    cout << endl << endl << nombre << "\t";
    //VALORES D CADA COSTO
    for(it2=costoNodos.begin();it2!=costoNodos.end();it2++){
        cout << it2->second.first << "\t";
    }



    cout << endl;
}





#endif // NODO_ENRUTADOR_OR_ROUTER_H
