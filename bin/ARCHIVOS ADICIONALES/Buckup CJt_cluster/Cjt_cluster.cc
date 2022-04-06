#include "Cjt_cluster.hh"

Cjt_cluster::Cjt_cluster() {
    M_dist.limpiar_tabla();
    Cjt_clu.clear();
}


Cjt_cluster::Cjt_cluster(const Cjt_cluster& C_esp) {
    M_dist = C_esp.M_dist;
    Cjt_clu = C_esp.Cjt_clu;
}


Cjt_cluster::~Cjt_cluster(){}

void Cjt_cluster::copiar_tabla(const Tabla_distancias& a) {
    M_dist = a;
}

bool Cjt_cluster::paso_wpgma() {
    bool estado;
    if (M_dist.size() <= 1) estado = false;
    else {
        algoritmo_wpgma(M_dist, Cjt_clu);

        M_dist.escribir_tabla();
        estado = true;
    }
    return estado;
}
void Cjt_cluster::inicializar_clusters(Tabla_distancias a) {
    M_dist = a;

    Cjt_clu.clear();
    set<string> ids = a.get_ids();

    for (set<string>::const_iterator it = ids.begin(); it != ids.end(); ++it) {
        BinTree<pair<string,double>> a(make_pair(*it, 0.00));
        Cjt_clu.insert(make_pair(*it, a));
    }
    M_dist.escribir_tabla();
}

bool Cjt_cluster::escribir_cluster(const string& k) {
    bool impreso = false;

    map<string, BinTree<pair<string, double>>>::const_iterator it = Cjt_clu.begin();

    while (it != Cjt_clu.end() and not impreso) {
        if (k.size() >= it->first.size()) {
            impreso = buscar_bintree(it->second, k);
        }
        ++it;
    }

    return impreso;
}

bool Cjt_cluster::escribir_arbol(Tabla_distancias a) {
    bool estado;
    if (a.size() != 0) {
        map<string, BinTree<pair<string, double>>> cjt_arbol;
        set<string> ids = a.get_ids();

        for (set<string>::const_iterator it = ids.begin(); it != ids.end(); ++it) {
            BinTree<pair<string,double>> a(make_pair(*it, 0.00));
            cjt_arbol.insert(make_pair(*it, a));
        }
        
        while (a.size() != 1) {
            algoritmo_wpgma(a, cjt_arbol);
        }

        map<string, BinTree<pair<string, double>>>::const_iterator it = cjt_arbol.begin();
        imprimir_bintree(it->second);

        estado = true;
    }else estado = false;
    return estado;
}

bool Cjt_cluster::buscar_bintree(const BinTree<pair<string, double>>& a, const string& clus) {
    if (not a.empty()) {
        if (a.value().first == clus) {
            imprimir_bintree(a);
            return true;
        }else {
            return buscar_bintree(a.left(), clus);
            return buscar_bintree(a.right(), clus);
        }
    }else return false;
}

void Cjt_cluster::imprimir_bintree(const BinTree<pair<string, double>>& a) {
    if (not a.empty()) {
        if (a.value().second != 0.00) {
            cout << "[(" << a.value().first << ", " << a.value().second << ") ";

            imprimir_bintree(a.left());
            imprimir_bintree(a.right());
            cout << ']';
        } else {
            cout << '[' << a.value().first << ']';
        }
    }

}

void Cjt_cluster::algoritmo_wpgma(Tabla_distancias& M_dist, map<string, BinTree<pair<string, double>>>& Cjt_clu) {
    //Actualizar tabla

    string id1, id2;
    double dist_min = M_dist.distancia_minima(id1, id2);
    string new_cluster = id1+id2;

    set<string> clusters = M_dist.get_ids();

    M_dist.anadir_distancia(new_cluster, new_cluster, 0.00);

    for (set<string>::const_iterator it = clusters.begin(); it != clusters.end(); ++it) {
        if (*it != id1 and *it != id2) {
            double dist = (M_dist.get_distancia(id1, *it) + M_dist.get_distancia(id2, *it))/2.00;
            M_dist.anadir_distancia(new_cluster, *it, dist);
            M_dist.anadir_distancia(*it, new_cluster, dist);
        }
    }

    M_dist.eliminar_especie(id1);
    M_dist.eliminar_especie(id2);

    //Actualizar Clusters

    map<string, BinTree<pair<string, double>>>::iterator left = Cjt_clu.find(id1);
    map<string, BinTree<pair<string, double>>>::iterator right = Cjt_clu.find(id2);

    BinTree<pair<string,double>> cluster = BinTree<pair<string, double>>(make_pair(new_cluster, dist_min/2), left->second, right->second);
    
    Cjt_clu.insert(make_pair(new_cluster, cluster));

    Cjt_clu.erase(left);
    Cjt_clu.erase(right);

}