/** @file Cjt_cluster.hh
 *  @brief Especificacion de la clase Conjunto de Clusters.
 */

#ifndef CJT_CLUSTER_HH
#define CJT_CLUSTER_HH

#include "Cjt_especie.hh"
#include "Tabla_distancias.hh"
#include "BinTree.hh"

#ifndef NO_DIAGRAM   // sirve para ocultar este include al doxygen
#include <set>       // y de esta manera que no salga en el diagrama
using namespace std; // pero el compilador sigue viendo el include
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

    /** @brief Creadora copiadora. 

        Permite declarar un conjunto nuevo a partir de uno existente.
        \pre cierto.
        \post El resultado es el parametro implicito con la copia del conjunto.
    */  
    Cjt_cluster(const Cjt_cluster& C_esp);

    /** @brief Destructora por defecto.
    */
    ~Cjt_cluster();

    //Consultoras

    //Modificadoras
    
    /** @brief Modificadora de la tabla en el parametro implicito. 

        Coje la tabla pasada por reference constante y la copia en el parametro implicito.
        \pre cierto.
        \post La tabla esta copiada en el parametro implicito.
    */ 
    void copiar_tabla(const Tabla_distancias& a);

    /** @brief Paso WPGMA. 

        Actualiza la la tabla de distancias y los clusters juntando los de menor distancia 
        actuales.
        \pre cierto.
        \post Imprime la tabla de distancias actualizada.
    */ 
    bool paso_wpgma();

    /** @brief Inicializar clusters. 

        Actualiza el conjunto de cluster para que sea el mismo que la tabla de distancias.
        \pre cierto.
        \post El conjunto de clusters esta actualizado.
    */ 
    void inicializar_clusters(const Tabla_distancias& a);

    //Escritura y Lectura

    /** @brief Operacion de escritura.
        
        Busca el cluster que tenga el parametro k e imprime todas las ramas de ese cluster en
        concreto.
        \pre cierto.
        \post El cluster buscado del parametro implicito es enviado por el canal general 
              de salida. Si es encontrado devuelve un true, en caso contrario devuelve un false.
    */ 
    bool escribir_cluster(const string& k);


    /** @brief Operacion de escritura.
        
        Esta operacion acaba de unir todos los clusters necesarios e imprime todo el arbol.
        \pre cierto.
        \post El arbol del parametro implicito es enviado por el canal general de salida.
    */ 
    bool escribir_arbol(const Tabla_distancias& a);

private:
    map<string, BinTree<pair<string, double>>> Cjt_clu;

    Tabla_distancias M_dist;

    void imprimir_bintree(const BinTree<pair<string, double>>& a);

    bool buscar_bintree(const BinTree<pair<string, double>>& a, const string& clus); //habria que quitarlo

    static void algoritmo_wpgma(Tabla_distancias& M_dist, map<string, BinTree<pair<string, double>>>& Cjt_clu);

};
#endif