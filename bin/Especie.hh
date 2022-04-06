/** @file Especie.hh
 *  @brief Especificacion de la clase Especie.
 */

#ifndef ESPECIE_HH
#define ESPECIE_HH

using namespace std;

#ifndef NO_DIAGRAM // sirve para ocultar este include al doxygen
#include <string>  // y de esta manera que no salga en el diagrama
#include <map>     // pero el compilador sigue viendo el include
#include <iostream>
#endif

/** @class Especie
    @brief Representa una especie con un gen.
*/

class Especie {
public:
    //Constructoras

    /** @brief Creadora por defecto.

        \pre cierto.
        \post El resultado es una especie sin gen.
    */  
    Especie();

    /** @brief Destructora por defecto.
    */
    ~Especie();

    //Modificadoras

    /** @brief Modificadora valor para generar kmer.
        
        \pre Cierto.
        \post Modifica el parametro implicito.
    */ 
    static void mod_k(const int& i);

    //Consultoras

    /** @brief Consultora del gen.
        
        Retorna el gen del parametro implicito.
        \pre El parametro implicito contiene un gen valido.
        \post El resultado es el gen del parametro implicito.
    */ 
    string get_gen();

    /** @brief Procesardora de distancia.
        
        Calcula la distancia que hay entre dos especies tras comparar las 
        intersecciones y uniones que hay entre los kmeros (gen dividido en 
        fragmentos de longitud k) de ambas especies. Tras tener las intersecciones
        y uniones se aplica la formula [(1-(intersecciones/uniones))*100].
        
        \pre Ambas especies deben ser validos.
        \post Devuelve la distancia entre especies.
    */ 
    static double distancia_entre(const Especie& a, const Especie& b);

    //Lectura y escritura

    /** @brief Operacion de lectura.
        
        \pre Esta disponible un string correspondientes al gen en el canal
            general de entrada con valor valido.
        \post El gen del parametro implicito es modificado.
    */ 
    void leer_especie();    

    /** @brief Operacion de escritura.
        
        \pre cierto.
        \post El gen del parametro implicito es impreso por el
              canal general de salida.
    */ 
    void escribir_especie();  

private:
    /** @brief Gen completo de la especie */
    string Gen;

    /** @brief Map del gen dividido en substring de longitud k */
    map<string, int> kmer;

    /** @brief Varible que indica la longitud de los kmeros*/
    static int k;

    /** @brief Creadora de la secuencia de string que determina el kmer de la especie.
     *  
     *  Divide el gen en fragmentos de longitud k en todas las combinaciones posibles
     * siempre y cuando los k caracteres esten juntos.
     *  \pre Cierto. 
     *  \post Almacena los el gen dividido en longitudes k en la variable "kmer".
     * 
     */
    void generate_kmer();

};
#endif