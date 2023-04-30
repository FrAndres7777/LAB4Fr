
#ifndef REDFR_H
#define REDFR_H


class red
{
private:
    list <enrutador> n_enrutadores;

    void Conexiones_Iniciales(const string &router_name);
public:
    red();
    ~red();
    void agregar_Enrutador(const string &router_name);
    void eliminar_Enrutador(const string &router_name);


    list<enrutador> getN_enrutadores() const;
    void setN_enrutadores(const list<enrutador> &value);
};




#endif // REDFR_H


