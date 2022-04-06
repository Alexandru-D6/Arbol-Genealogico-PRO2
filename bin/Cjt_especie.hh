/** @file Cjt_especie.hh
 *  @brief Especificacion de la clase Conjunto de Especies (Cjt_especie).
 */

#ifndef CJT_ESPECIE_HH
#define CJT_ESPECIE_HH

#include "Especie.hh"
#include "Tabla_distancias.hh"

using namespace std;

#ifndef NO_DIAGRAM // sirve para ocultar este include al doxygen
#include <map>     // y de esta manera que no salga en el diagrama
#include <set>     // pero el compilador sigue viendo el include
#endif

/** @class Cjt_especie
    @brief Representa el conjunto de especies y la distancia que hay entre
            todas las especies.
*/

class Cjt_especie {
public:
    //Constructoras

    /** @brief Creadora por defecto. 

        \pre cierto.
        \post El resultado es un conjunto de especies vacio.
    */  
    Cjt_especie();

    /** @brief Destructora por defecto. */
    ~Cjt_especie();

    //Consultoras

    /** @brief Consultora de especie. 

        \pre cierto.
        \post El resultado es un bool que es cierto si la especie existe en el parametro
              implicito, en caso contrario es falso.
    */  
    bool existe_especie(const string& id);

    /** @brief Consultora de especie. 
     * 
        \pre La especie buscada existe en el conjunto.
        \post Retorna la especie buscada.
    */  
    Especie get_especie(const string& id);

    //Modificadoras

    /** @brief Añadir especie. 

        Permite añadir una especie adicional al conjunto y actualizar la tabla de distancias.
        \pre El id es valido, string con caracteres entre (a-z) y (A-Z).
        \post La funcion retorna un bool especificando si se ha podido añadir la especie
              o no. Si es falso, la especie ya existe en el conjunto y retornara false.
              En caso contrario, se se añadira la especie, se calcularan todas las distancias
              entre la nueva especie y las que habia en el conjunto, que consecuentemente se 
              añadiran a la tabla, y finalemente retornara un true.
    */  
    bool anadir_especie(const string& id, const Especie& esp, Tabla_distancias& tabla);

    /** @brief Eliminar especie. 

        Permite eliminar una especie del conjunto.
        \pre cierto.
        \post La funcion retorna un bool especificando si se ha podido eliminar la especie
              o no. Si es falso, la especie no existe en el conjunto, en caso contrario se
              se elimina la especie, se actualizara la tabla y retornara un true.
    */ 
    bool eliminar_especie(const string& id, Tabla_distancias& tabla);

    //Escritura y Lectura

    /** @brief Operacion de lectura.
        
        \pre Existen una n>= 0, que indica la cantidad de especies que se leeran,
             y n cantidad de especies validas en el canal general de entrada.
        \post Se añaden todas las especies al parametro implicito.
    */ 
    void leer_cjt_especie(Tabla_distancias& tabla);

    /** @brief Operacion de escritura.
        
        \pre cierto.
        \post Todas las especies del parametro implicito son enviados por el canal
            general de salida.
    */ 
    void escribir_cjt_especie();

private:

    /** @brief Conjunto que almacenara las distintas especies
               ordenadas ascendentemente segun su ID de la especie.*/
    map<string, Especie> especies;

    /** @brief Calcula todas las distancias actuales entre especies. 
     
        \pre cierto.
        \post Calcula todas las distancias entre la especie del parametro explicito
              y las del conjunto de especies del parametro implicito. A su vez,
              todas estas distancias son almacenadas en la tabla del parametro
              explicito.
    
    */ 
    void calcular_distancias(const string& id, const Especie& a, Tabla_distancias& tabla); 

};
#endif