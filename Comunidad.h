#ifndef __COMUNIDAD_H__
#define __COMUNIDAD_H__

#include <string>
#include <map>
#include <set>
#include <unordered_set>

using namespace std;

class Comunidad{
  public:
    Comunidad(); // O(1)

    const set<int> & inscriptos() const; // O(1)
    string obtener_empresa(int id) const; // O(log n)
    const set<string> & obtener_socios(int id) const; // O(log n)
    int cantidad_asociaciones() const; // O(1)
    int obtener_id(string empresa) const; // sin requerimiento
    bool es_empresa_popular(string empresa) const; // O(1) promedio

    void inscribir(string empresa, int id); // O(log n)
    void desinscribir(int id); // sin requerimiento
    void asociar(string empresa_A, string empresa_B); // sin requerimiento
    void desasociar(string empresa_A, string empresa_B); // sin requerimiento
    

  private:
    set<int> _inscriptos = {};//ids de empresas inscriptas
    map<int,string> mapa_id_a_nombre = {}; //Clave es el id -> nombre de la empresa (obtener_empresa O(log n))
    map<string,set<string>> mapa_nombre_a_set_asociaciones = {}; //Clave es el nombre -> direccion de set(obtener socios O(log n) n= size del map)
    int _cantidad_asociaciones = 0; // cantidad_asociaciones() O(1)
    unordered_set<string> Uset_empresas_populares = {}; // es_empresa_popular(string empresa) O(1) promedio

  // n = .size() de cualquiera de los maps porque tienen la misma cantidad de claves.
};

#endif

/*
Comunidad(); // O(1)
O(1) + O(1) + O(1) + O(1) + O(1) = O(1) 

const set<int> & inscriptos() const; // O(1)
O(1)

obtener_empresa(int id) const; // O(log n)
O(log n) + O(1) = O(log n)

const set<string> & obtener_socios(int id) const; // O(log n)
O(log n) + O(log n) + O(1) = O(log n)

int cantidad_asociaciones() const; // O(1)
O(1)

bool es_empresa_popular(string empresa) const; // O(1) promedio
O(1) promedio + O(1) = O(1) promedio

void inscribir(string empresa, int id); // O(log n)
O(log n) + O(log n) + O(log n) = O(log n)


Invariante:
_inscriptos contiene todos los ids de las empresas inscriptas. 
Las claves en los mapas: mapa_id_a_nombre y mapa_nombre_a_set_asociaciones son iguales a TODOS los elementos de _inscriptos en cuanto a su
valor y cantidad.
En el mapa, mapa_id_a_nombre, cada clave esta asociada al string correspondite a su id.
En el mapa, mapa_nombre_a_set_asociaciones, cada calve esta asociada a un set que contiene strings del nombre de todas
las empresas asociadas y si no tiene asocaiones contiene un set vacio.
_cantidad_asociaciones es igual a la cantidad de asociaciones unicas entre empresas.
Uset_empresas_populares, contiene unicamente a todas las empresas que tienen 5 o mas asociaciones.



Valores que cumplen el invariante:

set<int> _inscriptos = {10, 21, 23};
map<int,string> mapa_id_a_nombre = {[10, Messi], [21, Dybala], [23, Dibu]}; 
map<string,set<string>> mapa_nombre_a_set_asociaciones = {[Messi, {Dybala, Dibu}], [Dybala, {Messi}], [Dibu, {Messi}]}; 
int _cantidad_asociaciones = 2;
unordered_set<string> Uset_empresas_populares = {}; 



Valores que NO cumplen el invariante:

set<int> _inscriptos = {7, 10, 30};
map<int,string> mapa_id_a_nombre = {[7, Mbappe], [10, Ney], [30, Messi], [1, Donna]}; 
map<string,set<string>> mapa_nombre_a_set_asociaciones = {[Ney, {Messi}], [Messi, ]}; 
int _cantidad_asociaciones = 3;
unordered_set<string> Uset_empresas_populares = {Mbappe}; 

Errores: 
mapa_id_a_nombre: existe [1, Donna] sin pertenecer a _inscriptos
mapa_nombre_a_set_asociaciones: No existe la clave Mbappe, Messi no esta asoaciado a Ney aunque Ney este asociado a Messi y
Messi ni siquera tiene un set vacio.
_cantidad_asociaciones: deberia ser 0 o 1 dependiendo si se ceunta la asociacion Ney/Messi
Uset_empresas_populares: Mbappe no es popular y sin embargo pertenece al Uset exclusivo para populares.
*/
