#include "REDFr.h"
#include "Nodo_enrutador_or_router.h"


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

int red::Costo(const string &salida, const string &llegada)
{
    int costo = -1;
    for(auto router=n_enrutadores.begin();router!=n_enrutadores.end();router++){
        if(router->getNombre()==salida){// ENCONTRAMOS (PARTIDA)  ROUTER SALIDA
            for(router->it2=router->costoNodos.begin();router->it2!=router->costoNodos.end();router->it2++){
                if(router->it2->first==llegada){//ENCONTRAMOS EL COSTO CON LA SALIDA LLEGADDA
                    //cout<<router->it2->second.second;

                    //EL SECOND DEL SECOND INDICA CUAL ES LA ULTIMA CONEXION
                    //PARA LLEGAR A LA LLEGADA (SISTEMA GRAFOS) ALGORITM
                    costo = router->it2->second.first;
                    break;
                }
            }
            break;
        }
    }
    return costo;
}

void red::MejorCamino(const string &salida, const string &llegada)
{
    list<string> ruta;
    string nodo;
    nodo = llegada;
    ruta.push_back(nodo);
    //RECOREMOS ASTA ENCONTRAR EL ROUTER DE PARTIDA(SALIDA)
    for(auto router=n_enrutadores.begin();router!=n_enrutadores.end();router++){
        if(router->getNombre()==salida){
            while(nodo!=salida){
                //RECORREMOS SIEMPRE TENIENDO DE BASE EL ROUTER DE PARTIDA(SALIDA)

                //VAMOS AGREGANDO LAS RUTAS DE ULTIMO A PRIMERO RAZON POR LA QUE USO L PUSH FRONT

                //EL SECOND SECOND TIENE LA ULTIMA UBICACION

                //estaremos siempre en el mismo router hastq que el secont second sea la misma partida
                for(router->it2=router->costoNodos.begin();router->it2!=router->costoNodos.end();router->it2++){
                    if(router->it2->first==nodo){
                        nodo = router->it2->second.second;// se actualiza el nodo
                        ruta.push_front(nodo);
                        break;
                    }
                }
            }
            break;
        }
    }

    for(auto router=ruta.begin();router!=ruta.end()--;router++){
        if(router==ruta.begin())
            cout << *router;
        else
            cout << " --> " << *router;
    }
    cout << endl;
}

bool red::comprobar_Enrutador(const string &router_name)
{
    for(auto it=n_enrutadores.begin();it!=n_enrutadores.end();it++){
        if(it->getNombre()==router_name) return true;
    }
    return false;
}

void red::AlgoritmoDijkstra(const string &nodoInicial)

