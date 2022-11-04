#include "Comunidad.h"

using namespace std;

Comunidad::Comunidad(){
}

const set<int> & Comunidad::inscriptos() const{

    return _inscriptos; // O(1)
}
string Comunidad::obtener_empresa(int id) const{
    
    auto empresa = mapa_id_a_nombre.find(id); // O(log n)
    return (empresa->second); 
    
}
const set<string> & Comunidad::obtener_socios(int id) const{

    string nombre = obtener_empresa(id);

    auto empresa = mapa_asociaciones.find(nombre); // O(log n)
    return (empresa->second); 
}
int Comunidad::cantidad_asociaciones() const{

    return _cantidad_asociaciones;
}

void Comunidad::inscribir(string empresa, int id){
    //Post: El conjunto inscriptos() tiene un elemento más: id; y obtener_empresa(id) devuelve empresa.

    _inscriptos.insert(id); // O(log n)
    mapa_id_a_nombre[id] = empresa; //O(log n)
    mapa_asociaciones[empresa] = {};
}
void Comunidad::desinscribir(int id){
    //Post: Se elimina la empresa id del sistema y se eliminan todas las asociaciones de las que participaba.

    _inscriptos.erase(id);
    string nombre_a_borrar = obtener_empresa(id);
    mapa_id_a_nombre.erase(id);

    set<string> set_a_borrar = mapa_asociaciones[nombre_a_borrar];
    set<string>::iterator it = set_a_borrar.begin();

    for (int i = 0; i < set_a_borrar.size(); i++)
    {
        desasociar(nombre_a_borrar,*it);
        ++it;
    }
    
    mapa_asociaciones.erase(nombre_a_borrar);
}

void Comunidad::asociar(string empresa_A, string empresa_B){
    
    auto empresaA = mapa_asociaciones.find(empresa_A); 
    (empresaA->second).insert(empresa_B); 
    if(empresaA->second.size() >= 5) Uset_empresas_populares.insert(empresa_A);

    auto empresaB = mapa_asociaciones.find(empresa_B); 
    (empresaB->second).insert(empresa_A); 
    if(empresaB->second.size() >= 5) Uset_empresas_populares.insert(empresa_B);

    _cantidad_asociaciones++;
    
}
void Comunidad::desasociar(string empresa_A, string empresa_B){

    auto empresaA = mapa_asociaciones.find(empresa_A); 
    (empresaA->second).erase(empresa_B); 
    if(empresaA->second.size() < 5 && es_empresa_popular(empresa_A)) Uset_empresas_populares.erase(empresa_A);

    auto empresaB = mapa_asociaciones.find(empresa_B); 
    (empresaB->second).erase(empresa_A); 
    if(empresaB->second.size() < 5 && es_empresa_popular(empresa_B)) Uset_empresas_populares.erase(empresa_B);

    _cantidad_asociaciones--;
}

int Comunidad::obtener_id(string empresa) const{
    int vr;
    for (auto elemento : mapa_id_a_nombre)
    {
        if (elemento.second == empresa) vr = elemento.first;
    }
    return vr;
}
bool Comunidad::es_empresa_popular(string empresa) const{

    bool rv = true;

    unordered_set<string>::const_iterator got = Uset_empresas_populares.find(empresa); //Average case: constant.
    if (got == Uset_empresas_populares.end()) rv = false;

    return rv;
}