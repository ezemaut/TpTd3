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
    /* completar */
};

#endif