/**
 * @mainpage Arbol Filogenico.
 
 * Este programa permite la gestion de multiples especies que se pueden clasificar segun
 * sus antecesores a traves de sus propios genes.
 * 
 * 
*/

/** @file Program.cc
    @brief Programa principal.
*/

// para que el diagrama modular quede bien se han escrito includes redundantes;
// en los ficheros .hh de la documentación de las clases ocurre lo mismo.
#include "Especie.hh"
#include "Cjt_especie.hh"
#include "Cjt_cluster.hh"
#include "Tabla_distancias.hh"

using namespace std;

#ifndef NO_DIAGRAM
#include <iostream>
#endif


/** @brief Programa principal con todas las operacion que se pueden realizar <em>Arbol Filogenico</em>.
*/
int main() {
    int k; cin >> k;

    Especie::mod_k(k);

    string op;
    Cjt_cluster C_cluster;
    Cjt_especie C_especie;
    Tabla_distancias T_especies;

    while (cin >> op and op != "fin") {
        cout << "# " << op;

        if (op == "crea_especie") {
            string id; cin >> id;

            Especie esp;
            esp.leer_especie();

            cout << ' ' << id << ' ';
            esp.escribir_especie();
            
            if (not C_especie.anadir_especie(id, esp, T_especies)) {
                cout << "ERROR: La especie " << id << " ya existe." << endl;
            }

        }else if (op == "obtener_gen") {
            string id; cin >> id;

            cout << ' ' << id << endl;

            if (C_especie.existe_especie(id)) {
                C_especie.get_especie(id).escribir_especie();
            }else {
                cout << "ERROR: La especie " << id << " no existe." << endl;
            }


        }else if (op == "distancia") {  
            string id1, id2;
            cin >> id1 >> id2;

            cout << ' ' << id1 << ' ' << id2 << endl;

            if (C_especie.existe_especie(id1)) {
                if (C_especie.existe_especie(id2)) {
                    double dist = T_especies.get_distancia(id1, id2);
                    cout << dist << endl;
                }else{
                    cout << "ERROR: La especie " << id2 << " no existe." << endl;
                }
            }else {
                if (C_especie.existe_especie(id2)) cout << "ERROR: La especie " << id1 << " no existe." << endl;
                else cout << "ERROR: La especie " << id1 << " y la especie " << id2 << " no existen." << endl;
            }


        }else if (op == "elimina_especie") {
            string id; cin >> id;
            cout << ' ' << id << endl;
            if (not C_especie.eliminar_especie(id, T_especies)) cout << "ERROR: La especie " << id << " no existe." << endl;


        }else if (op == "existe_especie") {
            string id; cin >> id;
            cout << ' ' << id << endl;
            if (C_especie.existe_especie(id)) cout << "SI" << endl;
            else cout << "NO" << endl;

        }else if (op == "lee_cjt_especies") {
            cout << endl;
            C_especie.leer_cjt_especie(T_especies);


        }else if (op == "imprime_cjt_especies") {
            cout << endl;
            C_especie.escribir_cjt_especie();


        }else if (op == "tabla_distancias") {
            cout << endl;
            T_especies.escribir_tabla();


        }else if (op == "inicializa_clusters") {
            cout << endl;
            C_cluster.inicializar_clusters(T_especies);
            T_especies.escribir_tabla();


        }else if (op == "ejecuta_paso_wpgma") {
            cout << endl;
            if (not C_cluster.paso_wpgma()) cout << "ERROR: num_clusters <= 1" << endl;


        }else if (op == "imprime_cluster") {
            string alpha; cin >> alpha;
            cout << ' ' << alpha << endl;

            if (not C_cluster.escribir_cluster(alpha)) cout << "ERROR: El cluster " << alpha << " no existe." << endl;
            else cout << endl;

        } else if (op == "imprime_arbol_filogenetico") {
            cout << endl;
            C_cluster.inicializar_clusters(T_especies);
            if (not C_cluster.escribir_arbol()) cout << "ERROR: El conjunto de clusters es vacio." << endl;
            else cout << endl;

        }
        cout << endl;
    }
}