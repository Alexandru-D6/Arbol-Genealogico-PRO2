/** @file Cjt_cluster.cc
    @brief Código de la clase Conjunto de Clusters (Cjt_cluster).
*/

#include "Cjt_cluster.hh"

Cjt_cluster::Cjt_cluster() {
    M_dist.limpiar_tabla();
    Cjt_clu.clear();
}

Cjt_cluster::~Cjt_cluster(){}

bool Cjt_cluster::paso_wpgma() {
    if (M_dist.size() <= 1) return false;
    else {
        algoritmo_wpgma();
        M_dist.escribir_tabla();
        return true;
    }
}

void Cjt_cluster::inicializar_clusters(const Tabla_distancias& a) {
    M_dist.limpiar_tabla();
    M_dist = a;

    Cjt_clu.clear();

    //crea todos los clusters con las especies individuales.
    for (int i = 1; i <= M_dist.size(); ++i) {
        string iden = M_dist.id_iesimo(i);
        BinTree<pair<string,double>> a(make_pair(iden, 0.00));
        Cjt_clu.insert(make_pair(iden, a));
    }
}

bool Cjt_cluster::escribir_cluster(const string& k) {

    map<string, BinTree<pair<string, double>>>::const_iterator it = Cjt_clu.find(k);

    if (it != Cjt_clu.end()) imprimir_bintree(it->second);

    return (it != Cjt_clu.end());
}

bool Cjt_cluster::escribir_arbol() {
    if (M_dist.size() != 0) {
        
        while (M_dist.size() > 1) algoritmo_wpgma();

        map<string, BinTree<pair<string, double>>>::const_iterator it = Cjt_clu.begin();
        imprimir_bintree(it->second);

        return true;
    }else return  false;
}

void Cjt_cluster::imprimir_bintree(const BinTree<pair<string, double>>& a) {
    if (not a.empty()) {
        if (a.value().second != 0.00 or not a.left().empty() or not a.right().empty()) {
            cout << "[(" << a.value().first << ", " << a.value().second << ") ";

            imprimir_bintree(a.left());
            imprimir_bintree(a.right());
            cout << ']';
        } else {
            cout << '[' << a.value().first << ']';
        }
    }

}

void Cjt_cluster::algoritmo_wpgma() {
    //Actualizar tabla

    string id1, id2;
    double dist_min = M_dist.distancia_minima(id1, id2);
    string new_cluster = id1+id2;

    M_dist.anadir_distancia(new_cluster, new_cluster, 0.00);

    //recalculando las nuevas distancias entre el nuevo cluster y los clusters
    //antiguas
    for (int i = 1; i <= M_dist.size(); ++i) {
        string iden = M_dist.id_iesimo(i);

        if (iden != id1 and iden != id2 and iden != new_cluster) {
            double dist = (M_dist.get_distancia(id1, iden) + M_dist.get_distancia(id2, iden))/2.00;
            M_dist.anadir_distancia(new_cluster, iden, dist);
            M_dist.anadir_distancia(iden, new_cluster, dist);
        }
    }

    M_dist.eliminar_especie(id1);
    M_dist.eliminar_especie(id2);

    //Actualizar Clusters
    
    map<string, BinTree<pair<string, double>>>::iterator left = Cjt_clu.find(id1);
    map<string, BinTree<pair<string, double>>>::iterator right = Cjt_clu.find(id2);

    BinTree<pair<string,double>> cluster = BinTree<pair<string, double>>(make_pair(new_cluster, dist_min/2.00), left->second, right->second);
    Cjt_clu.insert(make_pair(new_cluster, cluster));

    Cjt_clu.erase(left);
    Cjt_clu.erase(right);

}