{
    list<string> nodosVistos;
    string nodo = nodoInicial;
    int costo = 0;
    enrutador *router = new enrutador;
    //BUSCAMOS EL NODO EN LA LISTA DE LA REDDD
    for(auto p=n_enrutadores.begin();p!=n_enrutadores.end();p++){//encontramos nodo
        if(p->getNombre()==nodoInicial){
            router->setNombre(p->getNombre());// nombre del nodo tm
            router->conexiones = p->conexiones; // CONEXIONES NODO CON NODO
            break;
        }
    }
    for(router->it=router->conexiones.begin();router->it!=router->conexiones.end();router->it++){
        if(router->it->first == router->getNombre())
            //SE CONECTA ROUTER CON SI MISMO EN  LISTA DE COSTOS
            router->Agregar_Conexion(router->getNombre(),router->getNombre(),0);
        else if(router->it->second  != -1)
            //LAS CONECIONES INICIALES DEL ROTER CON LO SDEMAS EN LA LISTA DE COSTOS(MEJOR CAMI)
            router->Agregar_Conexion(router->it->first,router->getNombre(),router->it->second);
    }
    nodosVistos.push_back(nodo);// EN ESTE PUNTO SOLO TENEMOOS EL MISMO NODO (INICIAL)
    while(true){
        //elegir el nodo de menor costo
        costo = 1000000000;

        for(router->it2=router->costoNodos.begin();router->it2!=router->costoNodos.end();router->it2++){
            //si no encuentra  en lista de nodos vistos
            if(find(nodosVistos.begin(),nodosVistos.end(),router->it2->first) == nodosVistos.end()){

                // si el costonodos es menor al actual costo
                if(router->it2->second.first < costo){
                    costo = router->it2->second.first;
                    nodo = router->it2->first;
                }
            }
        }// AQUI SALE EL PRIMERO  NODO CON MENOR COSTO DE CADA ENRUTADOR Y QUE NO ESTA EN LT NV


        //si se encuentra el nodo en la lista de nodos vistos, terminar el ciclo
        if(find(nodosVistos.begin(),nodosVistos.end(),nodo) !=  nodosVistos.end())

        break;
        //buscar el nodo en la lista de enrutadores y revisar sus conexiones
        /////cout<<"____help___"<<nodo<<"____"<<endl;
        for(auto router2=n_enrutadores.begin();router2 != n_enrutadores.end();router2++){

            if(router2->getNombre() == nodo){

                for(router2->it = router2->conexiones.begin();router2->it != router2->conexiones.end();router2->it++){
                    //para evitar ciclo en la red (grafos)
                    if(find(nodosVistos.begin(),nodosVistos.end(),router2->it->first)!= nodosVistos.end()){
                        //agregar conexión si el costo es mayor que cero y no se está conectando consigo mismo

                    }else if(router2->it->first!=router->getNombre() and router2->it->second>0){
                        //si el nodo no está en la lista de costos, agregar la conexión
                        if(router->costoNodos.find(router2->it->first)==router->costoNodos.end()){

                            router->Agregar_Conexion(router2->it->first,router2->getNombre(),router2->it->second+costo);
                        }
                        //si el costo es menor al costo actual, actualizar el costo
                        else if(router2->it->second+costo < router->costoNodos.find(router2->it->first)->second.first){

                            router->Agregar_Conexion(router2->it->first,router2->getNombre(),router2->it->second+costo);
                        }
                    }
                }

                break;
            }
        }
        nodosVistos.push_back(nodo);
    }

    for(auto borrar=n_enrutadores.begin();borrar!=n_enrutadores.end();borrar++){
        if(borrar->getNombre()==router->getNombre()){
            n_enrutadores.erase(borrar);
            break;
        }
    }

    n_enrutadores.push_back(*router);
    OrdenarLista();
    delete router;
}

void red::ActualizarTabla()
{
    list<string> router_name;
    string nodo;
    /*for(auto router=n_enrutadores.begin();router!=n_enrutadores.end();router++){
        for(router->it=router->conexiones.begin();router->it!=router->conexiones.end();router->it++){
          //  router_name.push_back(router->it->first);
        //}
            break;
            }
        }
        /*/


    //SACAR NOMBRE DE LOS ROUTERS
    for(auto router=n_enrutadores.begin();router!=n_enrutadores.end();router++){
        router_name.push_back(router->getNombre());
    }


    //APLICAR EL ALGORIMO DE MEJOR CAMINO PARA ACTUALILIZAR CONEXIONES Y COSTOS
    for(auto router=router_name.begin();router!=router_name.end();router++){
        nodo = *router;

        AlgoritmoDijkstra(nodo);
    }
}

void red::TablaConexionesRed()
{
    cout << " \t";// PRIMERA PARTE  A B C D F , , , ,   (SUPERIOR)
    for(auto router=n_enrutadores.begin();router!=n_enrutadores.end();router++){
        cout << router->getNombre() << "\t";
    }
    cout << endl << endl;

    for(auto router=n_enrutadores.begin();router!=n_enrutadores.end();router++){
        //NAME DEL ROTERRRRR
        cout << router->getNombre() << "\t";
        // CONEXIONE S ED CADA ROUTER
        for(router->it=router->conexiones.begin();router->it!=router->conexiones.end();router->it++){
            cout << router->it->second << "\t";
        }
        cout << endl << endl;
    }
}

