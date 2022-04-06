/** @file Cjt_cluster.hh
 *  @brief Especificacion de la clase Conjunto de Clusters (Cjt_cluster).
 */

#ifndef CJT_CLUSTER_HH
#define CJT_CLUSTER_HH

#include "Cjt_especie.hh"
#include "Tabla_distancias.hh"

using namespace std;

#ifndef NO_DIAGRAM    // sirve para ocultar este include al doxygen
#include <set>        // y de esta manera que no salga en el diagrama
#include "BinTree.hh" // pero el compilador sigue viendo el include
#include <map>
#endif

/** @class Cjt_cluster
    @brief Representa el conjunto arbolesco de unas especies.
*/

class Cjt_cluster {
public:
    //Constructoras

    /** @brief Creadora por defecto. 

        Se ejecuta automáticamente al declarar un Cjt_cluster.
        \pre cierto.
        \post El resultado es un conjunto de cluster vacio.
    */ 
    Cjt_cluster();

    /** @brief Destructora por defecto.
    */
    ~Cjt_cluster();

    //Modificadoras

    /** @brief Paso WPGMA. 

        Esta funcion ejecuta el algoritmo WPGMA el cual consiste en cojer los clusters
        de menor distancia entre si y crea un nuevo cluster con la distancia y el identificador
        de los dos clusters seleccionados. A su vez, actualiza todas las distancias entre las
        otras especies que tenian influencia con las seleccionadas. 
        Si no se pudo ejecutar correctamente el algoritmo, cuando no tiene ninguna especie o
        cuando se ha generado completamente el arbol filogenetico, saltara un error por el
        canal general de salida.

        \pre cierto.
        \post Tras actualizar la tabla de distancias y conjunto de cluster 
              imprime la tabla de distancias actualizada. Tambien devuelve un true, si se 
              ha podido ejecutar correctamente, o un false en caso contrario
    */ 
    bool paso_wpgma();

    /** @brief Inicializar clusters. 

        Esta funcion borrar todos los datos tanto de la tabla de distancia como el 
        conjunto de clusters del parametro impricito y crea nuevos datos con la
        tabla de distancias, del parametro explicito, del conjunto de especie en el 
        estado actual. 
        Los clusters estan divididos en especies individuales sin haber ejecutado
        ningun paso WPGMA.

        \pre cierto.
        \post La tabla del distancias esta sustituida con el parametro explicito
              y han sido añadidos los nuevos clusters.
    */ 
    void inicializar_clusters(const Tabla_distancias& a);

    //Escritura y Lectura

    /** @brief Operacion de escritura.
        
        Busca el cluster que tenga el parametro k como identificador e imprime 
        todas las ramas que tenga el cluster en concreto, en caso contrario, salta
        un error por el canal general de salida.

        \pre cierto.
        \post El cluster buscado del parametro implicito es enviado por el canal general 
              de salida. Si es encontrado devuelve un true, en caso contrario devuelve un false.
    */ 
    bool escribir_cluster(const string& k);


    /** @brief Operacion de escritura.
        
        Tras inicializar clusters con las especies actualizadas, esta operacion va 
        ejecutando el algoritmo WPGMA hasta general el arbol filogenetico completo 
        y luego es impreso por el canal general de salida.
        
        \pre cierto.
        \post El arbol del parametro implicito es escrito por el canal general de salida.
    */ 
    bool escribir_arbol();

private:
    /** @brief Conjunto de los clusters */
    map<string, BinTree<pair<string, double>>> Cjt_clu;

    /** @brief Tabla de distancias de los clusters*/
    Tabla_distancias M_dist;

    /** @brief Operacion de escritura de un arbol
    
       \pre Cierto.
       \post El BinTree del parametro explicito es enviado por el canal general de salida. Tiene
             el formato Preorden con una estructura de parentesis especifico para comprender mejor
             el arbol a la salida.
      
    */
    static void imprimir_bintree(const BinTree<pair<string, double>>& a);

    /** @brief Operacion de WPGMA

     *  Esta operacion ejecuta todos lo calculos y operaciones necesarias para crear, tanto
     *  en la tabla de distancias como en el conjunto de clusters, el nuevo cluster que sale
     *  de juntar los dos clusters de menor distancia. Y luego elimina los clusters antiguos 
     *  que son los hijos del nuevo.
    
        \pre Cierto.
        \post Junta los clusters con menor distancia del parametro implicito, actualizando la 
              tabla, el conjunto de clusters y la lista de especies.
    */
    void algoritmo_wpgma();

};
#endif