/** @file Tabla_distancias.cc
    @brief Código de la clase Tabla de distancias (Tabla_distancias).
*/

#include "Tabla_distancias.hh"

Tabla_distancias::Tabla_distancias() {
    M_dist.clear();
}

Tabla_distancias::~Tabla_distancias() {}

//Modificadoras

void Tabla_distancias::anadir_distancia(const string& id1, const string& id2, const double& dist) {
    M_dist.insert(make_pair(id1, map<string,double>()));
    M_dist[id1].insert(make_pair(id2,dist));
}

bool Tabla_distancias::eliminar_especie(const string& id) {
    bool borrado = M_dist.erase(id);
    
    map<string, map <string, double>>::iterator itr = M_dist.begin();

    while (itr != M_dist.end() and borrado) {
        itr->second.erase(id);
        ++itr;
    }

    return borrado;
}

void Tabla_distancias::limpiar_tabla() {
    M_dist.clear();
}

//Consultoras

double Tabla_distancias::get_distancia(const string& id1, const string& id2) const{
    map<string,map<string,double>>::const_iterator itr = M_dist.find(id1);
    map<string,double>::const_iterator itc = itr->second.find(id2);
    return itc->second;
}

int Tabla_distancias::size() const {
    return M_dist.size();
}

string Tabla_distancias::id_iesimo(int i) {
    map<string, map<string, double>>::const_iterator it = M_dist.begin();

    while (i > 1) {
        ++it;
        --i;
    }

    return it->first;
}

bool Tabla_distancias::existe_especie(const string& id) {
    map<string, map<string,double>>::const_iterator it = M_dist.find(id);

    return it != M_dist.end();
}

double Tabla_distancias::distancia_minima(string& id1, string& id2) {
    map<string, map <string, double>>::iterator itr = M_dist.begin();
    map <string, double>::iterator itc;

    double min_dist = 101.00;

    while (itr != M_dist.end()) {
        itc = itr->second.find(itr->first);
        ++itc;

        while (itc != itr->second.end()) {
            if (itc->second < min_dist) {
                min_dist = itc->second;
                id1 = itr->first;
                id2 = itc->first;
            }
            ++itc;
        }
        ++itr;
    }
    return min_dist;
}  

//Escritura

void Tabla_distancias::escribir_tabla() {
    map<string, map <string, double>>::iterator itr = M_dist.begin();
    map <string, double>::iterator itc;

    while (itr != M_dist.end()) {
        itc = itr->second.find(itr->first);
        ++itc;

        cout << itr->first << ':';

        while (itc != itr->second.end()) {
            cout << ' ' << itc->first << ' ' << '(' << itc->second << ')';
            ++itc;
        }
        cout << endl;
        ++itr;
    }
}