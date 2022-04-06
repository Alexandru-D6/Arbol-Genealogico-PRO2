/** @file Cjt_especie.cc
    @brief Código de la clase Conjunto de Especies (Cjt_especie).
*/

#include "Cjt_especie.hh"

Cjt_especie::Cjt_especie() {
    especies.clear();
}

Cjt_especie::~Cjt_especie() {}

bool Cjt_especie::existe_especie(const string& id) {
    map<string,Especie>::iterator it = especies.find(id);

    return it != especies.end();
}

Especie Cjt_especie::get_especie(const string& id) {
    return especies[id];
}

bool Cjt_especie::anadir_especie(const string& id, const Especie& esp, Tabla_distancias& tabla) {
    map<string,Especie>::iterator it = especies.find(id);

    if (it == especies.end()) {
        especies.insert(make_pair(id,esp));

        calcular_distancias(id, esp, tabla);
    }

    return not(it != especies.end());
}

bool Cjt_especie::eliminar_especie(const string& id, Tabla_distancias& tabla) {
    map<string,Especie>::iterator it = especies.find(id);
    bool estado = false;

    if (it != especies.end()) {
        especies.erase(id);

        tabla.eliminar_especie(id);
        estado = true;
    }

    return estado;
}

void Cjt_especie::leer_cjt_especie(Tabla_distancias& tabla) {
    especies.clear();
    tabla.limpiar_tabla();
    int n_especies; cin >> n_especies;

    while (n_especies > 0) {
        string id; cin >> id;
        Especie esp;
        esp.leer_especie();

        especies.insert(make_pair(id, esp));
        --n_especies;
    }

    for (map<string,Especie>::iterator it = especies.begin(); it != especies.end(); ++it) {
        calcular_distancias(it->first, it->second, tabla);
    }
}

void Cjt_especie::escribir_cjt_especie() {
    for (map<string,Especie>::iterator it = especies.begin(); it != especies.end(); ++it) {
        cout << it->first << ' ';
        it->second.escribir_especie();
    }
}

void Cjt_especie::calcular_distancias(const string& id, const Especie& a, Tabla_distancias& tabla) {
    for (map<string,Especie>::const_iterator it = especies.begin(); it != especies.end(); ++it) {
        double dist = Especie::distancia_entre(a, it->second);
        tabla.anadir_distancia(id, it->first, dist);
        tabla.anadir_distancia(it->first, id, dist);
    }
}