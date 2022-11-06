#include "Comunidad.h"

using namespace std;

Comunidad::Comunidad(){
}

const set<int> & Comunidad::inscriptos() const{

    return _inscriptos; // O(1)
}
string Comunidad::obtener_empresa(int id) const{
    
    auto empresa = mapa_id_a_nombre.find(id); // O(log n) )
    return (empresa->second); // O(1)
    
}
const set<string> & Comunidad::obtener_socios(int id) const{

    string nombre = obtener_empresa(id); //O(log n) 

    auto empresa = mapa_nombre_a_set_asociaciones.find(nombre); // O(log n)
    return (empresa->second); // O(1)
}
int Comunidad::cantidad_asociaciones() const{

    return _cantidad_asociaciones; // O(1)
}

void Comunidad::inscribir(string empresa, int id){
    //Post: El conjunto inscriptos() tiene un elemento más: id; y obtener_empresa(id) devuelve empresa.

    _inscriptos.insert(id); // O(log n) se puede hacer O(1) con una hint
    mapa_id_a_nombre[id] = empresa; //O(log n)
    mapa_nombre_a_set_asociaciones[empresa] = {}; //O(log n)
}
void Comunidad::desinscribir(int id){
    //Post: Se elimina la empresa id del sistema y se eliminan todas las asociaciones de las que participaba.

    _inscriptos.erase(id); // saca de la lista de inscriptos a id

    string nombre_a_borrar = obtener_empresa(id); // se guarda en nombre para uso futuro
    mapa_id_a_nombre.erase(id); // saca la entrada del mapa de id

    set<string> set_a_borrar = mapa_nombre_a_set_asociaciones[nombre_a_borrar]; // el set contiene todas las asociaciones de id.
    set<string>::iterator it = set_a_borrar.begin();

    for (int i = 0; i < set_a_borrar.size(); i++)
    {
        desasociar(nombre_a_borrar,*it);
        ++it;
    }
    // desasocia de todas las empresas que estan asociadas a id.
    // Saca los nombres del set de id y la empresa asociada hasta que el set de id este vacio.
    
    mapa_nombre_a_set_asociaciones.erase(nombre_a_borrar); // saca la clave que ahora esta vacia
}

void Comunidad::asociar(string empresa_A, string empresa_B){
    
    auto empresaA = mapa_nombre_a_set_asociaciones.find(empresa_A);
    int size1 = (empresaA->second).size(); // es el size antes del insert 
    (empresaA->second).insert(empresa_B); //si el elemento es distinto a todos los demas size1 < size2
    int size2 = (empresaA->second).size();// size1 y 2 se usan para ver si empresa_A y empresa_B ya estaban asociados 
    if(empresaA->second.size() >= 5) Uset_empresas_populares.insert(empresa_A);

    auto empresaB = mapa_nombre_a_set_asociaciones.find(empresa_B); 
    (empresaB->second).insert(empresa_A); 
    if(empresaB->second.size() >= 5) Uset_empresas_populares.insert(empresa_B);
    // Vemos si hay almenos 5 empresas asociadas, y si las hay, la empresa se considera popular
    // y es agregada al Unsorted Set de empresas populares. Esto se hace para empresa_A y empresa_B

    if (size1 < size2)_cantidad_asociaciones++; // si no estaban asociadas antes, _cantidad_asociaciones aumenta
}
void Comunidad::desasociar(string empresa_A, string empresa_B){

    auto empresaA = mapa_nombre_a_set_asociaciones.find(empresa_A); //busca empresa_A en el mapa
    (empresaA->second).erase(empresa_B); // saca empresa_B del set con las asocaiciones.
    if(empresaA->second.size() < 5 && es_empresa_popular(empresa_A)) Uset_empresas_populares.erase(empresa_A);

    auto empresaB = mapa_nombre_a_set_asociaciones.find(empresa_B); 
    (empresaB->second).erase(empresa_A); 
    if(empresaB->second.size() < 5 && es_empresa_popular(empresa_B)) Uset_empresas_populares.erase(empresa_B);
    // Vemos si la empresa antes era popular y ahora no lo es.  
    // En ese caso se las saca del Unsorted Set de empresas populares. Esto se hace para empresa_A y empresa_B

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
    if (got == Uset_empresas_populares.end()) rv = false; //O(1)

    // todas las empresas poulares pertencen a Uset_empresas_populares.
    // Si se busca la empresa en el Unsorted Set y no se encuentra entonces no es popular.

    return rv;
}