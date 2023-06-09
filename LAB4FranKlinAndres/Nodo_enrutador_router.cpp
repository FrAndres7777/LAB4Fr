#include "Nodo_enrutador_or_router.h"

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

    cout << " \t";// PRIMERA PARTE  A B C D F  (SUPERIOR)
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
