#include "REDFr.h"
red::red()                // Constructor de la clase red
{
}

red::~red()               // Destructor de la clase red
{
}

list<enrutador> red::getN_enrutadores() const   // Metodo para obtener la lista de enrutadores de la red
{
    return n_enrutadores;
}

void red::setN_enrutadores(const list<enrutador> &value)  // Metodo para asignar la lista de enrutadores de la red
{
    n_enrutadores = value;//value hace referncia a lista de objetos de la clase enrutador
}

void red::agregar_Enrutador(const string &router_name)   // Metodo para agregar un nuevo enrutador a la red
{
    enrutador *router = new enrutador;                   // Se crea un nuevo objeto enrutador
    router->setNombre(router_name);                      // Se le asigna un nombre al enrutador
    router->Conectar_Enrutador(router->getNombre(),0);    // Se conecta el enrutador consigo mismo
    n_enrutadores.push_back(*router);                     // Se agrega el enrutador a la red // lista de enrutadores
    Conexiones_Iniciales(router->getNombre());            // Se establecen las conexiones iniciales del enrutador

    delete router;                                        // Se libera la memoria ocupada por el objeto enrutador
}

void red::Conexiones_Iniciales(const string &router_name)  // Método para establecer las conexiones iniciales de un enrutador
{
    for(auto router1=n_enrutadores.begin();router1!=n_enrutadores.end();router1++){   // Se recorre la lista de enrutadores
        if(router1->getNombre()==router_name){                                        // Si se encuentra el enrutador cuyas conexiones iniciales se desean establecer
            for(auto router2=n_enrutadores.begin();router2!=n_enrutadores.end();router2++){  // Se recorre la lista de enrutadores
                if(router1->getNombre()!=router2->getNombre()){                                 // Si el enrutador no es el mismo
                    router1->Conectar_Enrutador(router2->getNombre(),-1);                        // Se conecta el enrutador 1 con el enrutador 2 con costo -1
                    router2->Conectar_Enrutador(router1->getNombre(),-1);                        // Se conecta el enrutador 2 con el enrutador 1 con costo -1
                }
            }
            break;
        }
    }
}

void red::eliminar_Enrutador(const string &router_name)
{
    for(auto router=n_enrutadores.begin();router!=n_enrutadores.end();router++){// ELIMINAMOS CADA CONEXION
        if(router->getNombre()!=router_name)//BORRAR LA CONEXION CON CADA ROUTER (ENRUTADOR)
            router->eliminar_Enrutador(router_name);// FUNCION PARA BORRA LA CONEXION DE UN ROTER CON OTRO
    }
    // SE BUSCA EL ENRUTADOR EN LA LISTA DE RED
    for(auto router=n_enrutadores.begin();router!=n_enrutadores.end();router++){
        if(router->getNombre()==router_name){
            n_enrutadores.erase(router);// SE BORRA EL ENRUTADOR DE LA RED
            break;
        }
    }
}

void red::Conectar2Enrutadores(const string &name1, const string &name2, int cost)
{
    for(auto router1=n_enrutadores.begin();router1!=n_enrutadores.end();router1++){
        if(router1->getNombre()==name1){//ENCONTRAMOS EL PRIMERE ROUTER
            // YA TENIENDO EL PRIMERO BUSCAMOS EL SEGUNDO
            for(auto router2=n_enrutadores.begin();router2!=n_enrutadores.end();router2++){
                if(router2  ->getNombre()==name2){// SEGUNDO ROUTER
                    //CONECTAMOS LOS ROUTERS
                    router1->Conectar_Enrutador(router2->getNombre(),cost);
                    router2->Conectar_Enrutador(router1->getNombre(),cost);
                }
            }
            break;
        }
    }
}