void red::TablaCostosRed()
{
    cout << " \t";// PRIMERA PARTE  A B C D F , , ,(,SUPERIOR)
    for(auto router=n_enrutadores.begin();router!=n_enrutadores.end();router++){
        cout << router->getNombre() << "\t";
    }
    cout << endl << endl;

    for(auto router=n_enrutadores.begin();router!=n_enrutadores.end();router++){
        cout << router->getNombre() << "\t";//NOMBRE DE CASA ROTER LUEGO SUS COSTOS
        for(auto router2=n_enrutadores.begin();router2!=n_enrutadores.end();router2++){
            //UTILIZAMOS FUNCION COSTA QUE DEVUELVE EL COSTO DE MEJOR CAMINO ENTRE DOS NODOS (ROUTERS)
            cout << Costo(router->getNombre(),router2->getNombre()) << "\t";
        }
        cout << endl << endl;
    }
}

void red::TablaConexionesEnrutador(const string &nodo)
{
    for(auto router=n_enrutadores.begin();router!=n_enrutadores.end();router++){
        if(router->getNombre()==nodo){
            router->TablaConexiones();
        }
    }
}

void red::TablaCostosEnrutador(const string &nodo)
{
    for(auto router=n_enrutadores.begin();router!=n_enrutadores.end();router++){
        if(router->getNombre()==nodo){
            router->TablaCostos();
        }
    }
}

void red::OrdenarLista()
{
}

bool red::ComprobarConexion(const string &nodo, const string &nodo2)

{
    //ENCONTRAMOS EL PRIMER NODO
    for(auto router=n_enrutadores.begin();router!=n_enrutadores.end();router++){
        if(router->getNombre()==nodo){
            //COMPROBAMOS SU CONEXION CON EL NODO 2
            if(router->conexiones[nodo2] == -1){
                return false;
                break;
            }
        }
    }
    return true;
}

void red::LeerTexto(const string &nombretexto)
{
    string nodo="",linea="";
    fstream lectura;
    int numeroDeNodos=0;
    list<string> l_nodos;

    lectura.open(nombretexto);
    if(lectura.fail()){
        cout<<"No se pudo abrir el archivo." << endl;
    }
    getline(lectura,linea);


    numeroDeNodos= (char) linea[0]-48;
    cout<<numeroDeNodos;
    getline(lectura,linea);
    while(numeroDeNodos>0){
        getline(lectura,linea);
        l_nodos.push_back(linea);
        numeroDeNodos--;
    }

    list<string>:: iterator FrA ;
    for(FrA = l_nodos.begin();FrA != l_nodos.end();FrA++){
        cout<<*FrA<<endl;
        agregar_Enrutador(*FrA);
    }
    getline(lectura,linea);
    while(lectura.good()){
        linea.clear();
        getline(lectura,linea);
        getline(lectura,nodo);
        Conectar2Enrutadores(linea,nodo,4);
    }

    lectura.close();
    ActualizarTabla();
}

void red::GenerarRedAleatoria()
{
    srand(time(NULL));
    int  num=4+rand()%(10-3);//RANGO ENTRE 4 _ 10 ROUTERS
    cout << "Nodos generados: " << num << endl;
    string nodo;
    list<string> l_nodos;

    for (int i=0,j=65;i<num ; i++,j++) {

        nodo=j;
        agregar_Enrutador(nodo);
    }
    ActualizarTabla();

    for(auto i=n_enrutadores.begin();i!=n_enrutadores.end();i++){
        l_nodos.push_back(i->getNombre());
    }

    for(auto i=l_nodos.begin();i!=l_nodos.end();i++){
        int num_enlaces=2+ rand()%(l_nodos.size()-2);//DEJAR ALMENOS UNO DESCONECTC
        nodo = *i;//NODO
        for(int j=0;j<num_enlaces;j++){
            string nodo2;
            //PARA QUE SEA MUY ALEATORIA PONEMOS UNA VARIABLE -_____ ENLACE ____--
            int enlace = rand()%(l_nodos.size());//P POCISION ALEATORIA
            int pos = 0;
            for(auto nombre=l_nodos.begin();nombre!=l_nodos.end();nombre++){
                // CUANDO ESTEMOS EN LA POCION ALEATORIA DEL NODO CON ESE NOMBBRE
                if(pos==enlace){
                    nodo2 = *nombre;
                    break;
                }
                pos ++;
            }
            if(ComprobarConexion(nodo,nodo2)==false){
                int costo = 1 + rand()%(50);
                Conectar2Enrutadores(nodo,nodo2,costo);
            }
        }
    }
    ActualizarTabla();
}

