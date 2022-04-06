/** @file Especie.cc
    @brief Código de la clase Especie
*/

#include "Especie.hh"

int Especie::k = -1;

Especie::Especie() {
    Especie::Gen = -1;

}

Especie::~Especie() {

}

void Especie::mod_k(const int& i) {
    Especie::k = i;
}

string Especie::get_gen() {
    return Especie::Gen;
}

double Especie::distancia_entre(const Especie& a, const Especie& b) {
    int interseccion_kmer = 0;
    int union_kmer = 0;
    map<string,int>::const_iterator ita = a.kmer.begin();
    map<string,int>::const_iterator itb = b.kmer.begin();

    //recorre ambos map y va anotando las intersecciones y uniones que se
    //producen.
    while (ita != a.kmer.end() and itb != b.kmer.end()) {
        if (ita->first < itb->first) {
            union_kmer += ita->second;
            ++ita;
        }else if (ita->first > itb->first) {
            union_kmer += itb->second;
            ++itb;
        }else {
            if (ita->second > itb->second) {
                interseccion_kmer += itb->second;
                union_kmer += ita->second;
            }else {
                interseccion_kmer += ita->second;
                union_kmer += itb->second;
            }
            ++ita;
            ++itb;
        }
    }

    while(ita != a.kmer.end()){
        union_kmer += ita->second;
        ++ita;
    }
    while(itb != b.kmer.end()){
        union_kmer += itb->second;
        ++itb;
    }

    return double((1.00 - double(interseccion_kmer)/double(union_kmer))*100.00);
    
}

void Especie::leer_especie() {
    cin >> Especie::Gen;

    generate_kmer();
}

void Especie::escribir_especie() {
    cout << Especie::Gen << endl;
}

void Especie::generate_kmer() {
    int gen_size = Especie::Gen.size();

    for (int i = 0; i <= gen_size - k; ++i) {
        string temp = "";
        for (int j = i; j - i < k; ++j) {
            temp += Gen[j];
        }

        kmer[temp] += 1;
    }
}