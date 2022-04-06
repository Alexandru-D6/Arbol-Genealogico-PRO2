/** @file Tabla_distancias.hh
 *  @brief Especificacion de la Tabla de distancias (Tabla_distancias).
 */

#ifndef TABLA_DISTANCIAS_HH
#define TABLA_DISTANCIAS_HH

#include "Especie.hh"

using namespace std;

#ifndef NO_DIAGRAM   // sirve para ocultar este include al doxygen
#include <map>       // y de esta manera que no salga en el diagrama
#include <set>       // pero el compilador sigue viendo el include
#include <iostream>
#endif

/** @class Tabla_distancias
    @brief Representa una tabla cuadrada de las distancias entre distancias
*/

class Tabla_distancias {
public:

    //Constructoras
    
    /** @brief Creadora por defecto.
     * 
        \pre cierto.
        \post El resultado es una tabla de especies vacia.
    */ 
    Tabla_distancias();

    /** @brief Destructora por defecto. */
    ~Tabla_distancias();

    //Modificadoras

    /** @brief Modificadora que añade una distancia entre dos especies.
        
        \pre La distancia entre ambas especies no existe.
        \post Las especies son añadidas a la tabla con la distancia especificada en
              parametro explicito.
    */ 
    void anadir_distancia(const string& id1, const string& id2, const double& dist);

    /** @brief Modificadora que elimina una especie.
        
        \pre Cierto.
        \post Las distancias que hacen referencia a la especie son eliminadas, a su
              vez retorna un bool que indica si se ha podido eliminar satisfactoriamente
              la especie o no, con un true o false respectivamente.
    */ 
    bool eliminar_especie(const string& id);

    /** @brief Vaciadora de tabla.
        
        \pre cierto.
        \post Elimina todas las especies y la deja vacia.
    */ 
    void limpiar_tabla();

    //Consultoras

    /** @brief Consultora de distancia.
        
        \pre Las dos especies existen en la tabla con una distancia valida.
        \post El return devuelve la distancia entre ambas especies.
    */ 
    double get_distancia(const string& id1, const string& id2) const;

    /** @brief Consultora de tamaño.
        
        \pre cierto.
        \post Retorna el tamaño del map;
    */ 
    int size() const;

    /** @brief Consultora de la especie iesima.
        
        \pre La "i" del parametro explicito esta dentro de los limites 1 <= i <= M_dist.size().
        \post El return devuelve el id de la especie que se encuentra en la posicion "i".
    */ 
    string id_iesimo(int i);

    /** @brief Consultora de existencia de especie
        
        \pre Cierto.
        \post El return devuelve true o false si la especie se encuentra en el map o 
              no respectivamente.
    */ 
    bool existe_especie(const string& id);

    /** @brief Consultora de distancia minima

     *  El algoritmo ejecuta una busqueda secuencial buscando la distancia minima
     *  que hay entre todas las especies. En caso de empate solo tiene en cuenta la
     *  primera encontrada y de esta manera cumple con que la union de ambos identificadores
     *  es el menor lexicograficamente.

        \pre Cierto.
        \post Retorna la distancia minima que existe en la tabla de distancia 
              y los parametros explicitos retornan sus respectivos id-s.
    */ 
    double distancia_minima(string& id1, string& id2);

    //Escritura

    /** @brief Operacion de escritura.
        
        \pre cierto.
        \post La tabla de distancias del parametro implicito son enviados por el canal
              general de salida.
    */ 
    void escribir_tabla();
    
private:

    /** @brief Matriz que almacena las distancias entre especies */
    map<string, map<string,double> > M_dist;
};

#endif