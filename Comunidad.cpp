#include "Comunidad.h"

using namespace std;

Comunidad::Comunidad(){
    /* completar */
}

const set<int> & Comunidad::inscriptos() const{
    /* completar */

    /* El siguiente return sirve
    para que el proyecto vacio compile
    sin errores. Al implementar la funcion
    lo tienen que borrar.
     */
    return *(new set<int>);
}
string Comunidad::obtener_empresa(int id) const{
    /* completar */
    return "";
}
const set<string> & Comunidad::obtener_socios(int id) const{
    /* completar */

    /* El siguiente return sirve
    para que el proyecto vacio compile
    sin errores. Al implementar la funcion
    lo tienen que borrar.
     */
    return *(new set<string>);
}
int Comunidad::cantidad_asociaciones() const{
    /* completar */
    return 0;
}

void Comunidad::inscribir(string empresa, int id){
    /* completar */
}
void Comunidad::desinscribir(int id){
    /* completar */
}

void Comunidad::asociar(string empresa_A, string empresa_B){
    /* completar */
}
void Comunidad::desasociar(string empresa_A, string empresa_B){
    /* completar */
}

int Comunidad::obtener_id(string empresa) const{
    /* completar */
    return 0;
}
bool Comunidad::es_empresa_popular(string empresa) const{
    /* completar */
    return false;
}